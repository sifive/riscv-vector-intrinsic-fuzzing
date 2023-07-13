import os
import utils
import re

utils.check_package('elftools', 'pyelftools')

import elftools.elf.elffile

class HexFile:
    def __init__(self, path, hexclass):
        self.path = path
        self.fileClass = hexclass

def createHexFile(path):
    if not os.path.exists(path):
        raise Exception("%s not found" % path)
    rv = 0
    hexclass = None

    '''
    A better way to do this is to invoke grep via subprocess.
    However, the behavior of subprocesss is unexpected with
    type = (callable function) in argparse.
    I suppose it should continue to the next line after invoking subprocess,
    but it doesn't
    '''
    with open(path) as hex_file:
        for a_line in hex_file.readlines():
            if re.match("[g-z]", a_line):
                rv = 1
                break
            if hexclass == None:
                if len(a_line) == 8:
                    hexclass = 32
                elif len(a_line) == 16:
                    hexclass = 64
    if rv != 0:
        return None
    return HexFile(path, hexclass)

class ElfFile:
    def __init__(self, path, elffile):
        self.path = path
        self.machine = elffile.header['e_machine'].lstrip('EM_')
        self.fileClass = elffile.elfclass
        self.elffile = elffile


def createElfFile(path):
    if not os.path.exists(path):
        raise Exception("%s not found" % path)

    try:
        p = elftools.elf.elffile.ELFFile(open(path, 'rb'))
    except elftools.common.exceptions.ELFError:
        raise Exception("%s is not ELF file!" % path)

    return ElfFile(path, p)

def fileHandler(path):
    try:
        input_file = createElfFile(path)
    except:
        input_file = createHexFile(path)
    return input_file
