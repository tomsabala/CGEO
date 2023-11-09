from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup
from glob import glob

__files__ = sorted(glob("*.cpp"))

__version__ = "0.0.1"

ext_modules = [
    Pybind11Extension(
        "libGeo_2D",
        __files__,
        define_macros=[("VERSION_INFO", __version__)],
    ),
]

__desc__ = "A computational geometry package for basic geometric algorithms. It is built for quick and easy use of well-known performance-oriented algorithms and important data structures in the field of computational geometry in any Python program."

setup(
    name="cgeo",
    version=__version__,
    author="Tom Sabala",
    author_email="sabala144@gmail.com",
    url="https://github.com/tomsabala/CGEO",
    description="A computational geometry lib, written in cpp and pybind11",
    long_description=__desc__,
    ext_modules=ext_modules,
    # extras_require={"test": "pytest"},
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.7",
)
