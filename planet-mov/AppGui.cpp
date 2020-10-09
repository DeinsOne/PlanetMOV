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



void PlanetMOV::DrawGui() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0} );

    static short wnFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NavFlattened;

    ImGui::SetNextWindowSize(ImVec2(96, 21) );
    ImGui::SetNextWindowPos(ImVec2(getWindowSize().x - 96 - 3, 2 ) );
    ImGui::Begin("ToolsBar:1", nullptr, wnFlags );
        // Resume button
        ImGui::SetCursorScreenPos(ImVec2(ImGui::GetWindowPos().x + 6, ImGui::GetWindowPos().y + 6) );
        if (_playTime == true) { if (customButton("", {20, 20}, {1,0,0} )) _playTime = false; }
        else if (customButton("", {20, 20}, {0,1,0} )) { 
            _nowTime = std::chrono::high_resolution_clock::now();
            _playTime = true;
        }

        // Restart button
        ImGui::SetCursorScreenPos(ImVec2(ImGui::GetWindowPos().x + 38, ImGui::GetWindowPos().y + 6) );
        if (customButton("", {20, 20} )) { _elapsedTime = 0.0; }


        // Terminal button
        ImGui::SetCursorScreenPos(ImVec2(ImGui::GetWindowPos().x + 70, ImGui::GetWindowPos().y + 6) );
        if (customButton("", {20, 20}) ) { CI_LOG_I("Planets config folder is : " << "assets/" << "  | open console. . ." ); }


    ImGui::End();


    // Time info
    ImGui::SetNextWindowSize(ImVec2(172, 51) );
    ImGui::SetNextWindowPos(ImVec2(getWindowSize().x - 172 - 96 - 3, 2 ) );
    ImGui::Begin("DebugWindow", nullptr, wnFlags | ImGuiWindowFlags_NoBackground );
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1,1,1,0.5) );
        ImGui::Text("%f : %s", _elapsedTime, "_elapsedTime" );
        ImGui::Text("%f : %s", _deltaTime, "_deltaTime" );

        ImGui::Text("%f : %s", _zoom, "_zLevel" );
        ImGui::PopStyleColor();
    ImGui::End();



    ImGui::PopStyleVar();

}