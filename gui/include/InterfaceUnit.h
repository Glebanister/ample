#pragma once

#include <imgui.h>

namespace ample::gui
{
class InterfaceUnit
{
public:
    virtual void drawInterface() = 0;
};
} // namespace ample::gui
