#include <algorithm>

#include "ample/RegularPolygon.h"
#include "ample/Utils.h"
#include "ample/VectorRectangle.h"
#include "ample/WorldObject2d.h"

#include "AmpleGui.h"
#include "Editor.h"
#include "LevelEditor.h"
#include "StateMachineEditor.h"
#include "Utils.h"
#include "Browser.h"

namespace ample::gui
{
Editor::Editor(game::game2d::Game2dEditor &editor)
    : _game2dEditor(editor)
{
    _creators[tabClass::LEVEL]
        .addParameters()
        .add<param::String>("Name")
        .add<param::Float>("Slice thickness", 10.0f, 0.0f, 100.0f, 1.0f)
        .add<param::Float>("Physics layer position", 0.5f, 0.0f, 1.0f, 0.05f)
        .add<param::Float>("Gravity X", 0.5f, 0.0f, 1.0f, 0.05f)
        .add<param::Float>("Gravity Y", 0.5f, 0.0f, 1.0f, 0.05f);

    _creatorFunctions[tabClass::LEVEL] = [&](const auto &params) {
        auto [level, loader] = editor.createLevel(param::value<std::string>(*params[0]),
                                                  param::value<float>(*params[1]),
                                                  param::value<float>(*params[2]),
                                                  {param::value<float>(*params[3]),
                                                   param::value<float>(*params[4])});
        utils::ignore(loader);
        _openedEditors.emplace_back(std::make_unique<LevelEditor>(level));
    };

    _creators[tabClass::STATE_MACHINE]
        .addParameters()
        .add<param::String>("Name")
        .add<param::LevelsList>("Level", &editor.getLevelsList());

    _creatorFunctions[tabClass::STATE_MACHINE] = [&](const auto &params) {
        if (!param::value<std::shared_ptr<game::game2d::Level>>(*params[1]))
        {
            throw game::GameException("Select level to create State Machine");
        }
        auto stateMachine = editor.createStateMachine(param::value<std::string>(*params[0]),
                                                      param::value<std::shared_ptr<game::game2d::Level>>(*params[1]));
        _openedEditors.emplace_back(std::make_unique<StateMachineEditor>(stateMachine));
    };
}

void Editor::TabCreator()
{
    _creators[_tabClass].drawInterface(_creatorFunctions[_tabClass]);
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
            if (ImGui::BeginTabItem(_openedEditors[i]->editorTargetNamedObject()->name().c_str()))
            {
                Browser::instance().openBrowserTab(_openedEditors[i]->editorTargetNamedObject());
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
    return *_openedEditors[_activeTab]->editorTargetNamedObject();
}
} // namespace ample::gui
