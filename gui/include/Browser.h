#pragma once

#include <memory>

#include "ample/NamedObject.h"

#include "InterfaceUnit.h"
#include "TabBrowser.h"

namespace ample::gui
{
class Browser : public InterfaceUnit<Browser>
{
public:
    void drawInterface() override;
    void openBrowserTab(std::shared_ptr<filing::NamedObject>);

private:
    std::vector<std::unique_ptr<TabBrowser>> _openedBrowsers;
    size_t _openedBrowserId;
};
} // namespace ample::gui
