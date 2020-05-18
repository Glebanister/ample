![travis](https://travis-ci.com/Glebanister/ample.svg?branch=master) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/bfb66781f2fc499ca6bbad09ed5d43c6)](https://app.codacy.com/manual/Glebanister/ample?utm_source=github.com&utm_medium=referral&utm_content=Glebanister/ample&utm_campaign=Badge_Grade_Dashboard)

### Ample engine
3D Graphics, 2D physics game engine. Does not requires any programming
language knowledge for start. So far works only on Linux, other platforms support is coming. Project is in the developing stage at this moment. You may check out CONTRIBUTING.md if you want to help us :)

### Current feautures
- Static and dynamic physics objects
- Objects texturing
- Single light source
- Game logic is done using state machines
- Graphical user interface

### Coming
- More actions for state machines
- 3D models uploading
- Python scripting
- Windows support

![Level editor](resources/level_editor.png)
![State machine editor](resources/state_machine_editor.png)

### Install (Works on Ubuntu 18.04 for sure)

`$ git clone --recursive https://github.com/Glebanister/ample`
`$ ./ci/travis/install-linux.sh`  - installs dependencies, requires apt. You may want to install them by yourself \
`$ mkdir build && cd build` \
`$ cmake .. -DCMAKE_CXX_COMPILER=g++-9` \
`$ make -j4` or just make, if you have some time and don't want this process to disturb you

If you have any problems with the construction of the project, please write about this in issue.

### Create your project with gui

`$ ./build/gui/ample-gui`

### Run project with executor

`$ ./build/engine/ample-engine -p <your-project-path>`
