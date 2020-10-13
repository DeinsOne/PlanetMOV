#include "PlanetMOV.h"
#include "cinder/Display.h"

#include "cinder/CinderImGui.h"
#include "cinder/Log.h"

void PlanetMOV::setup()
{
    printf("Main display size : %d | %d\n", getDisplay()->getSize().x, getDisplay()->getSize().y);
    printf("Current window size : %d | %d\n", getWindowSize().x, getWindowSize().y);

    // Centring window
    setWindowPos(glm::ivec2((getDisplay()->getSize().x / 2) - (getWindowSize().x / 2), (getDisplay()->getSize().y / 2) - (getWindowSize().y / 2)));

    // Initialize ImGui
    ImGui::Initialize();
    ImGui::GetIO().Fonts->AddFontDefault();
    static ImWchar ranges[] = {0xf000, 0xf3ff, 0};
    ImFontConfig config;
    config.MergeMode = true;
    ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/fa-solid-900.ttf", 12.0f, &config, ranges);

    // TimeControl PlanetSystem
    TimeControl::Get().initTimeControl();

    // Initialize PlanetSystem
    PlanetSystem::Get().loadPlanetsConfig();
}