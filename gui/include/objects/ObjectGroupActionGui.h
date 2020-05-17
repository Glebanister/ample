#pragma once

#include <memory>

#include "ample/Game2dEditor.h"
#include "ample/StateMachine.h"

#include "ActionGui.h"

namespace ample::gui
{
class ObjectGui;
class ObjectStorageGui;
template <typename T>
class ObjectGroupActionGui : public ActionGui
{
public:
    ObjectGroupActionGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);
    ObjectGroupActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);

    void onEdit() override;
    void onSubmitEdit() override;
    void onInspect() override;

protected:
    std::shared_ptr<filing::NamedObject> _selectedObjectToAdd;
    std::shared_ptr<game::stateMachine::actions::ObjectGroupAction<T>> _groupAction;
};
} // namespace ample::gui

#include "templates/ObjectGroupActionGui.hpp"
