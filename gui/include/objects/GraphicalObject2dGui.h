#pragma once

#include <memory>

#include "ample/GraphicalObject2d.h"
#include "ample/NamedObject.h"

#include "objects/ObjectGui.h"

namespace ample::gui
{
class GraphicalObject2dGui : public ObjectGui
{
public:
    GraphicalObject2dGui(std::shared_ptr<filing::NamedObject>);
    GraphicalObject2dGui();

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
    std::shared_ptr<graphics::GraphicalObject2d> _object;

    char nameBuffer[255];
    
};
} // namespace ample::gui
