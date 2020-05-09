#pragma once

#include <imgui.h>
#include <memory>

#include <imfilebrowser.h>

#include "ample/Game2dEditor.h"
#include "ample/Level.h"

#include "ample/NamedObject.h"
#include "ample/Scene2d.h"
#include "ample/Texture.h"

#include "ObjectStorageGui.h"
#include "objects/ObjectGui.h"

namespace ample::gui
{
class TextureGui : public ObjectGui
{
public:
    TextureGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor>, ObjectStorageGui *);
    TextureGui(std::shared_ptr<game::game2d::Game2dEditor>, ObjectStorageGui *);

    void onCreate() override;
    void onSubmitCreate() override;
    void onEdit() override;
    void onSubmitEdit() override;
    void onView() override;
    void onInspect() override;
    void onPreview() override;

    std::string name() const override;
    std::string className() const override;

private:
    std::shared_ptr<graphics::Texture> _texture;
    std::shared_ptr<game::game2d::Game2dEditor> _game2dEditor;

    ObjectStorageGui *_objectStorageGui;

    char nameBuffer[255] = {0};
    std::string texturePath;
    graphics::Vector2d<uint32_t> eachSize = {0, 0};
    graphics::Vector2d<int32_t> startPosition = {0, 0};
    graphics::Vector2d<uint32_t> framesCount = {1, 1};
    std::string format = "rgba";
    std::string playback = "normal";
    uint32_t total = 0UL;
    std::string originX = "normal";
    std::string originY = "normal";

    ImGui::FileBrowser _filebrowser;
};
} // namespace ample::gui
