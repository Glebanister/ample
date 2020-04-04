#include "ImguiActivity.h"
#include "ample/Window.h"
#include "ample/Game2d.h"
#include "ample/EventManager.h"
#include "ample/Camera.h"
#include "ample/LightSource.h"
#include "ample/Behaviour.h"

class KeyboardControlCamera : public ample::activity::Behaviour
{
public:
    KeyboardControlCamera(ample::control::EventManager &manager, ample::graphics::Camera &camera)
        : _manager(manager), _camera(camera)
    {
    }

    void onActive() override
    {
        if (_manager.keyboard().isKeyDown(ample::control::keysym::KEY_d))
        {
            _camera.moveRight(1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::KEY_a))
        {
            _camera.moveRight(-1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::ARROW_UP))
        {
            _camera.rotateUp(1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::ARROW_DOWN))
        {
            _camera.rotateUp(-1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::KEY_w))
        {
            _camera.moveForward(1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::KEY_s))
        {
            _camera.moveForward(-1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::ARROW_LEFT))
        {
            _camera.rotateRight(-1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::ARROW_RIGHT))
        {
            _camera.rotateRight(1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::COMMA))
        {
            _camera.rotateForward(-1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::PERIOD))
        {
            _camera.rotateForward(1);
        }
        _camera.rotateRight(-_manager.mouse().getMouseXRel() / (1.0 / 0.1));
        _camera.rotateUp(-_manager.mouse().getMouseYRel() / (1.0 / 0.1));
        _lamp.setTranslate({_camera.getX(), _camera.getY(), _camera.getZ()});

        if (_manager.keyboard().isKeyDown(ample::control::keysym::NUM_1))
        {
            _lamp.addIntensitiy({-10, 0, 0});
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::NUM_2))
        {
            _lamp.addIntensitiy({10, 0, 0});
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::NUM_3))
        {
            _lamp.addIntensitiy({0, -10, 0});
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::NUM_4))
        {
            _lamp.addIntensitiy({0, 10, 0});
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::NUM_5))
        {
            _lamp.addIntensitiy({0, 0, -10});
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::NUM_6))
        {
            _lamp.addIntensitiy({0, 0, 10});
        }
    }

    ample::graphics::light::LightSource &getLamp()
    {
        return _lamp;
    }

protected:
    ample::control::EventManager &_manager;
    ample::graphics::light::LightSource _lamp;
    ample::graphics::Camera &_camera;
};

namespace ample::gui
{

class AnimationSwapper : public ample::activity::Behaviour
{
public:
    AnimationSwapper(ample::graphics::Texture *texture, size_t delta)
        : delta(delta), texture(texture)
    {
    }

    void onActive() override
    {
        ample::activity::Behaviour::onActive();
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

private:
    void drawInterface() override;

    ample::graphics::GraphicalObject2d object;
    std::shared_ptr<KeyboardControlCamera> cameraRemote;
    std::shared_ptr<ample::graphics::Texture> texture;
    std::shared_ptr<AnimationSwapper> swapper;
};
} // namespace ample::gui
