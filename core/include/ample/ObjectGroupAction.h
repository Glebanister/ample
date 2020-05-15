#pragma once

#include <string>

#include "Action.h"
#include "GameException.h"

namespace ample::game::stateMachine::actions
{
template <typename T>
class ObjectGroupAction : public Action
{
public:
    ObjectGroupAction(const std::string &name,
                      const std::string &className,
                      const std::vector<std::string> &bodyNames);
    ObjectGroupAction(const filing::JsonIO &input);
    std::string dump() override;

    void addObjectName(const std::string &name) noexcept;

    std::vector<std::shared_ptr<T>> &bodyPointers() noexcept;
    std::vector<std::string> &bodyNames() override;

    void onActive() override;

protected:
    std::vector<std::string> _bodyNames;
    std::vector<std::shared_ptr<T>> _bodyPointers;
    void updateObjectPointers();

private:
    std::shared_ptr<T> getObjectPointer(const std::string &name);
    bool _pointersInitialized = false;
};
} // namespace ample::game::stateMachine::actions

#include "templates/ObjectGroupAction.hpp"
