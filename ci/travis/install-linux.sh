#!/bin/bash
echo toolchain
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test > output

echo software-properties-common
sudo apt install software-properties-common > output

# echo ppa:deadsnakes/ppa
# sudo add-apt-repository ppa:deadsnakes/ppa > output

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
sudo apt-get install libglm-dev > output
sudo apt-get install libgles2-mesa-dev > output
sudo apt-get install libegl1-mesa-dev > output
sudo apt-get install libsdl2-dev > output

echo python3
sudo apt-get install python3.6 > output
sudo update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.6 1 > output
sudo update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.7 2 > output
sudo update-alternatives --config python3 > output
python3 --version

echo pip3
sudo apt install python3-pip > output

echo linters
pip3 install --user pytest pytest-cov pytest-mock flake8 pep8-naming flake8-quotes mypy pylint > output
sudo apt install pylint3 > output
pylint --version

rm -rf output
