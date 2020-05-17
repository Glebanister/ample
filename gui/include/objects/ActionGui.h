#pragma once

#include <memory>

#include "ample/Game2dEditor.h"
#include "ample/StateMachine.h"

#include "ObjectGui.h"

namespace ample::gui
{
class ObjectGui;
class ObjectStorageGui;
class ActionGui : public ObjectGui
{
public:
    ActionGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);
    ActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);

    std::shared_ptr<game::Action> getAction();
    void setState(std::shared_ptr<game::StateMachine::State>) noexcept;
    std::shared_ptr<game::StateMachine::State> getState() const noexcept;

protected:
    std::shared_ptr<game::game2d::Game2dEditor> _game2dEditor;
    ObjectStorageGui *_objectStorageGui;
    std::shared_ptr<game::Action> _baseActionPointer;
    std::shared_ptr<game::StateMachine::State> _state;
};
} // namespace ample::gui
