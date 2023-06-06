#!/bin/env zsh

source_dir=`pwd`
script_dir=`dirname ${0}`

mkdir -p $script_dir/bin-utils

cd $script_dir/bin-utils

# Download WebAssembly binary tools
if [ ! -d wabt ] ; then
  git clone --recursive https://github.com/WebAssembly/wabt
  cd wabt
else
  cd wabt
  git pull
  git submodule update --init --recursive
fi
cmake -S . -B build
make -C build -j
cd $script_dir

# Download LLVM-WebAssembly backend
if [ ! -d emsdk ] ; then
  git clone --recursive https://github.com/emscripten-core/emsdk
  cd emsdk
else
  cd emsdk
  git pull
  git submodule update --init --recursive
fi
./emsdk install latest
./emsdk activate latest
cd $source_dir

# Set up environment variables.
source $source_dir/setup.sh
