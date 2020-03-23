#pragma once

#include <vector>

namespace ample::activity
{
class Behaviour
{
public:
    void addBehaviour(Behaviour &act);
    virtual ~Behaviour() = default;

    virtual void onAwake();
    virtual void onStart();
    virtual void onActive();
    virtual void onStop();
    virtual void onDestroy();
    virtual void onKill();
    virtual void onPause();

protected:
    std::vector<Behaviour *> _behaviours;
};
} // namespace ample::activity
