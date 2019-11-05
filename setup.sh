#!/bin/bash

printf "If you haven't already, install the required dependencies \u001b[33m(for Ubuntu)\u001b[0m:"

printf "\n\u001b[32msudo apt install python3-pybind11 python3-distutils libpython3.7-dev graphviz\u001b[0m\n"

printf "\nIf you're done, press \u001b[33mENTER\u001b[0m to continue. Otherwise, press \u001b[33mCtrl + C\u001b[0m to close.\n"

read -p ""

printf "Compiling Genesys as a dynamic library..."
(cd genesys && make -f Makefile CONF=Debug clean && make -f Makefile CONF=Debug)

printf "\nMoving 'libgenesys.so' to 'src' folder..."
cp genesys/dist/Debug/GNU-Linux/libgenesys.so src

printf "\nDone."

printf "\nYou can run the project with the following command: \u001b[32mpython3 src/main.py\u001b[0m\n\n"

