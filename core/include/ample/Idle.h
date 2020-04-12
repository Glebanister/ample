#pragma once

#include "Action.h"

namespace ample::game
{
class Idle : public Action
{
public:
    Idle(filing::JsonIO input); // TODO
    void onActive() override;
    std::string dump(filing::JsonIO output, const std::string &filedName) override; // TODO
};
} // namespace ample::game
