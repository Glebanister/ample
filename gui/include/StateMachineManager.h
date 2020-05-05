#pragma once

#include <memory>

#include <imgui.h>
#include <imnodes.h>

#include "ample/StateMachine.h"
#include "ample/Singleton.h"

#include "InterfaceUnit.h"

namespace ample::gui
{
    struct RawState
    {
        char nameBuffer[256];
        std::vector<std::shared_ptr<game::StateMachine::Transition>> transitions;
    };

    struct RawTransition
    {
        char nameBuffer[256];
        char classNameBuffer[256];

        std::shared_ptr<game::StateMachine::State> nextState;
    };

    int make_id(int node, int attribute);

    class StateMachineManager : public InterfaceUnit, public utils::Singleton<StateMachineManager>
    {
    public:
        StateMachineManager();
        ~StateMachineManager();

    public:
        void drawInterface() override;

        void remove_link(int id);

    private:
        struct Link
        {
            int start, end;
        };

        int current_id;
        std::unordered_map<int, Link> links;
        game::StateMachine machine{"machine"};

        std::unordered_map<int, RawState> states;
        std::unordered_map<int, int> state_id_by_input_id;
        std::unordered_map<int, int> state_id_by_output_id;
        std::unordered_map<int, std::shared_ptr<game::StateMachine::State>> state_by_id;

        std::unordered_map<int, RawTransition> transitions;
        std::unordered_map<int, int> transition_id_by_input_id;
        std::unordered_map<int, int> transition_id_by_output_id;
        std::unordered_map<int, std::shared_ptr<game::StateMachine::Transition>> transition_by_id;
    };
} // namespace ample::gui
