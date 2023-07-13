SUPPORTTED_EXTS = "iemafdcbvp"
MC_EXT_PREFIX = "zsx"

def parse_mc_ext(ext_str, idx):
    end_idx = ext_str[idx+1:].find('_')
    if end_idx == -1:
        end_idx = len(ext_str)
    else:
        end_idx = end_idx + idx + 1
    major = 0
    minor = 0
    version_begin_idx = end_idx
    if ext_str[end_idx-1].isdigit():
        # This ext came with the version.
        v_idx = end_idx - 1
        while (ext_str[v_idx].isdigit()) and v_idx > idx:
            v_idx -= 1
        major = int(ext_str[v_idx+1:end_idx])
        version_begin_idx = v_idx+1
        if (ext_str[v_idx] == 'p'):
            minor = major
            major_v_idx = v_idx - 1
            while (ext_str[major_v_idx].isdigit()) and major_v_idx > idx:
                major_v_idx -= 1
            major = int(ext_str[major_v_idx+1:v_idx])
            version_begin_idx = major_v_idx+1

    return end_idx, ext_str[idx:version_begin_idx], major, minor

def parse_version(ext_str, idx):
    major = 2
    minor = 0
    strlen = len(ext_str)
    end_idx = idx + 1
    if idx+1 < strlen and ext_str[idx+1].isdigit():
        v_idx = idx + 1
        while v_idx < strlen and (ext_str[v_idx].isdigit()):
            v_idx += 1
        major = int(ext_str[idx+1:v_idx])
        end_idx = v_idx
        if (ext_str[v_idx] == 'p'):
            minor_v_idx = v_idx + 1
            while minor_v_idx < strlen and  (ext_str[minor_v_idx].isdigit()):
                minor_v_idx += 1
            minor = int(ext_str[v_idx+1:minor_v_idx])
            end_idx = minor_v_idx

    return end_idx, ext_str[idx], major, minor

def parse(isa_str):
    isa_str = isa_str.replace("rv64g", "rv64imafd").replace("rv32g", "rv32imafd")
    if not (isa_str.startswith("rv32") or isa_str.startswith("rv64")):
        return None
    ext_str = isa_str[4:]
    # XXX: We don't validate arch string too much.
    # TODO: Handle ext. implication.
    idx = 0
    extstrlens = len(ext_str)
    exts = dict()
    while idx < extstrlens:
        if ext_str[idx] in SUPPORTTED_EXTS:
            idx, ext_name, major, minor = parse_version(ext_str, idx)
        elif ext_str[idx] in MC_EXT_PREFIX:
            idx, ext_name, major, minor = parse_mc_ext(ext_str, idx)
        elif ext_str[idx] == '_':
            idx = idx + 1
            continue
        else:
            raise Exception("Unrecognized ext : `%s`, %s" %
                            (ext_str[idx], ext_str))
        exts[ext_name] = (major, minor)
    return exts

# Testcase:
if __name__ == '__main__':
    print(parse("rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_v1p0_zicsr2p0_zfh0p1_zba1p0_zbb1p0_zve32f1p0_zve32x1p0_zve64d1p0_zve64f1p0_zve64x1p0_zvfh0p1_zvl128b1p0_zvl256b1p0_zvl32b1p0_zvl512b1p0_zvl64b1p0_xsfvfhbfmin0p1_xsfvqmaccqoq0p1"))
