#include "ImguiActivity.h"
#include "AmpleGui.h"
#include "ample/RegularPolygon.h"

namespace ample::gui
{
AmpleGui::AmpleGui(ample::window::Window &window)
    : ImguiActivity(window),
      object(ample::geometry::RegularPolygon<float>(10.0, 30),
             10.0f,
             50.0f,
             {1.0f, 1.0f},
             {1.0f, 1.0f},
             ample::graphics::normalsMode::FACE,
             {0.0f, 0.0f},
             0.0f)
{
    auto &level = createLevel(1, 10.0f, 0.5f);
    level.frontSlice().addObject(object);
    setCurrentLevel(1);
    level.camera().translate({0.0, 10.0, 0.0});
    cameraRemote = std::make_shared<KeyboardControlCamera>(eventManager(), level.camera());
    addBehaviour(*cameraRemote);
    level.frontSlice().addObject(cameraRemote->getLamp());
    texture = std::make_shared<ample::graphics::Texture>(ample::graphics::TextureRaw("../../demo/textures/braid.jpg",
                                                                                     {820UL / 7 - 1, 546UL / 4 - 1},
                                                                                     {2L, 2L},
                                                                                     {7, 4},
                                                                                     ample::graphics::channelMode::RGBA,
                                                                                     ample::graphics::texturePlayback::NORMAL,
                                                                                     27,
                                                                                     {
                                                                                         ample::graphics::textureOrigin::REVERSED,
                                                                                         ample::graphics::textureOrigin::REVERSED,
                                                                                     }));
    object.side().bindTexture(texture);
    object.face().bindTexture(texture);

    swapper = std::make_shared<AnimationSwapper>(texture.get(), 15);
    addBehaviour(*swapper);
}

void AmpleGui::drawInterface()
{
    ImguiActivity::drawInterface();
    // ImGui::Begin("Triangle Position/Color");
    // static float rotation = 0.0;
    // ImGui::SliderFloat("rotation", &rotation, 0, 2 * M_PI);
    // static float translation[] = {0.0, 0.0};
    // ImGui::SliderFloat2("position", translation, -1.0, 1.0);
    // ImGui::End();
}
} // namespace ample::gui
