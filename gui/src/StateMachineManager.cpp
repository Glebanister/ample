#include "StateMachineManager.h"

#include <SDL_keycode.h>
#include <cstdio>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace ample::gui
{
    int make_id(int node, int attribute)
    {
        return (node << 16) | attribute;
    }

    StateMachineManager::StateMachineManager()
    {
        imnodes::Initialize();
    }

    StateMachineManager::~StateMachineManager()
    {
        imnodes::Shutdown();
    }

    void StateMachineManager::drawInterface()
    {
        ImGui::Begin("StateMachineManager");

        imnodes::BeginNodeEditor();

        for (auto &elem : states)
        {
            const float node_width = 120.0f;
            imnodes::BeginNode(elem.first);

            imnodes::BeginNodeTitleBar();
            ImGui::TextUnformatted("state");
            imnodes::EndNodeTitleBar();

            imnodes::BeginInputAttribute(make_id(elem.first, 1));
            ImGui::Text("input");
            state_id_by_input_id[make_id(elem.first, 1)] = elem.first;
            imnodes::EndAttribute();

            ImGui::Spacing();
            {
                imnodes::BeginOutputAttribute(make_id(elem.first, 3));
                const float label_width = ImGui::CalcTextSize("transitions").x;
                ImGui::Indent(node_width - label_width - 1.5f);
                ImGui::Text("transitions");
                for (size_t i = 0; i < elem.second.transitions.size(); ++i)
                {
                    ImGui::Text(elem.second.transitions[i]->className().c_str());
                }
                state_id_by_output_id[make_id(elem.first, 3)] = elem.first;
                imnodes::EndAttribute();
            }

            ImGui::Text("\n");
            ImGui::PushItemWidth(100.0f);
            ImGui::InputText("Name", elem.second.nameBuffer, 255);
            ImGui::PopItemWidth();

            std::string out = std::string("Name : ") + (strcmp(elem.second.nameBuffer, "") ? "yes" : "no");
            ImGui::Text(out.c_str());

            if (strcmp(elem.second.nameBuffer, ""))
            {
                if (ImGui::Button("update"))
                {
                    std::string name(elem.second.nameBuffer);
                    std::shared_ptr<game::StateMachine::State> state = std::make_shared<game::StateMachine::State>(machine, name);
                    state_by_id[make_id(elem.first, 0)] = state;
                }
            }
            imnodes::EndNode();
        }

        for (auto &elem : transitions)
        {
            const float node_width = 120.0f;
            imnodes::BeginNode(elem.first);

            imnodes::BeginNodeTitleBar();
            ImGui::TextUnformatted("transition");
            imnodes::EndNodeTitleBar();

            imnodes::BeginInputAttribute(make_id(elem.first, 1));
            ImGui::Text("input");
            transition_id_by_input_id[make_id(elem.first, 1)] = elem.first;
            imnodes::EndAttribute();
            ImGui::Spacing();
            {
                imnodes::BeginOutputAttribute(make_id(elem.first, 2));
                const float label_width = ImGui::CalcTextSize("nextState").x;
                ImGui::Indent(node_width - label_width - 1.5f);
                ImGui::Text("nextState");
                transition_id_by_output_id[make_id(elem.first, 2)] = elem.first;
                imnodes::EndAttribute();
            }

            ImGui::Text("\n");
            ImGui::PushItemWidth(100.0f);
            ImGui::InputText("Name", elem.second.nameBuffer, 255);
            ImGui::PopItemWidth();
            ImGui::PushItemWidth(100.0f);
            ImGui::InputText("Class name", elem.second.classNameBuffer, 255);
            ImGui::PopItemWidth();

            std::string out = std::string("Name : ") + (strcmp(elem.second.nameBuffer, "") ? "yes" : "no");
            ImGui::Text(out.c_str());

            out = std::string("Class name : ") + (strcmp(elem.second.classNameBuffer, "") ? "yes" : "no");
            ImGui::Text(out.c_str());

            out = std::string("Next state : ") + (elem.second.nextState ? "yes" : "no");
            ImGui::Text(out.c_str());

            if (strcmp(elem.second.nameBuffer, "") &&
                strcmp(elem.second.classNameBuffer, "") &&
                elem.second.nextState)
            {
                if (ImGui::Button("update"))
                {
                    std::string name(elem.second.nameBuffer);
                    std::string className(elem.second.classNameBuffer);
                    std::shared_ptr<game::StateMachine::Transition> transition =
                        std::make_shared<game::StateMachine::Transition>(name, className, elem.second.nextState);
                    transition_by_id[make_id(elem.first, 0)] = transition;
                }
            }
            imnodes::EndNode();
        }

        for (const auto linkpair : links)
        {
            imnodes::Link(
                linkpair.first, linkpair.second.start, linkpair.second.end);
        }

        // Context menu for adding new nodes
        if (!ImGui::IsAnyItemHovered() && ImGui::IsMouseClicked(1))
        {
            ImGui::OpenPopup("context menu");
        }

        if (ImGui::BeginPopup("context menu"))
        {
            int new_node = -1;
            ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();

            if (ImGui::MenuItem("create state"))
            {
                new_node = current_id++;
                states.insert(std::make_pair(new_node, RawState{}));
            }

            if (ImGui::MenuItem("create transition"))
            {
                new_node = current_id++;
                transitions.insert(std::make_pair(new_node, RawTransition{}));
            }

            ImGui::EndPopup();

            if (new_node != -1)
            {
                imnodes::SetNodeScreenSpacePos(new_node, click_pos);
            }
        }
        imnodes::EndNodeEditor();

        int link_start, link_end;
        if (imnodes::IsLinkCreated(&link_start, &link_end))
        {
            if (transition_id_by_output_id.find(link_start) != transition_id_by_output_id.end() &&
                state_id_by_input_id.find(link_end) != state_id_by_input_id.end())
            {
                int first_id = transition_id_by_output_id[link_start];
                RawTransition &rawTransition = transitions[first_id];

                int second_id = state_id_by_input_id[link_end];
                rawTransition.nextState = state_by_id[make_id(second_id, 0)];

                if (rawTransition.nextState)
                {
                    links.insert(
                        std::make_pair(current_id++, Link{link_start, link_end}));
                }
            }
            else if (state_id_by_output_id.find(link_start) != state_id_by_output_id.end() &&
                     transition_id_by_input_id.find(link_end) != transition_id_by_input_id.end())
            {
                int first_id = state_id_by_output_id[link_start];
                RawState &rawState = states[first_id];

                int second_id = transition_id_by_input_id[link_end];
                std::shared_ptr<game::StateMachine::Transition> transition = transition_by_id[make_id(second_id, 0)];
                if (transition)
                {
                    rawState.transitions.push_back(transition);
                    links.insert(
                        std::make_pair(current_id++, Link{link_start, link_end}));
                }
            }
        }

        const int num_selected = imnodes::NumSelectedLinks();
        if (num_selected > 0 && ImGui::IsKeyReleased(SDL_SCANCODE_X))
        {
            static std::vector<int> selected_links;
            selected_links.resize(static_cast<size_t>(num_selected), -1);
            imnodes::GetSelectedLinks(selected_links.data());
            for (const int link_id : selected_links)
            {
                remove_link(link_id);
                links.erase(link_id);
            }
            selected_links.clear();
        }
        ImGui::End();
    }

    void StateMachineManager::remove_link(int id)
    {
        int link_start = links[id].start;
        int link_end = links[id].end;
        if (transition_id_by_output_id.find(link_start) != transition_id_by_output_id.end() &&
            state_id_by_input_id.find(link_end) != state_id_by_input_id.end())
        {
            int first_id = transition_id_by_output_id[link_start];
            RawTransition &rawTransition = transitions[first_id];
            rawTransition.nextState = nullptr;
        }
        else if (state_id_by_output_id.find(link_start) != state_id_by_output_id.end() &&
                 transition_id_by_input_id.find(link_end) != transition_id_by_input_id.end())
        {
            int first_id = state_id_by_output_id[link_start];
            RawState &rawState = states[first_id];

            int second_id = transition_id_by_input_id[link_end];
            std::shared_ptr<game::StateMachine::Transition> transition = transition_by_id[make_id(second_id, 0)];
            if (transition)
            {
                auto it = rawState.transitions.begin();
                for (; it != rawState.transitions.end(); ++it)
                {
                    if (transition == *it)
                    {
                        break;
                    }
                }
                rawState.transitions.erase(it);
            }
        }
    }

} // namespace ample::gui