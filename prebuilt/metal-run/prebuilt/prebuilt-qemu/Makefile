QEMU_SRC_PATH:=
INSTALL_PROG:=qemu-riscv32 qemu-system-riscv64 qemu-riscv64 qemu-system-riscv32

QEMU_BRANCH=$(shell git -C $(QEMU_SRC_PATH) branch --show-current)
QEMU_SHA1=$(shell git -C $(QEMU_SRC_PATH) rev-parse HEAD)
QEMU_REMOTE_URL=$(shell git -C $(QEMU_SRC_PATH) config --get remote.origin.url)
NEW_BRANCH_NAME=$(QEMU_BRANCH)-$(shell  git -C $(QEMU_SRC_PATH) rev-parse --short HEAD)

all: stamps/add-git-qemu

stamps/configure-qemu:
	mkdir -p $(dir $@)
	mkdir -p build
	cd build && \
		$(QEMU_SRC_PATH)/configure \
		--target-list=riscv32-linux-user,riscv64-linux-user,riscv32-softmmu,riscv64-softmmu \
		--enable-plugins \
		--disable-bzip2 \
		--prefix=`pwd`/../install \
		--disable-docs --disable-guest-agent --disable-gio \
		--disable-spice --disable-spice-protocol --disable-vnc \
		--disable-sdl --disable-gtk --disable-alsa
	touch $@

stamps/build-qemu: stamps/configure-qemu
	mkdir -p $(dir $@)
	cd build && $(MAKE)
	cd build && $(MAKE) install
	touch $@

stamps/build-qemu-hist-plugin: stamps/build-qemu
	mkdir -p plugins
	$(CXX) plugin-src/insn.cxx -O3 -shared -o plugins/insn_hist.so `pkg-config glib-2.0 --cflags` -I install/include/ -fPIC -static-libgcc -static-libstdc++
	touch $@

stamps/add-git-qemu: stamps/build-qemu stamps/build-qemu-hist-plugin
	mkdir -p $(dir $@)
	mkdir -p bin
	cp $(addprefix install/bin/, $(INSTALL_PROG)) bin/
	strip bin/*
	git add $(addprefix bin/, $(INSTALL_PROG))
	git add plugins/*
	git branch $(NEW_BRANCH_NAME)
	git checkout $(NEW_BRANCH_NAME)
	git commit \
		-m "Prebuilt binary for '$(QEMU_BRANCH)' branch" \
		-m "sha1: $(QEMU_SHA1)" \
		-m "repo: $(QEMU_REMOTE_URL)"
	git push origin $(NEW_BRANCH_NAME)
