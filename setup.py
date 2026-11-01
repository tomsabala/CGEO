"""Build config for the C++ extension only; all metadata lives in pyproject.toml."""

import sys
from glob import glob

from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

extra_compile_args = ["/O2", "/W3"] if sys.platform == "win32" else ["-O3", "-Wall"]

setup(
    ext_modules=[
        Pybind11Extension(
            "cgeo._cgeo",
            sorted(glob("src/**/*.cpp", recursive=True)),
            include_dirs=["src"],
            define_macros=[("EXTENSION_NAME", "_cgeo")],
            cxx_std=17,
            extra_compile_args=extra_compile_args,
        )
    ],
    cmdclass={"build_ext": build_ext},
)
