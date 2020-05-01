#pragma once

#include <functional>

#include "GraphicalObject.h"
#include "ObjectGroupAction.h"

namespace ample::game::stateMachine::actions
{
class GraphicalAction : public ObjectGroupAction<graphics::GraphicalObject>
{
public:
    GraphicalAction(const std::string &name,
                    const std::string &className,
                    const std::vector<std::string> &bodyNames,
                    const std::function<void(std::shared_ptr<graphics::GraphicalObject>)> &function);
    GraphicalAction(const filing::JsonIO &input);
    void onActive() override;

private:
    std::function<void(std::shared_ptr<graphics::GraphicalObject>)> _f;
};
} // namespace ample::game::stateMachine::actions
