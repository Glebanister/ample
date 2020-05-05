#pragma once

#include <memory>

#include <imgui.h>
#include <imfilebrowser.h>

#include "ample/Texture.h"
#include "ample/Singleton.h"

#include "InterfaceUnit.h"

namespace ample::gui
{
class TextureManager : public InterfaceUnit<TextureManager>
{
public:
    TextureManager();
    void TexturesList();
    void TextureLoader();

    struct RawTexture
    {
        std::string pathBuffer;
        char name[255];

        ImGui::FileBrowser fileDialog;

        graphics::Vector2d<size_t> eachSize = {128, 128};
        size_t eachSizeStep = 1;

        graphics::Vector2d<int> startPosition = {0, 0};
        size_t startPositionStep = 1;

        graphics::Vector2d<size_t> framesCount = {1, 1};
        size_t framesCountStep = 1;

        const char *format[2] = {"RGB", "RGBA"};
        int curFormat = 0;

        const char *playback[3] = {"normal", "reversed", "boomerang"};
        int curPlayback = 0;

        size_t total = 0;
        size_t totalStep = 1;

        const char *textureOrigin[2] = {"normal", "reversed"};
        int curOriginX = 0, curOriginY = 0;

        bool success = false;
        std::string errorString;
    };

public:
    void drawInterface() override;
    std::vector<std::shared_ptr<ample::graphics::Texture>> textures() noexcept;

private:
    std::vector<std::shared_ptr<ample::graphics::Texture>> _textures;
    RawTexture rawTexture;
};
} // namespace ample::gui
