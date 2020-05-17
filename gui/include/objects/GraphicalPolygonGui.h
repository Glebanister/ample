#pragma once

#include <memory>

#include "ample/GraphicalPolygon.h"
#include "ample/NamedObject.h"

#include "objects/ObjectGui.h"

namespace ample::gui
{
class ObjectGui;
class GraphicalPolygonGui : public ObjectGui
{
public:
    GraphicalPolygonGui(std::shared_ptr<filing::NamedObject>);
    GraphicalPolygonGui();

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
    std::shared_ptr<graphics::GraphicalPolygon> _polygon;

    char nameBuffer[255];
    
};
} // namespace ample::gui
