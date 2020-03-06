#pragma once

#include <vector>

namespace ample::activity
{
class Behaviour
{
public:
    void addBehaviour(Behaviour &act);

    virtual ~Behaviour() = default;

protected:
    virtual void onAwake();
    virtual void onStart();
    virtual void onActive();
    virtual void onStop();
    virtual void onDestroy();

    std::vector<Behaviour *> _behaviours;
};
} // namespace ample::activity
