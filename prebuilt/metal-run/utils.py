import subprocess
import importlib
import os
import random
import socket
import sys

def escape_shell_arg(arg):
    arg = arg.replace("\"", "\\\"")
    return "\"%s\"" % arg

def check_package(package_name, install_name=None, version=3):
    if install_name is None:
        install_name = package_name
    try:
        importlib.import_module(package_name)
    except ImportError:
        pip_lock = os.path.join(os.path.dirname(os.path.abspath(__file__)), ".piplock")
        subprocess.call("flock %s %s -m pip install --user %s" %
                        (pip_lock, sys.executable, install_name), shell=True)
        # Ref: https://stackoverflow.com/questions/25384922/how-to-refresh-sys-path
        import site
        importlib.reload(site)

def check_port_available(port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    result = sock.connect_ex(('127.0.0.1',port)) != 0
    sock.close()
    return result

def grab_available_port():

    uid = os.getuid()
    base_port = uid + 10000
    port = base_port
    while not check_port_available(port):
        port += random.randint(1,100)

        # Too bad, rewind and try again.
        if port > 65535:
            port = base_port

    return port
