from setuptools import setup

from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11 import get_cmake_dir

import sys

__version__ = "0.0.2"


ext_modules = [
    Pybind11Extension(
        "signate131",
        ["src/signate131.cpp"],
        define_macros = [('VERSION_INFO', __version__)],
    ),
]

setup(
    name="signate131",
    version=__version__,
    author="oct_path",
    author_email="",
    url="",
    description="signate131 postprocessing",
    long_description="",
    ext_modules=ext_modules,
    extras_require={},
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
