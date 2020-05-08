#pragma once

#include <memory>

#include "ample/GraphicalObject.h"
#include "ample/NamedObject.h"

#include "objects/ObjectGui.h"

namespace ample::gui
{
class GraphicalObjectGui : public ObjectGui
{
public:
    GraphicalObjectGui(std::shared_ptr<filing::NamedObject>);
    GraphicalObjectGui();

    void onCreate() override;
    void onSubmitCreate() override;
    void onEdit() override;
    void onSubmitEdit() override;
    void onView() override;
    void onInspect() override;
    void onPreview() override;

    std::string name() const override;
    std::string className() const override;

private:
    std::shared_ptr<graphics::GraphicalObject> _object;

    char nameBuffer[255];
    
};
} // namespace ample::gui
