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


void PlanetMOV::setupGui() {
    ImGui::Initialize();
    _fontDefault = ImGui::GetIO().Fonts->AddFontDefault();

    static ImWchar ranges[] = {0xf000, 0xf3ff, 0};
    ImFontConfig config;
    config.MergeMode = true;

    try {
        _fontSymbols = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/fa-solid-900.ttf", 12.0f, &config, ranges);
        if (!_fontSymbols ) throw std::runtime_error(std::string("assets/fonts/fa-solid-900.ttf -> ") + std::string("Font did not loaded") );
    } catch (std::exception& e ) {
        CI_LOG_EXCEPTION("", e );
        ErrorHandler::Get().push(Error(ErrorType::Error_Config, "Font loading", e.what() ) );
        _fontSymbols = _fontDefault;
    }


    try {
        _fontMain12 = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/UbuntuMono-Regular.ttf", 12.0f);
        if (!_fontMain12 ) throw std::runtime_error(std::string("assets/fonts/UbuntuMono-Regular.ttf -> ") + std::string("Font did not loaded") );
    } catch (std::exception& e ) {
        CI_LOG_EXCEPTION("", e );
        ErrorHandler::Get().push(Error(ErrorType::Error_Config, "Font loading", e.what() ) );
        _fontMain12 = _fontDefault;
    }


    try {
        _fontMain14 = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/UbuntuMono-Regular.ttf", 14.0f);
        if (!_fontMain14 ) throw std::runtime_error(std::string("assets/fonts/UbuntuMono-Regular.ttf -> ") + std::string("Font did not loaded") );
    } catch (std::exception& e ) {
        CI_LOG_EXCEPTION("", e );
        ErrorHandler::Get().push(Error(ErrorType::Error_Config, "Font loading", e.what() ) );
        _fontMain14 = _fontDefault;
    }


    try {
        _fontMainBold14 = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/UbuntuMono-Bold.ttf", 14.0f );
        if (!_fontMainBold14 ) throw std::runtime_error(std::string("assets/fonts/UbuntuMono-Bold.ttf -> ") + std::string("Font did not loaded") );
    } catch (std::exception& e ) {
        CI_LOG_EXCEPTION("", e );
        ErrorHandler::Get().push(Error(ErrorType::Error_Config, "Font loading", e.what() ) );
        _fontMainBold14 = _fontDefault;
    }

}

void PlanetMOV::drawButtons() {
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
            CI_LOG_I("Reloading scripts...");
            ErrorHandler::Get()._errors.clear();

            for (auto i : PlanetSystem::Get()._planets ) {
                i.second->_script.destroy();
                i.second->_shader.destroy();
                i.second.reset();
            }
            

            PlanetSystem::Get()._planets.clear();
            PlanetSystem::Get().loadPlanets("assets/planet-mov.json" );

        }


    ImGui::End();

    ImGui::PopStyleVar();
}


void PlanetMOV::drawTools() {

    static short wnFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NavFlattened;

    // Editor and tools
    if (_toolsWindowOpen ) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0 );
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0 );
        ImGui::SetNextWindowSize(ImVec2(_toolsXSize, ci::app::getWindow()->getSize().y) );
        ImGui::SetNextWindowPos(ImVec2(0, 0 ) );
        ImGui::Begin("Tools", nullptr, wnFlags );
            ImGui::PushFont(_fontMainBold14 );
            PlanetSystem::Get()._selectedPlanet.empty() ? ImGui::TextColored(ImVec4(1,1,1,0.4), "No selected planet") : ImGui::Text("%s", PlanetSystem::Get()._selectedPlanet.c_str() ); 
            ImGui::PopFont();


            ImGui::Separator(); ImGui::Spacing();

            // Tool
            if (!PlanetSystem::Get()._selectedPlanet.empty() ) {
                ImGui::PushFont(_fontMain12 );
                if (ImGui::TreeNode("Planet") ) {
                    ImGui::LabelText("Name", "%s", PlanetSystem::Get()._selectedPlanet.c_str() );
                    ImGui::Spacing();

                    for (auto i : PlanetSystem::Get().getSelectedPlanet()->_args.getMemberNames() ) {
                        if (PlanetSystem::Get().getSelectedPlanet()->_args[i.c_str()].isInt() )
                            ImGui::LabelText(i.c_str(), "%i", PlanetSystem::Get().getSelectedPlanet()->_args[i.c_str()].asInt() );
                        else if (PlanetSystem::Get().getSelectedPlanet()->_args[i.c_str()].isDouble() )
                            ImGui::LabelText(i.c_str(), "%.3f", PlanetSystem::Get().getSelectedPlanet()->_args[i.c_str()].asFloat() );
                        else if (PlanetSystem::Get().getSelectedPlanet()->_args[i.c_str()].isBool() )
                            ImGui::LabelText(i.c_str(), "%i", PlanetSystem::Get().getSelectedPlanet()->_args[i.c_str()].asBool() );
                        else if (PlanetSystem::Get().getSelectedPlanet()->_args[i.c_str()].isString() )
                            ImGui::LabelText(i.c_str(), "%s", PlanetSystem::Get().getSelectedPlanet()->_args[i.c_str()].asCString() );
                        else if (PlanetSystem::Get().getSelectedPlanet()->_args[i.c_str()].isArray() )
                            ImGui::LabelText(i.c_str(), "%.3f | %.3f",
                                PlanetSystem::Get().getSelectedPlanet()->_args[i.c_str()][0].asFloat(),
                                PlanetSystem::Get().getSelectedPlanet()->_args[i.c_str()][1].asFloat()
                            );

                    }

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

                ImGui::PopFont();
            }


            ImGui::SetCursorScreenPos(ImVec2((ImGui::GetWindowSize().x/2) - (ImGui::CalcTextSize("vrs:x.x.x").x/2), ImGui::GetWindowSize().y - ImGui::GetFrameHeight()) );
            ImGui::PushFont(_fontMain12 );
            ImGui::TextColored(ImVec4(1,1,1,0.4), "Vrs:1.1.4" );
            ImGui::PopFont();

            // Close tools window button
            ImGui::SetCursorScreenPos(ImVec2(ImGui::GetWindowSize().x-26, 6 ) );
            if (customButton("", {20, 20}, {1,1,1}, true) ) { _toolsWindowOpen = false; }
        ImGui::End();
        ImGui::PopStyleVar(2);
    }
    else {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0} );
        ImGui::SetNextWindowPos(ImVec2(6,6) );
        ImGui::Begin("ButonForOpen", nullptr, wnFlags | ImGuiWindowFlags_NoBackground );
            // Open tools window button
            if (customButton("", {25, 25}, {1,1,1}, true) ) { _toolsWindowOpen = true; }
        ImGui::End();
        ImGui::PopStyleVar();
    }

}

void PlanetMOV::drawGui() {
    static short wnFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NavFlattened;

    drawButtons();

    drawTools();

    drawErrors();

    // Time info
    ImGui::SetNextWindowSize(ImVec2(172, 51) );
    ImGui::SetNextWindowPos(ImVec2(getWindowSize().x - 172 - 96 - 3, 2 ) );
    ImGui::Begin("DebugWindow", nullptr, wnFlags | ImGuiWindowFlags_NoBackground );
        ImGui::PushFont(_fontMain12 );
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1,1,1,0.5) );
        ImGui::Text("%f : %s", TimeControl::Get()._elapsedTime, "_elapsedTime" );
        ImGui::Text("%f : %s", TimeControl::Get().getDeltaTime(), "_deltaTime" );
        ImGui::PopStyleColor();
        ImGui::PopFont();
    ImGui::End();


}

void PlanetMOV::drawErrors() {
    static short wnFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoTitleBar;


    ImGui::SetNextWindowSize(ImVec2(30, 30) );
    ImGui::SetNextWindowPos(_toolsWindowOpen ? ImVec2(_toolsXSize + 3, 2) : ImVec2(26, 2) );
    ImGui::Begin("Errors", nullptr, wnFlags | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration );
        if (customButton("", ImVec2(20,20), ErrorHandler::Get()._errors.size() > 0 ? glm::vec3(1,0,0) : glm::vec3(1,1,1), true) ) _errorsWindowOpen = !_errorsWindowOpen;
    ImGui::End();


    if (_errorsWindowOpen ) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 3.0 );
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0 );
        ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 6.0 );

        ImGui::SetNextWindowSize(ImVec2(295, 150) );
        ImGui::SetNextWindowPos(_toolsWindowOpen ? ImVec2(_toolsXSize + 36, 12) : ImVec2(56, 12) );
        ImGui::Begin("ErrorsWindow", nullptr, wnFlags | ImGuiWindowFlags_NoResize );
            if (!ErrorHandler::Get()._errors.size() ) ImGui::TextColored(ImVec4(1,1,1,0.4), "No errors" );
            else {
                for (int i = 0; i < ErrorHandler::Get()._errors.size(); i++ ) {
                    std::string ers = "err:";
                    ers += std::to_string(i);

                    ImGui::BeginChild(ers.c_str(), {0, 45 } );

                    ImVec4 _cl = ImVec4(1,0,0,1);
                    std::string _lb = "?";
                    ErrorType _ert = ErrorHandler::Get()._errors.at(i)._type;
                    switch (_ert) {
                        case (ErrorType::Error_Script) : { _cl = ImVec4(1,1,1,1); _lb = ""; break; }
                        case (ErrorType::Error_Shader) : { _cl = ImVec4(1,1,1,1); _lb = ""; break; }
                        case (ErrorType::Error_Config) : { _cl = ImVec4(1,1,1,1); _lb = ""; break; }
                    }

                    ImVec2 _pos = ImGui::GetCursorScreenPos();
                    ImGui::GetWindowDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[0], 12, {_pos.x , _pos.y + 4}, ImGui::GetColorU32(_cl), _lb.c_str() );

                    ImGui::PushFont(_fontMain14 );
                    ImGui::SetCursorScreenPos({_pos.x + 15, _pos.y});
                    ImGui::Text(ErrorHandler::Get()._errors.at(i)._title.c_str() );
                    ImGui::PopFont();


                    ImGui::SetCursorScreenPos(ImVec2(_pos.x + 19, _pos.y + 14) );
                    ImGui::PushFont(_fontMain12 );
                    ImGui::TextColored(ImVec4(1,1,1,0.4), ErrorHandler::Get()._errors.at(i)._details.c_str() );
                    ImGui::PopFont();


                    ImGui::Spacing();

                    ImGui::EndChild();
                    if (i != ErrorHandler::Get()._errors.size() - 1) ImGui::Separator();


                    if (ImGui::IsItemHovered() ) {
                    }

                    // if (ImGui::IsItemClicked() ) ErrorHandler::Get().pop(i );

                }
            }

        ImGui::End();

        ImGui::PopStyleVar(3 );
    }



}