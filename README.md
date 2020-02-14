## Ample - little engine

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/bfb66781f2fc499ca6bbad09ed5d43c6)](https://app.codacy.com/manual/Glebanister/ample?utm_source=github.com&utm_medium=referral&utm_content=Glebanister/ample&utm_campaign=Badge_Grade_Dashboard)

Ample engine is a linux-based game engine.

### Engine
2D, physics-friendly

### Project manager
You can create ample directories anywhere, using ample script.

### Install (Linux)

`$ ./ci/travis/install-linux.sh` \
`$ mkdir build && cd build` \
`$ cmake .. && cmake --build`


### Run
`$ cd script`
`$ mkdir [your-project-name] && cd [your-project-name]` \
`$ ../ample.py init [your-project-name]` \
`$ ../ample.py build [your-project-name]` \
`$ ../ample.py run [your-project-name]`

-------
![travis](https://travis-ci.com/Glebanister/ample.svg?branch=master)
