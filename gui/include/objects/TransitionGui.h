#pragma once

#include "ample/Game2dEditor.h"
#include "ample/StateMachine.h"
#include "ample/Level.h"

#include "ObjectGui.h"

namespace ample::gui
{
class ObjectGui;
class ObjectStorageGui;
class TransitionGui : public ObjectGui
{
public:
    TransitionGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);
    TransitionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);

    void onCreate() override;

    void presetStateMachine(std::shared_ptr<game::StateMachine>) noexcept;
    void presetNextState(std::shared_ptr<game::StateMachine::State>) noexcept;

    std::shared_ptr<game::StateMachine::Transition> getBaseTransition() const noexcept;

protected:
    std::shared_ptr<game::game2d::Game2dEditor> _game2dEditor;
    ObjectStorageGui *_objectStorageGui;
    std::shared_ptr<game::StateMachine::Transition> _baseTransition = nullptr;

    std::shared_ptr<game::game2d::Level> _level = nullptr;
    std::shared_ptr<game::StateMachine> _stateMachine = nullptr;
    std::shared_ptr<game::StateMachine::State> _nextState = nullptr;
    bool _levelPresetted = false;
    bool _stateMachinePresetted = false;
    bool _nextStatePresetted = false;
};
} // namespace ample::gui
