#pragma once

#include <vector>

namespace ample::activity
{
class Behavior
{
public:
    void addBehaviour(Behavior &act);
    virtual ~Behavior() = default;

    virtual void onAwake();
    virtual void onStart();
    virtual void onActive();
    virtual void onStop();
    virtual void onDestroy();
    virtual void onKill();
    virtual void onPause();

protected:
    std::vector<Behavior *> _behaviours;
};
} // namespace ample::activity
