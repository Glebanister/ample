#pragma once

#include <imgui.h>

#include "ample/Singleton.h"

namespace ample::gui
{
class GraphicalInterface
{
public:
    virtual void drawInterface() = 0;
};

template <class T>
class InterfaceUnit : public utils::Singleton<T>, GraphicalInterface
{
};
} // namespace ample::gui
