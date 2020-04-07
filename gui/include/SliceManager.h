#pragma once

#include "ample/Singleton.h"
#include "ample/WorldLayer2d.h"
#include "ample/Level.h"

#include "InterfaceUnit.h"

namespace ample::gui
{
class SliceManager : public InterfaceUnit, public utils::Singleton<SliceManager>
{
public:
    void drawInterface() override;
    void setLevel(std::shared_ptr<game::game2d::Level>);

private:
    struct TextureSelector
    {
        std::shared_ptr<graphics::Texture> selectedTexture = nullptr;
    };

    std::shared_ptr<game::game2d::Level> _currentLevel;
};
} // namespace ample::gui
