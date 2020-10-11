#include "PlanetMOV.h"
#include "cinder/Display.h"

#include "cinder/CinderImGui.h"
#include "cinder/Log.h"


void PlanetMOV::setup() {
    printf("Main display size : %d | %d\n", getDisplay()->getSize().x, getDisplay()->getSize().y);
    printf("Current window size : %d | %d\n", getWindowSize().x, getWindowSize().y);

    // Centring window
    setWindowPos(glm::ivec2((getDisplay()->getSize().x/2) - (getWindowSize().x/2), (getDisplay()->getSize().y/2) - (getWindowSize().y/2) ) );


    // Initilize ImGui
    ImGui::Initialize();
    ImGui::GetIO().Fonts->AddFontDefault();
    static ImWchar ranges[] = { 0xf000, 0xf3ff, 0 };
    ImFontConfig config; config.MergeMode = true;
    ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/fa-solid-900.ttf", 12.0f, &config, ranges);



    _planets["Sun"] = std::make_shared<Planet>(glm::vec2(0,0), 3.0f );
    _planets["Sun"]->_shader = ci::gl::GlslProg::create(
        ci::loadFile("assets/shaders/glsl/default.vs.glsl"),
        ci::loadFile("assets/shaders/glsl/sunShader.fs.glsl" )
    );
    
    _planets["Sun"]->_pathToFragmentShader = "assets/shaders/glsl/sunShader.fs.glsl";
    std::ifstream ifs(_planets["Sun"]->_pathToFragmentShader );
    _planets["Sun"]->_fragmentShaderText = std::string((std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>()) );
    ifs.close();

}