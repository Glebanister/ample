#include <algorithm>

#include "ample/RegularPolygon.h"
#include "ample/Utils.h"
#include "ample/VectorRectangle.h"
#include "ample/WorldObject2d.h"

#include "Editor.h"
#include "LevelEditor.h"
#include "StateMachineEditor.h"
#include "Utils.h"

namespace ample::gui
{
void Editor::TabCreator()
{
    switch (_tabClass)
    {
    case tabClass::LEVEL:
        LevelCreator();
        break;
    case tabClass::STATE_MACHINE:
        StateMachineCreator();
        break;
    }
}

void Editor::LevelCreator()
{
    ImGui::InputText("Name", _levelRaw.name, 255);
    ImGui::InputScalar("Slice thickness", ImGuiDataType_Float, &_levelRaw.sliceThickness, &_levelRaw.sliceThicknessStep);
    utils::limit(_levelRaw.physicsLayerPosition, _levelRaw.physicsLayerPositionMin, _levelRaw.physicsLayerPositionMax);
    ImGui::InputScalar("Physics layer position", ImGuiDataType_Float, &_levelRaw.physicsLayerPosition, &_levelRaw.physicsLayerPositionStep);
    ImGui::InputScalar("Gravity X", ImGuiDataType_Float, &_levelRaw.gravity.x, &_levelRaw.gravityStep);
    ImGui::InputScalar("Gravity Y", ImGuiDataType_Float, &_levelRaw.gravity.y, &_levelRaw.gravityStep);

    if (ImGui::Button("Create"))
    {
        try
        {
            ASSERT(_editor);
            auto [level, loader] = _editor->createLevel(std::string(_levelRaw.name),
                                                        _levelRaw.sliceThickness,
                                                        _levelRaw.physicsLayerPosition,
                                                        _levelRaw.gravity);
            utils::ignore(loader);
            _openedEditors.emplace_back(std::make_unique<LevelEditor>(level));
            _levelRaw.success = true;
            _levelRaw.name[0] = '\0';
        }
        catch (const std::exception &e)
        {
            ImGui::OpenPopup("Unable to create level");
            _levelRaw.errorString = e.what();
        }
    }
    gui_utils::MessagePopup("Unable to create level", _levelRaw.errorString);
    ImGui::SameLine();
    gui_utils::CloseCurrentPopupOnSuccessButton(_levelRaw.success);
}

void Editor::StateMachineCreator()
{
    ImGui::InputText("Name", _stateMachineRaw.name, 255);
    if (auto selectedLevel = gui_utils::SelectNamedObjectFromList("Level", _editor->getLevelsList()); selectedLevel)
    {
        _stateMachineRaw.selectedLevel = selectedLevel;
    }
    ImGui::TextUnformatted(!_stateMachineRaw.selectedLevel ? "" : _stateMachineRaw.selectedLevel->name().c_str());

    if (ImGui::Button("Create"))
    {
        try
        {
            if (!_stateMachineRaw.selectedLevel)
            {
                throw game::GameException("select level");
            }
            ASSERT(_editor);
            auto stateMachine = _editor->createStateMachine(_stateMachineRaw.name, _stateMachineRaw.selectedLevel);
            _openedEditors.emplace_back(std::make_unique<StateMachineEditor>(stateMachine));
            _stateMachineRaw.success = true;
            _stateMachineRaw.name[0] = '\0';
        }
        catch (const std::exception &e)
        {
            ImGui::OpenPopup("Unable to create state machine");
            _stateMachineRaw.errorString = e.what();
        }
    }
    gui_utils::MessagePopup("Unable to create state machine", _stateMachineRaw.errorString);
    ImGui::SameLine();
    gui_utils::CloseCurrentPopupOnSuccessButton(_stateMachineRaw.success);
}

void Editor::openTabCreator(tabClass newTabClass)
{
    _tabCreatorOpened = true;
    _tabClass = newTabClass;
}

void Editor::drawInterface()
{
    if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_NoTooltip))
    {
        for (size_t i = 0; i < _openedEditors.size(); ++i)
        {
            if (ImGui::BeginTabItem(_openedEditors[i]->editorTarget()->name().c_str()))
            {
                _activeTab = i;
                _openedEditors[i]->drawInterface();
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
    if (_tabCreatorOpened)
    {
        ImGui::OpenPopup("New tab");
        _tabCreatorOpened = false;
    }
    if (ImGui::BeginPopupModal("New tab", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        TabCreator();
        ImGui::EndPopup();
    }
}

filing::NamedObject &Editor::getFocusedObject() noexcept
{
    return *_openedEditors[_activeTab]->editorTarget();
}

void Editor::setEditor(game::game2d::Game2dEditor &editor)
{
    _editor = &editor;
}
} // namespace ample::gui
