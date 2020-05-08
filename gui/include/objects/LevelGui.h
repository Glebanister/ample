#pragma once

#include <memory>

#include "ample/Game2dEditor.h"
#include "ample/Level.h"
#include "ample/NamedObject.h"

#include "Observer.h"
#include "objects/ObjectGui.h"

namespace ample::gui
{
class LevelGui : public ObjectGui
{
public:
    LevelGui(std::shared_ptr<filing::NamedObject>, game::game2d::Game2dEditor *);
    LevelGui(game::game2d::Game2dEditor *);

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
    std::shared_ptr<game::game2d::Level> _level;
    std::shared_ptr<game::LevelLoader> _loader;
    game::game2d::Game2dEditor *_game2dEditor;

    char nameBuffer[255];
    float thickness = 20.0f;
    float physicsLayerPos = 20.0f;
    graphics::Vector2d<float> gravity;
    Observer _observer;
};
} // namespace ample::gui
