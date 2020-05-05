#pragma once

#include <imgui.h>

#include "ample/Singleton.h"

namespace ample::gui
{
template <class T>
class InterfaceUnit : public utils::Singleton<T>
{
public:
    virtual void drawInterface() = 0;
};
} // namespace ample::gui
