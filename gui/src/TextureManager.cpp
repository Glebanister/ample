#include <sstream>

#include "ample/Debug.h"

#include "TextureManager.h"

namespace ample::gui
{

TextureManager::TextureManager()
{
    rawTexture.fileDialog.SetTitle("Select texture path");
    rawTexture.fileDialog.SetTypeFilters({".png", ".jpg", ".jpeg", ".bmp"});
}

void TextureManager::TexturesList()
{

    for (size_t i = 0; i < _textures.size(); ++i)
    {
        if (ImGui::TreeNode(_textures[i]->name().c_str()))
        {
            ImGui::Text("Path: %s", _textures[i]->path().c_str());
            ImGui::Text("Size: %dx%d", _textures[i]->getWidth(), _textures[i]->getHeight());
            ImGui::Text("Preview:");
            ImGui::SameLine();
            ImGui::Image((void *)(intptr_t)_textures[i]->getCurrentTexture().glTextureId(),
                         ImVec2(64, 64));
            ImGui::TreePop();
        }
    }
}

void TextureManager::TextureLoader()
{
    if (ImGui::Button("Path"))
    {
        rawTexture.fileDialog.Open();
    }
    ImGui::SameLine();
    ImGui::Text("%s", rawTexture.pathBuffer.c_str());
    ImGui::InputText("Name", rawTexture.name, 255);
    ImGui::InputScalar("Width", ImGuiDataType_U32, &rawTexture.eachSize.x, &rawTexture.eachSizeStep);
    ImGui::InputScalar("Height", ImGuiDataType_U32, &rawTexture.eachSize.y, &rawTexture.eachSizeStep);
    ImGui::InputScalar("X", ImGuiDataType_U32, &rawTexture.startPosition.x, &rawTexture.startPositionStep);
    ImGui::InputScalar("Y", ImGuiDataType_U32, &rawTexture.startPosition.y, &rawTexture.startPositionStep);
    ImGui::InputScalar("Frames X", ImGuiDataType_U32, &rawTexture.framesCount.x, &rawTexture.framesCountStep);
    ImGui::InputScalar("Frames Y", ImGuiDataType_U32, &rawTexture.framesCount.y, &rawTexture.framesCountStep);
    ImGui::Combo("Pixel format", &rawTexture.curFormat, rawTexture.format, IM_ARRAYSIZE(rawTexture.format));
    ImGui::Combo("Playback", &rawTexture.curPlayback, rawTexture.playback, IM_ARRAYSIZE(rawTexture.playback));
    ImGui::Combo("Origin X", &rawTexture.curOriginX, rawTexture.textureOrigin, IM_ARRAYSIZE(rawTexture.textureOrigin));
    ImGui::Combo("Origin Y", &rawTexture.curOriginY, rawTexture.textureOrigin, IM_ARRAYSIZE(rawTexture.textureOrigin));

    if (ImGui::Button("Upload"))
    {
        graphics::channelMode pixelFormat = graphics::channelMode::RGB;
        graphics::texturePlayback playback = graphics::texturePlayback::NORMAL;
        graphics::Vector2d<graphics::textureOrigin> origin = {graphics::textureOrigin::NORMAL, graphics::textureOrigin::NORMAL};
        if (rawTexture.curFormat == 1)
        {
            pixelFormat = graphics::channelMode::RGBA;
        }
        if (rawTexture.curPlayback == 1)
        {
            playback = graphics::texturePlayback::REVERSED;
        }
        if (rawTexture.curPlayback == 2)
        {
            playback = graphics::texturePlayback::BOOMERANG;
        }
        if (rawTexture.curOriginX == 1)
        {
            origin.x = graphics::textureOrigin::REVERSED;
        }
        if (rawTexture.curOriginY == 1)
        {
            origin.y = graphics::textureOrigin::REVERSED;
        }
        std::string path(rawTexture.pathBuffer);
        std::string name(rawTexture.name);
        try
        {
            auto texture = std::make_shared<graphics::Texture>(graphics::TextureRaw{path,
                                                                                    name,
                                                                                    rawTexture.eachSize,
                                                                                    rawTexture.startPosition,
                                                                                    rawTexture.framesCount,
                                                                                    pixelFormat,
                                                                                    playback,
                                                                                    rawTexture.total,
                                                                                    origin});
            _textures.push_back(texture);
            rawTexture.success = true;
        }
        catch (const std::exception &e)
        {
            ImGui::OpenPopup("Unable to load texture");
            rawTexture.errorString = e.what();
        }
    }
    if (ImGui::BeginPopupModal("Unable to load texture", NULL))
    {
        ImGui::Text("%s", rawTexture.errorString.c_str());
        if (ImGui::Button("Close"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Close") || rawTexture.success)
    {
        rawTexture.success = false;
        ImGui::CloseCurrentPopup();
    }
    rawTexture.fileDialog.Display();
    if (rawTexture.fileDialog.HasSelected())
    {
        rawTexture.pathBuffer = rawTexture.fileDialog.GetSelected();
        rawTexture.fileDialog.ClearSelected();
    }
}

void TextureManager::drawInterface()
{
    TexturesList();
    if (ImGui::Button("Upload new texture"))
    {
        ImGui::OpenPopup("Texture loader");
    }
    if (ImGui::BeginPopupModal("Texture loader", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        TextureLoader();
        ImGui::EndPopup();
    }
}

std::vector<std::shared_ptr<ample::graphics::Texture>> TextureManager::textures() noexcept
{
    return _textures;
}
} // namespace ample::gui
