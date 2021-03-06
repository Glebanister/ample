#pragma once

#include <memory>

#include "ample/Game2dEditor.h"
#include "ample/Level.h"

#include "ample/NamedObject.h"
#include "ample/Scene2d.h"

#include "ObjectStorageGui.h"
#include "Observer.h"
#include "objects/ObjectGui.h"

namespace ample::gui
{
class ObjectStorageGui;
class ObjectGui;
class Observer;
class SliceGui : public ObjectGui
{
public:
    SliceGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor>, ObjectStorageGui *);
    SliceGui(std::shared_ptr<game::game2d::Game2dEditor>, ObjectStorageGui *);

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
    std::shared_ptr<game::game2d::Game2dEditor> _game2dEditor;
    std::shared_ptr<game::game2d::Level> _level;

    ObjectStorageGui *_objectStorageGui;

    char nameBuffer[255] = {0};
    int32_t num = 1;
    graphics::Vector2d<float> gravity;

    Observer _observer;
};
} // namespace ample::gui
