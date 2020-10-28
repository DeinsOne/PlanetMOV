#include "PlanetMOV.h"
#include "cinder/Display.h"

#include "cinder/CinderImGui.h"
#include "cinder/Log.h"

#include "LuaContext.h"

void PlanetMOV::setup()
{
    printf("Main display size : %d | %d\n", getDisplay()->getSize().x, getDisplay()->getSize().y);
    printf("Current window size : %d | %d\n", getWindowSize().x, getWindowSize().y);

    // Centring window
    setWindowPos(glm::ivec2((getDisplay()->getSize().x / 2) - (getWindowSize().x / 2), (getDisplay()->getSize().y / 2) - (getWindowSize().y / 2)));

    // Initialize ImGui
    setupGui();

    // TimeControl PlanetSystem
    TimeControl::Get().initTimeControl();

    // Initialize PlanetSystem
    PlanetSystem::Get().loadPlanets("assets/config/planet-mov.json" );
    PlanetSystem::Get().eventOnSetup();


}