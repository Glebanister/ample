#include "ImguiActivity.h"
#include "ample/Window.h"
#include "ample/Game2d.h"
#include "ample/EventManager.h"
#include "ample/Camera.h"
#include "ample/LightSource.h"
#include "ample/Behaviour.h"
#include "ample/WorldObject2d.h"

#include "Observer.h"

namespace ample::gui
{

class AnimationSwapper : public ample::activity::Behavior
{
public:
    AnimationSwapper(ample::graphics::Texture *texture, size_t delta)
        : delta(delta), texture(texture)
    {
    }

    void onActive() override
    {
        ample::activity::Behavior::onActive();
        auto curTime = ample::time::Clock::globalTimeMs();
        if (curTime - lastTime > delta)
        {
            texture->nextFrame();
            lastTime = curTime;
        }
    }

private:
    size_t delta;
    ample::graphics::Texture *texture;
    size_t lastTime = 0;
};

class AmpleGui : public ImguiActivity
{
public:
    AmpleGui(ample::window::Window &window);
    void onResize() override;

private:
    void drawInterface() override;

    std::shared_ptr<ample::physics::WorldObject2d> object;
    gui::Observer _observer;
    std::shared_ptr<ample::graphics::Texture> texture;
    std::shared_ptr<AnimationSwapper> swapper;
};
} // namespace ample::gui
