![travis](https://travis-ci.com/Glebanister/ample.svg?branch=master) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/bfb66781f2fc499ca6bbad09ed5d43c6)](https://app.codacy.com/manual/Glebanister/ample?utm_source=github.com&utm_medium=referral&utm_content=Glebanister/ample&utm_campaign=Badge_Grade_Dashboard)

### Ample - Game engine
3D Graphics, 2D physics.
This is a first year group project of a Saint Petersburg Higher School of Economics.

### Install (Linux)

`$ ./ci/travis/install-linux.sh`  - installs dependencies \
`$ mkdir build && cd build` \
`$ cmake .. -DCMAKE_CXX_COMPILER=g++-9`
`$ make -j4` \ or just make, if you have some time and don't want this process to disturb you


### Create your project (in developing)

`$ ./build/gui/ample-gui`


### Show demo

`$ ./build/demo/demo`
