#!/bin/env python3

import os
import subprocess as sp
from argparse import ArgumentParser

import sys


def _parse_cli():
    parser = ArgumentParser(description="build Frit")
    parser.add_argument("-b", "--build", help="build type", choices=["Debug", "Release", "MinSizeRel"], default="Debug")
    parser.add_argument("-t", "--tests", help="build tests", action="store_true")
    return parser.parse_args()


def _cmake(*args):
    return sp.call(["cmake"] + list(args)) == 0


if __name__ == "__main__":
    parsed_args = _parse_cli()
    build_path = os.path.join(os.getcwd(), "build", parsed_args.build)

    cmake_options = [
        "-DCMAKE_BUILD_TYPE={}".format(parsed_args.build),
        "-DFRIT_BUILD_TESTS={}".format("ON" if parsed_args.tests else "OFF")
    ]

    if not _cmake("-S", os.getcwd(), "-B", build_path, *cmake_options):
        sys.exit(1)
    if not _cmake("--build", build_path):
        sys.exit(1)
    if parsed_args.tests:
        sp.call([sys.executable, "test.py", "-b", parsed_args.build])
    sys.exit(0)
