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
        for (auto &[id, slice] : level->layers())
        {
            buildGuiAndAdd(slice);
            for (auto &object : slice->objects())
            {
                buildGuiAndAdd(object);
                if (object->texture())
                {
                    if (!_guiByObjectName[object->texture()->name()])
                    {
                        buildGuiAndAdd(object->texture());
                        _textures.push_back(object->texture());
                    }
                }
                if (object->className() == "WorldObject2d" || object->className() == "GraphicalObject2d")
                {
                    auto doubleTextObject = std::dynamic_pointer_cast<graphics::GraphicalObject2d>(object);
                    if (doubleTextObject->face().texture())
                    {
                        if (!_guiByObjectName[doubleTextObject->face().getTextureName()])
                        {
                            buildGuiAndAdd(doubleTextObject->face().texture());
                            _textures.push_back(doubleTextObject->face().texture());
                        }
                    }
                    if (doubleTextObject->side().texture())
                    {
                        if (!_guiByObjectName[doubleTextObject->side().getTextureName()])
                        {
                            buildGuiAndAdd(doubleTextObject->side().texture());
                            _textures.push_back(doubleTextObject->side().texture());
                        }
                    }
                }
            }
        }
        for (auto &sm : level->stateMachines())
        {
            buildGuiAndAdd(sm);
            std::unordered_map<std::string, bool> used;
            std::function<void(std::shared_ptr<game::StateMachine::State>)> dfs =
                [&](std::shared_ptr<game::StateMachine::State> curState) {
                    ASSERT(curState);
                    if (used[curState->name()])
                        return;
                    used[curState->name()] = true;
                    for (const auto &transition : curState->transitions())
                    {
                        buildGuiAndAdd(transition);
                        dfs(transition->getNextState());
                    }
                    buildGuiAndAdd(curState);
                    auto actionAdder = [&](std::vector<std::shared_ptr<game::Action>> &actions) {
                        std::for_each(actions.begin(), actions.end(),
                                      [&](auto &act) {
                                          buildGuiAndAdd(act);
                                      });
                    };
                    actionAdder(curState->getOnStartActions());
                    actionAdder(curState->getOnActiveActions());
                    actionAdder(curState->getOnStopActions());
                };
            dfs(sm->getCurrentState());
        }
    }
}

std::shared_ptr<ObjectGui> ObjectStorageGui::getOnInputGui() const noexcept
{
    return _onInput;
}

inline void ObjectStorageGui::create(finalObjectClass objClass, bool needsFocus, std::function<void(std::shared_ptr<ObjectGui>)> func)
{
    ASSERT(!_onInput);
    _onInput = buildGui(objClass, _game2dEditor, this); // TODO: std::forward
    _onInputFunction = func;
    _onInputNeedsFocus = needsFocus;
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
    if (ImGui::Button("Edit"))
    {
        setFocus(gui);
    }
    gui->onInspect();
}

std::vector<std::shared_ptr<game::StateMachine::State>> &ObjectStorageGui::statesList(const std::string &machineName)
{
    return std::dynamic_pointer_cast<StateMachineGui>(objectGuiByName(machineName))->getStatesList();
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
    _focusedGui->onEdit();
    if (ImGui::Button("Submit"))
    {
        try
        {
            _focusedGui->onSubmitEdit();
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
    for (const auto &[name, type] : classIdByClassName)
    {
        if (type.drawInCreator)
        {
            if (ImGui::Selectable(name.c_str()))
            {
                create(type.finalClass);
            }
        }
    }

    if (!_onInput)
    {
        return;
    }
    ImGui::OpenPopup(("Create new " + _onInput->className()).c_str());
    if (ImGui::BeginPopupModal(("Create new " + _onInput->className()).c_str(),
                               NULL,
                               ImGuiWindowFlags_NoResize |
                                   ImGuiWindowFlags_AlwaysAutoResize))
    {
        _onInput->onCreate();
        if (ImGui::Button("Submit"))
        {
            try
            {
                _onInput->onSubmitCreate();
                _guiByObjectName[_onInput->name()] = _onInput;
                if (_onInputFunction)
                {
                    _onInputFunction(_onInput);
                    _onInputFunction = {};
                }
                _creationSuccess = true;
                if (_onInputNeedsFocus)
                {
                    setFocus(_onInput);
                }
                _onInputNeedsFocus = false;
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

void ObjectStorageGui::texturesViewer()
{
    for (auto &tex : texturesList())
    {
        if (auto texGui = objectGuiByName(tex->name());
            ImGui::TreeNode(texGui->name().c_str()))
        {
            inspectSingleItem(texGui);
            texGui->onInspect();
            ImGui::TreePop();
        }
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

std::vector<std::shared_ptr<graphics::Texture>> &ObjectStorageGui::texturesList() noexcept
{
    return _textures;
}
} // namespace ample::gui
