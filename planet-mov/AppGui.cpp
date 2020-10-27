#include "PlanetMOV.h"

#include "cinder/app/App.h"
#include "cinder/CinderImGui.h"

#include "cinder/Log.h"

bool customButton(const char* label, ImVec2 size, glm::vec3 textColor = {1,1,1}, bool centring = false ) {
    ImDrawList* list = ImGui::GetWindowDrawList();    
    ImVec2 minPos = ImGui::GetCursorScreenPos();
    bool pressed = false;

    if (ImGui::InvisibleButton(label, size )) pressed = true;

    if (ImGui::IsItemHovered() ) {
        list->AddRectFilled(minPos, ImVec2(minPos.x+size.x, minPos.y+size.y), ImGui::GetColorU32(ImGuiCol_ButtonHovered), 3 );

        if (!centring ) {
            list->AddText({minPos.x+3, minPos.y+3}, ImGui::GetColorU32(ImVec4(textColor.x,textColor.y,textColor.z,1)), label );
        } 
        else {
            ImVec2 txtSize = ImGui::CalcTextSize(label, nullptr, true );
            list->AddText({minPos.x + ((size.x-txtSize.x)/2), minPos.y + ((size.y-txtSize.y)/2)}, ImGui::GetColorU32(ImVec4(textColor.x,textColor.y,textColor.z,1)), label );
        }

    } 
    else {
        list->AddRectFilled(minPos, ImVec2(minPos.x+size.x, minPos.y+size.y), ImGui::GetColorU32(ImGuiCol_ButtonHovered, 0.05), 3 );
        if (!centring ) {
            list->AddText({minPos.x+3, minPos.y+3}, ImGui::GetColorU32(ImVec4(textColor.x,textColor.y,textColor.z,0.75)), label );
        }
        else {
            ImVec2 txtSize = ImGui::CalcTextSize(label, nullptr, true );
            list->AddText({minPos.x + ((size.x-txtSize.x)/2), minPos.y + ((size.y-txtSize.y)/2)}, ImGui::GetColorU32(ImVec4(textColor.x,textColor.y,textColor.z,0.75)), label );
        }
    }

    return pressed;
}


std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


void PlanetMOV::DrawGui() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0} );

    static short wnFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NavFlattened;

    // Time flow control tools
    ImGui::SetNextWindowSize(ImVec2(96, 21) );
    ImGui::SetNextWindowPos(ImVec2(getWindowSize().x - 96 - 3, 2 ) );
    ImGui::Begin("ToolsBar:1", nullptr, wnFlags );
        // Resume button
        ImGui::SetCursorScreenPos(ImVec2(ImGui::GetWindowPos().x + 6, ImGui::GetWindowPos().y + 6) );
        if (TimeControl::Get()._play == true) { if (customButton("", {20, 20}, {1,0,0} )) TimeControl::Get()._play = false; }
        else if (customButton("", {20, 20}, {0,1,0} )) { 
            TimeControl::Get()._time = std::chrono::high_resolution_clock::now();
            TimeControl::Get()._play = true;
        }

        // Restart button
        ImGui::SetCursorScreenPos(ImVec2(ImGui::GetWindowPos().x + 38, ImGui::GetWindowPos().y + 6) );
        if (customButton("", {20, 20} )) {
            TimeControl::Get()._elapsedTime = 0.0;
            PlanetSystem::Get().eventOnSetup();
        }


        // Terminal button
        ImGui::SetCursorScreenPos(ImVec2(ImGui::GetWindowPos().x + 70, ImGui::GetWindowPos().y + 6) );
        if (customButton("", {20, 20}) ) {
            // CI_LOG_I("Planets config folder is : " << "assets/" << "  | open console. . ." );
            CI_LOG_I("Reloading scripts...");

            for (auto i : PlanetSystem::Get()._planets ) {
                i.second->_script.reload();
                i.second->_script.check();
            }

        }


    ImGui::End();


    // Time info
    ImGui::SetNextWindowSize(ImVec2(172, 51) );
    ImGui::SetNextWindowPos(ImVec2(getWindowSize().x - 172 - 96 - 3, 2 ) );
    ImGui::Begin("DebugWindow", nullptr, wnFlags | ImGuiWindowFlags_NoBackground );
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1,1,1,0.5) );
        ImGui::Text("%f : %s", TimeControl::Get()._elapsedTime, "_elapsedTime" );
        ImGui::Text("%f : %s", TimeControl::Get().getDeltaTime(), "_deltaTime" );
        ImGui::PopStyleColor();
    ImGui::End();


    ImGui::PopStyleVar();



    // Editor and tools
    if (_toolsOpen ) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0 );
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0 );
        ImGui::SetNextWindowSize(ImVec2(275, ci::app::getWindow()->getSize().y) );
        ImGui::SetNextWindowPos(ImVec2(0, 0 ) );
        ImGui::Begin("Tools", nullptr, wnFlags );
            PlanetSystem::Get()._selectedPlanet.empty() ? ImGui::TextColored(ImVec4(1,1,1,0.4), "No selected planet") : ImGui::Text("%s", PlanetSystem::Get()._selectedPlanet.c_str() ); 


            ImGui::Separator(); ImGui::Spacing();

            // Tool
            if (!PlanetSystem::Get()._selectedPlanet.empty() ) {
                if (ImGui::TreeNode("Planet") ) {
                    ImGui::LabelText("Name", "%s", PlanetSystem::Get()._selectedPlanet.c_str() );
                    ImGui::Spacing();
                    ImGui::LabelText("Radius", "%.3f", PlanetSystem::Get().getSelectedPlanet()->_size );
                    ImGui::LabelText("Pos", "%.2f | %.2f", PlanetSystem::Get().getSelectedPlanet()->_pos.x, PlanetSystem::Get().getSelectedPlanet()->_pos.y );

                    ImGui::TreePop();
                }

                ImGui::Spacing();
                if (ImGui::TreeNode("Shader") ) {
                    ImGui::Text("%s", PlanetSystem::Get().getSelectedPlanet()->_shader._pathSEntt.c_str() );
                    ImGui::Spacing();

                    if (ImGui::TreeNode("Fragment shader") ) {
                        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0} );
                        std::vector<std::string> lines = split(PlanetSystem::Get().getSelectedPlanet()->_shader._textSEntt, "\n" );
                        for (int i = 0; i < lines.size(); i++ ) {
                            ImGui::Text("%s", lines.at(i).c_str() );
                        }
                        ImGui::PopStyleVar();
                        ImGui::TreePop();
                    }

                    ImGui::TreePop();
                }

                if (!PlanetSystem::Get().getSelectedPlanet()->_script._textSEntt.empty() ) {
                    ImGui::Spacing();
                    if (ImGui::TreeNode("Script") ) {
                        ImGui::Text("%s", PlanetSystem::Get().getSelectedPlanet()->_script._pathSEntt.c_str() );
                        ImGui::Spacing();


                        if (ImGui::TreeNode("Lua script") ) {
                            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0} );
                            std::vector<std::string> lines = split(PlanetSystem::Get().getSelectedPlanet()->_script._textSEntt, "\n" );
                            for (int i = 0; i < lines.size(); i++ ) {
                                ImGui::Text("%s", lines.at(i).c_str() );
                            }
                            ImGui::PopStyleVar();
                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }
                }
            }


            ImGui::SetCursorScreenPos(ImVec2((ImGui::GetWindowSize().x/2) - (ImGui::CalcTextSize("vrs:x.x.x").x/2), ImGui::GetWindowSize().y - ImGui::GetFrameHeight()) );
            ImGui::TextColored(ImVec4(1,1,1,0.4), "Vrs:prealpha" );

            // Close tools window button
            ImGui::SetCursorScreenPos(ImVec2(ImGui::GetWindowSize().x-26, 6 ) );
            if (customButton("", {20, 20}, {1,1,1}, true) ) { _toolsOpen = false; }
        ImGui::End();
        ImGui::PopStyleVar(2);
    }
    else {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0} );
        ImGui::SetNextWindowPos(ImVec2(6,6) );
        ImGui::Begin("ButonForOpen", nullptr, wnFlags | ImGuiWindowFlags_NoBackground );
            // Open tools window button
            if (customButton("", {25, 25}, {1,1,1}, true) ) { _toolsOpen = true; }
        ImGui::End();
        ImGui::PopStyleVar();
    }


}