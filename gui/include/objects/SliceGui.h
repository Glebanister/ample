#pragma once

#include <memory>

#include "ample/Scene2d.h"
#include "ample/NamedObject.h"

#include "objects/ObjectGui.h"

namespace ample::gui
{
class SliceGui : public ObjectGui
{
public:
    SliceGui(std::shared_ptr<filing::NamedObject>);
    SliceGui();

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
    std::shared_ptr<filing::Scene2d> _slice;

    char nameBuffer[255];
    
};
} // namespace ample::gui
