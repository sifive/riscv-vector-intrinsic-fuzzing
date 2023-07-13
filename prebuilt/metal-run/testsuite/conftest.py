#!/usr/bin/env python3
import pytest
import os
import sh

@pytest.fixture(autouse=True, scope="session")
def env_sifive():
    env_sifive = os.environ.copy()
    return env_sifive

@pytest.fixture(scope="session")
def qemu_run():
    return sh.Command(f"{os.getcwd()}/qemu-run")
