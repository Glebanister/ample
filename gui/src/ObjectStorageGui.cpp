#include <functional>
#include <imgui.h>

#include "ObjectStorageGui.h"

namespace ample::gui
{
ObjectStorageGui::ObjectStorageGui(std::shared_ptr<game::game2d::Game2dEditor> editor)
    : _game2dEditor(editor)
{
    for (auto level : editor->getLevelsList())
    {
        buildGuiAndAdd(level);
        //     for (auto &[id, slice] : level->layers())
        //     {
        //         buildGuiAndAdd(slice);
        //         for (auto &object : slice->objects())
        //         {
        //             buildGuiAndAdd(object);
        //         }
        //     }
        //     for (auto &sm : level->stateMachines())
        //     {
        //         buildGuiAndAdd(sm);
        //         std::unordered_map<std::string, bool> used;
        //         std::function<void(std::shared_ptr<game::StateMachine::State>)> dfs =
        //             [&](std::shared_ptr<game::StateMachine::State> curState) {
        //                 ASSERT(curState);
        //                 if (used[curState->name()])
        //                     return;
        //                 used[curState->name()] = true;
        //                 for (const auto &transition : curState->transitions())
        //                 {
        //                     buildGuiAndAdd(transition);
        //                     dfs(transition->getNextState());
        //                 }
        //                 buildGuiAndAdd(curState);
        //                 auto actionAdder = [&](std::vector<std::shared_ptr<game::Action>> &actions) {
        //                     std::for_each(actions.begin(), actions.end(),
        //                                   [&](auto &act) {
        //                                       buildGuiAndAdd(act);
        //                                   });
        //                 };
        //                 actionAdder(curState->getOnStartActions());
        //                 actionAdder(curState->getOnActiveActions());
        //                 actionAdder(curState->getOnStopActions());
        //             };
        //         dfs(sm->getCurrentState());
        //     }
    }
}

void ObjectStorageGui::cancelCreate()
{
    _onInput.reset();
}

std::shared_ptr<ObjectGui> ObjectStorageGui::objectGuiByName(const std::string &name)
{
    auto objIt = _guiByObjectName.find(name);
    if (objIt == _guiByObjectName.end())
    {
        throw game::GameException{"can not find object with name " + name};
    }
    return objIt->second;
}

void ObjectStorageGui::inspectSingleItem(const std::string &name)
{
    inspectSingleItem(objectGuiByName(name));
}

void ObjectStorageGui::inspectSingleItem(std::shared_ptr<ObjectGui> gui)
{
    gui->onPreview();
    if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
    {
        setFocus(std::move(gui));
    }
    gui->onInspect();
}

void ObjectStorageGui::setFocus(std::shared_ptr<ObjectGui> gui)
{
    _focusedGui = gui;
}

void ObjectStorageGui::browser()
{
    ASSERT(_game2dEditor);
    for (auto level : _game2dEditor->getLevelsList())
    {
        if (auto levelGui = objectGuiByName(level->name());
            ImGui::TreeNode(levelGui->name().c_str()))
        {
            inspectSingleItem(levelGui);
            ImGui::TreePop();
        }
    }
}

void ObjectStorageGui::editor()
{
    if (!_focusedGui)
    {
        ImGui::Text("Select object to edit");
        return;
    }
    _onInput->onEdit();
    if (ImGui::Button("Submit"))
    {
        try
        {
            _onInput->onSubmitEdit();
        }
        catch (const std::exception &e)
        {
            _editionFailPopup = {"Edition failed", e.what(), true};
        }
    }
    _editionFailPopup.drawInterface();
}

void ObjectStorageGui::creator()
{
    if (ImGui::Selectable("Level"))
    {
        create(finalObjectClass::LEVEL, _game2dEditor);
    }
    // if (ImGui::Selectable("Slice"))
    // {
    //     create(finalObjectClass::SLICE);
    // }
    // if (ImGui::Selectable("Graphical Object"))
    // {
    //     create(finalObjectClass::GRAPHICAL_OBJECT);
    // }
    // if (ImGui::Selectable("Polygon"))
    // {
    //     create(finalObjectClass::GRAPHICAL_POLYGON);
    // }
    // if (ImGui::Selectable("Edge"))
    // {
    //     create(finalObjectClass::GRAPHICAL_EDGE);
    // }
    // if (ImGui::Selectable("Graphical Object 2d"))
    // {
    //     create(finalObjectClass::GRAPHICAL_OBJECT_2D);
    // }
    // if (ImGui::Selectable("World Object"))
    // {
    //     create(finalObjectClass::WORLD_OBJECT);
    // }
    // if (ImGui::Selectable("State Machine"))
    // {
    //     create(finalObjectClass::STATE_MACHINE);
    // }

    if (!_onInput)
    {
        return;
    }
    ImGui::OpenPopup(("Create new " + _onInput->className()).c_str());
    if (ImGui::BeginPopupModal(("Create new " + _onInput->className()).c_str(),
                               NULL,
                               ImGuiWindowFlags_NoResize |
                                   ImGuiWindowFlags_NoMove |
                                   ImGuiWindowFlags_AlwaysAutoResize))
    {
        _onInput->onCreate();
        if (ImGui::Button("Submit"))
        {
            try
            {
                _onInput->onSubmitCreate();
                _guiByObjectName[_onInput->name()] = _onInput;
                _creationSuccess = true;
            }
            catch (const std::exception &e)
            {
                _creationFailPopup = {"Creation failed", e.what(), true};
            }
        }
        _creationFailPopup.drawInterface();
        ImGui::SameLine();
        if (ImGui::Button("Close") || _creationSuccess)
        {
            cancelCreate();
            ImGui::CloseCurrentPopup();
            _creationSuccess = false;
        }
        ImGui::EndPopup();
    }
}

void ObjectStorageGui::inspector()
{
    if (!_focusedGui)
    {
        ImGui::Text("Select object to inspect");
        return;
    }
    _focusedGui->onInspect();
}

void ObjectStorageGui::viewer()
{
    if (!_focusedGui)
    {
        ImGui::Text("Select object to view");
        return;
    }
    _focusedGui->onView();
}
} // namespace ample::gui
