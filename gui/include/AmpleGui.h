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
class AmpleGui : public ImguiActivity
{
public:
    AmpleGui(ample::window::Window &window);
    void onResize() override;

private:
    void drawInterface() override;

    std::shared_ptr<gui::Observer> _observer;
};
} // namespace ample::gui
