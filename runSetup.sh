#!/bin/bash

rm -r dist/
mkdir dist

python3 setup.py build_ext -bin
sudo python3 setup.py develop
sudo python3 setup.py sdist
