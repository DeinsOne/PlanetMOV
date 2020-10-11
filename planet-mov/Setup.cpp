#include "PlanetMOV.h"
#include "cinder/Display.h"

#include "cinder/CinderImGui.h"
#include "cinder/Log.h"

// #include <json/json.h>
#include "jsonConfig.h"

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



    Json::Value _planetsConfig;
    std::ifstream configFile("assets/config/planet-mov.json" );
    configFile >> _planetsConfig;
    configFile.close();


    if (_planetsConfig["planets"].isArray() ) {
        for (int i = 0; i < _planetsConfig["planets"].size(); i++ ) {
            std::string _id = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_ID, "" );
            float       _size = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_Radius, 0.0f );
            glm::vec2   _pos = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_Pos, glm::vec2(0.0f, 0.0f) );
            std::string _vShader = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_VShader, "assets/shaders/default.vs.glsl" );
            std::string _fShader = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_FShader, "assets/shaders/default.fs.glsl" );

            _planets[_id] = std::make_shared<Planet>(_pos, _size );
            _planets[_id]->_shader = ci::gl::GlslProg::create(
                ci::loadFile(_vShader),
                ci::loadFile(_fShader )
            );

            _planets[_id]->_pathToFragmentShader = _fShader;
            std::ifstream ifs(_planets[_id]->_pathToFragmentShader );
            _planets[_id]->_fragmentShaderText = std::string((std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>()) );
            ifs.close();

        }
    }


}