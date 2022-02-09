#!/bin/env python3

import os
import subprocess

import sys

if __name__ == "__main__":
    bin_path = os.path.join(os.getcwd(), "build", "Debug", "frit-test")

    if not os.path.exists(bin_path):
        sys.exit("test binary not found under '{}'".format(bin_path))

    sys.exit(subprocess.call([bin_path]))
