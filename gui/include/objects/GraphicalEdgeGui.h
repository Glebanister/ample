#pragma once

#include <memory>

#include "ample/GraphicalEdge.h"
#include "ample/NamedObject.h"

#include "objects/ObjectGui.h"

namespace ample::gui
{
class GraphicalEdgeGui : public ObjectGui
{
public:
    GraphicalEdgeGui(std::shared_ptr<filing::NamedObject>);
    GraphicalEdgeGui();

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
    std::shared_ptr<graphics::GraphicalEdge> _edge;

    char nameBuffer[255];
    
};
} // namespace ample::gui
