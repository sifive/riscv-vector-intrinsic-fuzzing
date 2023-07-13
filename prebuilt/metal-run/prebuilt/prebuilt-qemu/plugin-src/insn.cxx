/*
 * Copyright (C) 2018, Emilio G. Cota <cota@braap.org>
 *
 * License: GNU GPL, version 2 or later.
 *   See the COPYING file in the top-level directory.
 */
#include <unordered_map>
#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include <glib.h>

extern "C" {
#include <qemu-plugin.h>

QEMU_PLUGIN_EXPORT int qemu_plugin_version = QEMU_PLUGIN_VERSION;

QEMU_PLUGIN_EXPORT int qemu_plugin_install(qemu_plugin_id_t id,
                                           const qemu_info_t *info,
                                           int argc, char **argv);
}

// RISC-V PC at least 2 byte align.
static uint64_t chunk_offset(uint64_t pc){
  return (pc >> 1) & 0xfffull;
}

static uint64_t chunk_index(uint64_t pc){
  return ((pc >> 1) & ~0xfffull) >> 12;
}

struct Chunk {
  uint64_t index;
  uint64_t hist[4096];
};

static uint64_t insn_count;
static bool do_inline;
static std::unordered_map<uint64_t, Chunk> inst_histogram;
static Chunk *cache = nullptr;

static void vcpu_insn_exec_before(unsigned int cpu_index, void *udata)
{
    static uint64_t last_pc;
    uint64_t this_pc = GPOINTER_TO_UINT(udata);
    uint64_t offset = chunk_offset(this_pc);
    uint64_t index = chunk_index(this_pc);

    if (cache && cache->index == index) {
       cache->hist[offset]++;
       return;
    }

    cache = &inst_histogram[index];
    cache->index = index;
    cache->hist[offset]++;
}

static uint64_t *get_hist_ptr(uint64_t this_pc)
{
    uint64_t offset = chunk_offset(this_pc);
    uint64_t index = chunk_index(this_pc);

    if (cache && cache->index == index) {
       return &cache->hist[offset];
    }

    cache = &inst_histogram[index];
    cache->index = index;
    return &cache->hist[offset];
}

static void vcpu_tb_trans(qemu_plugin_id_t id, struct qemu_plugin_tb *tb)
{
    size_t n = qemu_plugin_tb_n_insns(tb);
    size_t i;
#if 0
    for (i = 0; i < n; i++) {
        struct qemu_plugin_insn *insn = qemu_plugin_tb_get_insn(tb, i);

        uint64_t vaddr = qemu_plugin_insn_vaddr(insn);
        qemu_plugin_register_vcpu_insn_exec_cb(
            insn, vcpu_insn_exec_before, QEMU_PLUGIN_CB_NO_REGS,
            GUINT_TO_POINTER(vaddr));
    }
#else
    for (i = 0; i < n; i++) {
        struct qemu_plugin_insn *insn = qemu_plugin_tb_get_insn(tb, i);

        uint64_t vaddr = qemu_plugin_insn_vaddr(insn);
	uint64_t *qhist_ptr = get_hist_ptr(vaddr);
	qemu_plugin_register_vcpu_insn_exec_inline(
	    insn, QEMU_PLUGIN_INLINE_ADD_U64, qhist_ptr, 1);
    }
#endif
}

static void plugin_exit(qemu_plugin_id_t id, void *p)
{
    // Sum up total inst count
    uint64_t total_count = 0;
    for (auto inst_info_chunk :  inst_histogram) {
	auto chunk = inst_info_chunk.second;
	for (size_t i = 0; i < 4096 ; ++i) {
            total_count += chunk.hist[i];
	}
    }

    g_autofree gchar *out =
	g_strdup_printf("pc,dyn_insn_count,%" PRIu64 "\n",
	                total_count);
    qemu_plugin_outs(out);
    for (auto inst_info_chunk :  inst_histogram) {
	auto chunk = inst_info_chunk.second;
	uint64_t base_pc = chunk.index << 13;
	for (size_t i = 0; i < 4096 ; ++i) {
            uint64_t pc = base_pc + (i << 1);
	    if (chunk.hist[i] == 0)
		continue;
            out = g_strdup_printf("0x%" PRIx64 ",%" PRIu64 "\n",
                    pc, chunk.hist[i]);
            qemu_plugin_outs(out);
	}
    }
}

QEMU_PLUGIN_EXPORT int qemu_plugin_install(qemu_plugin_id_t id,
                                           const qemu_info_t *info,
                                           int argc, char **argv)
{
    qemu_plugin_register_vcpu_tb_trans_cb(id, vcpu_tb_trans);
    qemu_plugin_register_atexit_cb(id, plugin_exit, NULL);
    return 0;
}
