#include "ImguiActivity.h"
#include "ample/Window.h"

namespace ample::gui
{
class AmpleGui : public ImguiActivity
{
public:
    AmpleGui(ample::window::Window &window);

private:
    void presentGui() override;
};
} // namespace ample::gui
