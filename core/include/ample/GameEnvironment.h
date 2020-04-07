#pragma once

#include <string>

#include "Singleton.h"
#include "JsonIO.h"

namespace ample::game
{

/*                                                                                              
Every project structre:
.
├── layouts                                 -- main menu, settings, user interface, etc.
│   └── <...>.json
├── levels                                  -- levels list
│   └── level_1
│       ├── behavior.json                   -- current level behavior
│       ├── scenes                          -- all 'slices' of level: foreground, backgrounds
│       │   └── <...>.json
│       └── textures                        -- level textures
│           └── <...>.[png, jpg, jpeg, bmp]
└── settings.json                           -- project settings
*/

class GameEnvironment : public utils::Singleton<GameEnvironment>
{
public:
    GameEnvironment(const std::string &projectAbsolutePath);
    const std::string &projectAbsolutePath() const;

private:
    const std::string _projectAbsolutePath;
};
} // namespace ample::game
