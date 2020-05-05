#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ample/Singleton.h"
#include "ample/WorldLayer2d.h"
#include "ample/Game2dEditor.h"

#include "InterfaceUnit.h"
#include "TabEditor.h"

namespace ample::gui
{
class Editor : public InterfaceUnit<Editor>
{
private:
    struct LevelRaw
    {
        char name[255];

        float sliceThickness = 10.0f;
        float sliceThicknessStep = 1.0f;

        float physicsLayerPosition = 0.5f;
        float physicsLayerPositionStep = 0.05f;
        float physicsLayerPositionMin = 0.0f;
        float physicsLayerPositionMax = 1.0f;

        ample::graphics::Vector2d<float> gravity = {-10.0f, 0.0f};
        float gravityStep = 1.0f;

        std::string errorString;

        bool success = false;
    };

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
        LEVEL
    };

public:
    void drawInterface() override;
    filing::NamedObject &getFocusedObject() noexcept;
    void openTabCreator(tabClass);
    void setEditor(game::game2d::Game2dEditor &editor);

private:
    void TabCreator();
    void LevelCreator();
    void StateMachineCreator();

    std::vector<std::unique_ptr<TabEditor>> _openedEditors;
    size_t _activeTab;

    bool _tabCreatorOpened = false;
    tabClass _tabClass;

    LevelRaw _levelRaw;
    StateMacnineRaw _stateMachineRaw;

    game::game2d::Game2dEditor *_editor;
};
} // namespace ample::gui
