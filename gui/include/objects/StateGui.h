#pragma once

#include <memory>

#include "ample/Game2dEditor.h"
#include "ample/StateMachine.h"

#include "ObjectGui.h"
#include "ObjectStorageGui.h"

namespace ample::gui
{
class ObjectStorageGui;
class ObjectGui;
class StateGui : public ObjectGui
{
public:
    StateGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);
    StateGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);

    void onCreate() override;
    void onSubmitCreate() override;
    void onEdit() override;
    void onSubmitEdit() override;
    void onView() override;
    void onInspect() override;
    void onPreview() override;

    void presetStateMachine(std::shared_ptr<game::StateMachine>) noexcept;

    std::shared_ptr<game::StateMachine::State> getState() const noexcept;

    std::string name() const override;
    std::string className() const override;

private:
    std::shared_ptr<game::game2d::Game2dEditor> _game2dEditor;
    ObjectStorageGui *_objectStorageGui;
    std::shared_ptr<game::StateMachine> _stateMachine;
    std::shared_ptr<game::StateMachine::State> _state;
    char nameBuffer[255] = {0};
    gui_utils::ClassSelector _actionSelector{"Select action class", "Action"};
    int _actionType = 0;
};
} // namespace ample::gui
