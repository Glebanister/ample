#pragma once

#include <string>

#include "ample/Game2dEditor.h"

namespace ample::gui
{
class ObjectGui
{
public:
    virtual void onCreate() = 0;
    virtual void onSubmitCreate() = 0;
    virtual void onEdit() = 0;
    virtual void onSubmitEdit() = 0;
    virtual void onPreview() = 0;
    virtual void onView() = 0;
    virtual void onInspect() = 0;
    // virtual void onDelete() = 0;

    virtual std::string name() const = 0;
    virtual std::string className() const = 0;
};
} // namespace ample::gui
