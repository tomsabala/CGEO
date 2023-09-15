#!/bin/bash

mkdir build
cd build
cmake -DBoost_NO_BOOST_CMAKE=TRUE \
      -DBoost_NO_SYSTEM_PATHS=TRUE \
      -DBOOST_ROOT:PATHNAME=${BOOST_DIR} \
      -DBoost_LIBRARY_DIRS:FILEPATH=${BOOST_DIR}/lib ..
make
