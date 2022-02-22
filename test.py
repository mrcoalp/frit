#!/bin/env python3

import os
import subprocess as sp
from argparse import ArgumentParser

import sys


def _parse_cli():
    parser = ArgumentParser(description="test Frit")
    parser.add_argument("-b", "--build", help="build type", choices=["Debug", "Release", "MinSizeRel"], default="Debug")
    return parser.parse_args()


if __name__ == "__main__":
    parsed_args = _parse_cli()
    test_path = os.path.join(os.getcwd(), "build", parsed_args.build, "test")
    os.chdir(test_path)
    sys.exit(sp.call(["ctest", "--extra-verbose"]))
