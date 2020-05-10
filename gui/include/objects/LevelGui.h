#pragma once

#include <memory>

#include "ample/Game2dEditor.h"
#include "ample/Level.h"
#include "ample/NamedObject.h"

#include "Observer.h"
#include "objects/ObjectGui.h"

namespace ample::gui
{
class Observer;
class ObjectGui;
class LevelGui : public ObjectGui
{
public:
    LevelGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor>, ObjectStorageGui *);
    LevelGui(std::shared_ptr<game::game2d::Game2dEditor>, ObjectStorageGui *);

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
    std::shared_ptr<game::game2d::Game2dEditor> _game2dEditor;
    ObjectStorageGui *_objectStorageGui;

    std::shared_ptr<game::game2d::Level> _level;
    std::shared_ptr<game::LevelLoader> _loader;

    char nameBuffer[255] = {0};
    float thickness = 20.0f;
    float physicsLayerPos = 20.0f;
    graphics::Vector2d<float> gravity;
    Observer _observer;
};
} // namespace ample::gui
