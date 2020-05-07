#pragma once

#include <memory>

namespace ample::gui
{
template <class ObjectT>
class ObjectGui
{
public:
    virtual void onInput() = 0;
    virtual void onSubmitInput() = 0;
    virtual void onEdit() = 0;
    virtual void onSubmitEdit() = 0;
    virtual void onView() = 0;
    virtual void onBrowse() = 0;

protected:
    std::unique_ptr<ObjectT> _target;
};
} // namespace ample::gui
