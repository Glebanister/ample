#!/bin/bash
echo toolchain
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test > output
echo apt-get update
sudo apt-get update > output
echo g++
sudo apt-get install g++-7 > output
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 40 > output
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 40 > output

g++ --version
gcc --version

echo checkinstall
sudo apt-get install build-essential checkinstall > output

echo cmake
CMAKE_VERSION=3.3.2
CMAKE_VERSION_DIR=v3.3

CMAKE_OS=Linux-x86_64
CMAKE_TAR=cmake-$CMAKE_VERSION-$CMAKE_OS.tar.gz
CMAKE_URL=http://www.cmake.org/files/$CMAKE_VERSION_DIR/$CMAKE_TAR
CMAKE_DIR=$(pwd)/cmake-$CMAKE_VERSION

wget --quiet $CMAKE_URL
mkdir -p $CMAKE_DIR
tar --strip-components=1 -xzf $CMAKE_TAR -C $CMAKE_DIR > output
export PATH=$CMAKE_DIR/bin:$PATH
rm -rf cmake-$CMAKE_VERSION*

cmake --version

echo libraries
sudo apt-get install libgl1-mesa-dev > output
sudo apt install libglm-dev > output
sudo apt install libgles2-mesa-dev > output
sudo apt install libegl1-mesa-dev > output
sudo apt install libsdl2-dev > output

echo python
sudo apt-get install python3 > output
rm -rf output