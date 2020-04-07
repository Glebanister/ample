#pragma once

#include <vector>
#include <memory>

namespace ample::activity
{
class Behavior
{
public:
    virtual void onAwake();
    virtual void onStart();
    virtual void onActive();
    virtual void onStop();
    virtual void onDestroy();
    virtual void onKill();
    virtual void onPause();

    void addBehavior(std::shared_ptr<Behavior>);
    void removeBehavior(std::shared_ptr<Behavior>);

    virtual ~Behavior() = default;

protected:
    std::vector<std::shared_ptr<Behavior>> _behaviours;
};
} // namespace ample::activity
