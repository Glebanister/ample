# Contributing to ample

First of all, thank you for taking the time to improve the ample! \
Your questions: [ample.engine@gmail.com](mailto:ample.engine@gmail.com)

## Developing branches
  - `master` - always stable branch, all pull requests coming from `development`, when some feauture is ready

  - `development` - mostly stable branch, progress of developing any
    feauture can be shown in it

  - `gui` - GUI branch, all work is in the `gui` folder, GUI is powered
    by imgui library

  - `graphics` - basically work with `OpenGL`

## Code writing
### Sources
All engine sources are placed at `core` folder
  - Headers: `core/include/ample/`

  - Sources: `core/src/`

  - Templates: `core/include/templates/`

Remember, once you add source file, you must add it to the
`core/CMakeLists.txt`.\
If you want to add some class you should find out what is it
about and add it to the one of `src/` folders.

### Style
Engine is written in `C++`, here is our preffered style
```cpp
// CamelCase.h

#pragma once

#include <somesystemheader>
#include <andonemore>

#include "LocalHeader.h"
#include "OneMoreLocalHeaderInCamelCase.h"

namespace ample::example
{
enum params
{
    PARAM1,
    PARAM2,
};

class CamelCase final : public Camel, protected Case
{
public:
    class PublicCamelCaseClass
    {
    };

private:
    class PrivateCamelCaseClass
    {
    };

public:
    CamelCase() = default;
    CamelCase(const std::string &name,
              const std::vector<int> &values);

private:
    const std::string _name;
    const std::vector<int> _values;
};
} // namespace ample::example
```

```cpp
// CamelCase.cpp

#include <somesystemheader>
#include <andonemore>

#include "CamelCase.h"
#include "LocalHeader.h"
#include "OneMoreLocalHeaderInCamelCase.h"

namespace ample::example
{

CamelCase::CamelCase(const std::string &name,
                     const std::vector<int> &values)
    : Camel("hello"),
      Case(1, 2, 3),
      _name(name),
      _values(values)
{
}

} // namespace ample::example

```

### For example
I want to implement projector light source
- If i have any questions,
i would ask [ample.engine@gmail.com](mailto:ample.engine@gmail.com) to
help me

- Fork this repo

- Then i will go to the `graphics branch`, checkout my own
branch, which i will name `graphics-light-projector`

- Create `ample/core/src/Graphics/Light/LightSourceProjector.cpp`
    and `ample/core/include/ample/LightSourceProjector.h`

- Add `src/Graphics/Light/LightSourceProjector.cpp` to the
`core/CMakeLists.txt`

- Implement my idea

- Create pull request to the `graphics` branch with explanation
    of my job
