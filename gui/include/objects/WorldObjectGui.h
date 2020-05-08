#pragma once

#include <memory>

#include "ample/WorldObject2d.h"

#include "objects/ObjectGui.h"

namespace ample::gui
{
class WorldObjectGui : public ObjectGui
{
public:
    WorldObjectGui(std::shared_ptr<filing::NamedObject>);
    WorldObjectGui();

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
    std::shared_ptr<physics::WorldObject2d> _object;

    char nameBuffer[255];
};
} // namespace ample::gui
