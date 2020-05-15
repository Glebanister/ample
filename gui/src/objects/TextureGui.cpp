#include <imgui.h>
#include <unordered_map>

#include "Utils.h"
#include "ample/Utils.h"

#include "objects/TextureGui.h"

namespace ample::gui
{
TextureGui::TextureGui(std::shared_ptr<filing::NamedObject> texture, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _texture(std::dynamic_pointer_cast<graphics::Texture>(texture)),
      _game2dEditor(editor),
      _objectStorageGui(storage)
{
    ASSERT(_game2dEditor);
}

TextureGui::TextureGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor),
      _objectStorageGui(storage)
{
    ASSERT(_game2dEditor);
}

std::unordered_map<std::string, graphics::textureOrigin> originByName{
    {"normal", graphics::textureOrigin::NORMAL},
    {"reversed", graphics::textureOrigin::REVERSED},
};

std::unordered_map<std::string, graphics::texturePlayback> playbackByName{
    {"normal", graphics::texturePlayback::NORMAL},
    {"reversed", graphics::texturePlayback::REVERSED},
    {"boomerang", graphics::texturePlayback::BOOMERANG},
};

std::unordered_map<std::string, graphics::channelMode> modeByName{
    {"rgb", graphics::channelMode::RGB},
    {"rgba", graphics::channelMode::RGBA},
};

void TextureGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    gui_utils::PathSelector("Path", texturePath, _filebrowser);
    gui_utils::InputCoordinates("Frame size", eachSize.x, eachSize.y, 1U);
    gui_utils::InputCoordinates("Start position", startPosition.x, startPosition.y, 1);
    gui_utils::InputCoordinates("Frames count", framesCount.x, framesCount.y, 1U);
    gui_utils::StringSelector("Format", format, {"rgb", "rgba"});
    gui_utils::StringSelector("Playback", playback, {"normal", "reversed", "boomerang"});
    gui_utils::InputScalar("Total frames", total, 1U);
    gui_utils::StringSelector("Origin x", originX, {"normal", "reversed"});
    gui_utils::StringSelector("Origin y", originY, {"normal", "reversed"});
}

void TextureGui::onSubmitCreate()
{
    _texture = std::make_shared<graphics::Texture>(
        graphics::TextureRaw(
            texturePath,
            std::string(nameBuffer),
            {eachSize.x, eachSize.y},
            {startPosition.x, startPosition.y},
            {framesCount.x, framesCount.y},
            modeByName[format],
            playbackByName[playback],
            total,
            {originByName[originX], originByName[originY]}));
    _objectStorageGui->texturesList().push_back(_texture);
}

void TextureGui::onEdit()
{
    ASSERT(_texture);
}

void TextureGui::onSubmitEdit()
{
}

graphics::Vector2d<float> fitSize(graphics::Vector2d<float> tex, graphics::Vector2d<float> win)
{
    if (win.x / win.y < tex.x / tex.y)
    {
        tex.y = (tex.y / tex.x) * win.x;
        tex.x = win.x;
    }
    else
    {
        tex.x = (tex.x / tex.y) * win.y;
        tex.y = win.y;
    }
    return tex;
}

void TextureGui::onView()
{
    auto texSize = fitSize({static_cast<float>(_texture->getWidth()), static_cast<float>(_texture->getHeight())},
                           {ImGui::GetWindowWidth(), ImGui::GetWindowHeight()});
    ImGui::Image((void *)(intptr_t)_texture->getCurrentTexture().glTextureId(),
                 ImVec2(texSize.x, texSize.y));
}

void TextureGui::onInspect()
{
}

void TextureGui::onPreview()
{
    ImGui::Separator();
    ImGui::Columns(2);
    ImGui::Text("Name: %s", _texture->name().c_str());
    ImGui::Text("Size: %dx%d", _texture->getWidth(), _texture->getHeight());
    ImGui::NextColumn();
    auto texSize = fitSize({static_cast<float>(_texture->getWidth()), static_cast<float>(_texture->getHeight())},
                           {64.0f, 64.0f});
    ImGui::Image((void *)(intptr_t)_texture->getCurrentTexture().glTextureId(),
                 ImVec2(texSize.x, texSize.y));
    ImGui::NextColumn();
}

std::string TextureGui::name() const
{
    ASSERT(_texture);
    return _texture->name();
}
std::string TextureGui::className() const
{
    return "Texture";
}
} // namespace ample::gui
