#pragma once

#include <memory>

#include "ample/Game2dEditor.h"
#include "ample/KeyboardTransition.h"

#include "ObjectGui.h"
#include "ObjectStorageGui.h"
#include "TransitionGui.h"

namespace ample::gui
{
class ObjectStorageGui;
class KeyboardTransitionGui : public TransitionGui
{
public:
    KeyboardTransitionGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);
    KeyboardTransitionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);

    void onCreate() override;
    void onSubmitCreate() override;
    void onEdit() override;
    void onSubmitEdit() override;
    void onView() override;
    void onInspect() override;
    void onPreview() override;

    std::string name() const override;
    std::string className() const override;

private:
    std::shared_ptr<game::KeyboardTransition> _transition;
    char nameBuffer[255];
    game::KeyboardTransition::type pressType = game::KeyboardTransition::type::PRESSED;
    std::string key = "";
    control::keysym keycode;
    std::string pressTypeString;
};
} // namespace ample::gui
