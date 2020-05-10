#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "ample/Singleton.h"
#include "ample/WorldLayer2d.h"
#include "ample/Game2dEditor.h"

#include "InterfaceUnit.h"
#include "TabEditor.h"
#include "ObjectConstructor.h"

namespace ample::gui
{
class Editor : public GraphicalInterface
{
private:
    struct StateMacnineRaw
    {
        char name[255];
        
        std::shared_ptr<game::game2d::Level> selectedLevel = nullptr;

        std::string errorString;

        bool success = false;
    };

public:
    enum tabClass
    {
        STATE_MACHINE,
        LEVEL,
    };

public:
    Editor(game::game2d::Game2dEditor &editor);

    void drawInterface() override;
    filing::NamedObject &getFocusedObject() noexcept;
    void openTabCreator(tabClass);

private:
    void TabCreator();

    std::vector<std::unique_ptr<TabEditor>> _openedEditors;
    size_t _activeTab;

    bool _tabCreatorOpened = false;
    tabClass _tabClass;

    std::unordered_map<tabClass, ObjectConstructor> _creators;
    std::unordered_map<tabClass, std::function<void(const std::vector<std::unique_ptr<param::Parameter>> &)>> _creatorFunctions;

    game::game2d::Game2dEditor &_game2dEditor;
};
} // namespace ample::gui
