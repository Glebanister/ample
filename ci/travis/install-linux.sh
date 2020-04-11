#!/bin/bash
echo toolchain
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test

sudo apt install software-properties-common

sudo apt-get update

sudo apt-get install g++-7 > output
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 40
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 40

g++ --version
gcc --version

sudo apt-get install build-essential checkinstall

CMAKE_VERSION=3.17.0
CMAKE_VERSION_DIR=v3.17

CMAKE_OS=Linux-x86_64
CMAKE_TAR=cmake-$CMAKE_VERSION-$CMAKE_OS.tar.gz
CMAKE_URL=http://www.cmake.org/files/$CMAKE_VERSION_DIR/$CMAKE_TAR
CMAKE_DIR=$(pwd)/cmake-$CMAKE_VERSION

wget --quiet $CMAKE_URL
mkdir -p $CMAKE_DIR
tar --strip-components=1 -xzf $CMAKE_TAR -C $CMAKE_DIR
export PATH=$CMAKE_DIR/bin:$PATH
rm -rf cmake-$CMAKE_VERSION*

cmake --version

sudo apt-get install libgl1-mesa-dev
sudo apt-get install libglm-dev
sudo apt-get install libgles2-mesa-dev
sudo apt-get install libegl1-mesa-dev
sudo apt-get install libsdl2-dev
sudo apt-get install libdevil1c2 libdevil-dev
sudo apt-get install libglew-dev
