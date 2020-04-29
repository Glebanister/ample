#pragma once

#include <string>
#include <filesystem>

#include "Singleton.h"
#include "JsonIO.h"

/*
Project structre:
.
├── levels                                  -- levels list
│   └── level_1
│       ├── behavior.json                   -- current level behavior
│       ├── settings.json                   -- current level settings
│       ├── scenes                          -- all 'slices' of level: foreground, backgrounds
│       │   └── <...>.json
│       └── textures                        -- level textures
│           └── <...>.[png, jpg, jpeg, bmp]
└── settings.json                           -- project settings
*/

namespace ample::game
{
class GameEnvironment : public utils::Singleton<GameEnvironment>
{
public:
    std::filesystem::path &projectAbsolutePath();

private:
    std::filesystem::path _projectAbsolutePath;
};
} // namespace ample::game
