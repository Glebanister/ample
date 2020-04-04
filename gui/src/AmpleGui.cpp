#include "ImguiActivity.h"
#include "AmpleGui.h"
#include "ample/RegularPolygon.h"
#include "ample/WorldObject2d.h"

namespace ample::gui
{
AmpleGui::AmpleGui(ample::window::Window &window)
    : ImguiActivity(window),
      _observer(eventManager())
{
    auto &level = createLevel(1, 10.0f, 0.5f);
    object = std::make_shared<ample::physics::WorldObject2d>(level.frontSlice(),
                                                             physics::BodyType::STATIC_BODY,
                                                             ample::geometry::RegularPolygon<float>(10.0f, 7),
                                                             1.0f,
                                                             0.0f,
                                                             graphics::Vector2d<float>{1.0f, 1.0f},
                                                             graphics::Vector2d<float>{1.0f, 1.0f},
                                                             graphics::normalsMode::FACE);
    // level.frontSlice().addObject(object);
    // auto obj = std::make_shared<ample::physics::WorldObject2d>(level.frontSlice(), physics::BodyType::STATIC_BODY, {{1.0f, 1.0f}}, 10.0f, 0.0f, {1.0f, 1.0f}, {1.0f, 1.0f}, graphics::normalsMode::FACE, {0.0f, 0.0f}, 0.0f);
    // object = std::make_shared(obj);
    setCurrentLevel(1);
    addBehaviour(_observer);
    level.camera().setVisibility(false);
    level.frontSlice().addCamera(_observer.getCamera());
    level.frontSlice().addObject(_observer.getLamp());
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
    object->face().bindTexture(texture);
    object->side().bindTexture(texture);
    object->bindTexture(texture);

    swapper = std::make_shared<AnimationSwapper>(texture.get(), 15);
    addBehaviour(*swapper);
}

void AmpleGui::onResize()
{
    ImguiActivity::onResize();
    _observer.onWindowResized({static_cast<int>(getWidth()), static_cast<int>(getHeight())});
}

void AmpleGui::drawInterface()
{
    ImGui::Begin("Slices");
    ImGui::End();

    ImGui::Begin("Preview");
    ImGui::End();

    ImGui::Begin("Levels");
    ImGui::End();

    ImGui::Begin("Editor");
    ImGui::End();
}
} // namespace ample::gui
