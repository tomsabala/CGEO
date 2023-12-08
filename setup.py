import os
import sys
DIR = os.path.abspath(os.path.dirname(__file__))
sys.path.append(os.path.join(DIR, "extern", "pybind11"))

from glob import glob
from setuptools import setup, find_packages
from pybind11.setup_helpers import Pybind11Extension, build_ext  # noqa: E402

del sys.path[-1]
pkg_name = 'cgeo'
ext_name = '_cgeo'
__version__ = '0.1.2'
__longDescription__ = open("README.md").read()

# don't forget to maintain while adding more modules
__pyModules__ = ['Point2D', 'Circle', 'Polygon', 'Segment2D', 'Triangle']

def srcFiles(directory):
    pattern = directory + '/**/*.cpp'
    return sorted(glob(pattern, recursive=True))

setup(
    name=pkg_name,
    version=__version__,

    description='Open source package for computational geometry',
    long_description_content_type='text/markdown',
    long_description=__longDescription__,

    author='Tom Sabala',
    author_email='sabala144@gmail.com',

    packages=find_packages(),
    package_data={pkg_name: ['./**.*']},
    py_modules=__pyModules__,

    ext_modules=[
        Pybind11Extension(
            name= '{}.{}'.format(pkg_name, ext_name),
            include_dirs=['./src'],
            sources=srcFiles('src'),
            define_macros=[('EXTENSION_NAME', ext_name)],
            extra_compile_args = ['-O3', '-Wall'],
        ),
    ],

    cmdclass={"build_ext": build_ext},

    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: GNU General Public License (GPL)",
        "Operating System :: Unix",
    ],
)