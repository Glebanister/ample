#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Action.h"
#include "Behaviour.h"
#include "NamedStoredObject.h"
#include "StateMachine.h"

namespace ample::game
{
template <typename ObjectT>
class ObjectOwner
{
public:
    ObjectOwner(std::shared_ptr<ObjectT> object);
    ObjectT &object() noexcept;
    std::shared_ptr<ObjectT> objectPtr() const noexcept;

private:
    std::shared_ptr<ObjectT> _object;
};

class ControlledObject : public activity::Behavior, public filing::NamedStoredObject
{
public:
    template <typename ObjectT>
    class ObjectState : public StateMachine::State, public ObjectOwner<ObjectT>
    {
    public:
        ObjectState(const std::string &name, std::shared_ptr<ObjectT> object);

    private:
        friend class ControlledObject;

    public:
        class ObjectAction : public Action, public ObjectOwner<ObjectT>
        {
        public:
            ObjectAction(const std::string &name,
                         const std::string &className,
                         std::shared_ptr<ObjectT> object);

        private:
            friend class ControlledObject;
        };
    };

public:
    ControlledObject(const std::string &name, const std::string &className);
    ControlledObject(const filing::JsonIO &input);
    std::string dump() override;
    StateMachine &stateMachine() noexcept;
    std::shared_ptr<StateMachine::State> idleState() const noexcept;

private:
    std::shared_ptr<StateMachine> _stateMachine;
    std::shared_ptr<StateMachine::State> _idle;
};
} // namespace ample::game

#include "templates/ControlledObject.hpp"
