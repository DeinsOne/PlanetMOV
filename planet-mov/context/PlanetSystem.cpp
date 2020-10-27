#include "PlanetSystem.h"
#include <cinder/gl/gl.h>
#include <cinder/gl/Batch.h>

#include "jsonConfig.h"
#include "TimeControl.h"
#include "CameraControl.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
    #include "luaconf.h"
}

#include "LuaBridge/LuaBridge.h"

#include "cinder/Log.h"

void PlanetSystem::loadPlanetsConfig(std::string _file)
{
    Json::Value _planetsConfig;
    std::ifstream configFile(_file.c_str() );
    configFile >> _planetsConfig;
    configFile.close();

    if (_planetsConfig["planets"].isArray())
    {
        for (int i = 0; i < _planetsConfig["planets"].size(); i++)
        {
            std::string _id = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_ID, "");
            float _size = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_Radius, 0.0f);
            glm::vec2 _pos = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_Pos, glm::vec2(0.0f, 0.0f));
            std::string _vShader = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_VShader, "assets/shaders/default.vs.glsl");
            std::string _fShader = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_FShader, "assets/shaders/default.fs.glsl");


            _planets[_id] = std::make_shared<Planet>(_pos, _size);
            _planets[_id]->_shader = ci::gl::GlslProg::create(
                ci::loadFile(_vShader),
                ci::loadFile(_fShader));

            _planets[_id]->_pathToFragmentShader = _fShader;
            std::ifstream ifs(_planets[_id]->_pathToFragmentShader);
            _planets[_id]->_fragmentShaderText = std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
            ifs.close();

            _planets[_id]->_script.loadScript(Json::getValueByLabel(_planetsConfig["planets"][i], Labels_Script, "" ) );
        }
    }
}

void PlanetSystem::update()
{
    _planetPicker.reset();
    _planetPicker = ci::gl::Fbo::create(ci::app::getWindow()->getSize().x, ci::app::getWindow()->getSize().y);
}

void PlanetSystem::onMouseDown(ci::app::MouseEvent event)
{
    if (event.isLeft())
    {
        ci::Surface32f pixel = _planetPicker->readPixels32f(ci::Area(0, 0, _planetPicker->getSize().x, _planetPicker->getSize().y), GL_COLOR_ATTACHMENT0);

        if (pixel.getPixel(event.getPos()).a != 0)
        {
            float _greenPx = pixel.getPixel(event.getPos()).g;

            auto planet = _planets.begin();
            for (int i = 0; i < _planets.size(); i++)
            {
                float _objCl = ((float)(i + 1)) / ((float)_planets.size());

                if (fabs(_objCl - _greenPx) <= 0.01)
                    _selectedPlanet = planet->first;

                planet++;
            }
        }
        else
            _selectedPlanet = "";
    }
}

void PlanetSystem::draw()
{
    for (auto planet : _planets)
    {
        ci::gl::setModelMatrix(ci::translate(glm::vec3(planet.second->_pos, 0.0)));

        if (_selectedPlanet == planet.first)
        {
            ci::gl::getStockShader(ci::gl::ShaderDef().color())->bind();
            ci::gl::color(ci::Color::hex(_colorOfBorder));
            ci::gl::drawSolidCircle({}, planet.second->_size + _radiusOfBorder, planet.second->_size * 12);
        }

        if (planet.second->_shader)
            planet.second->BindShader(TimeControl::Get()._elapsedTime, TimeControl::Get().getDeltaTime());
        else
            ci::gl::color(ci::Color::hex(0xeeeeee));
        ci::gl::drawSolidCircle({}, planet.second->_size, planet.second->_size * 12);
    }

    // Draw separeate fbo to give possibility planet picking
    _planetPicker->bindFramebuffer();
    ci::gl::clear(ci::Color::hex(0x0000));
    ci::gl::setMatrices(CameraControl::Get()._camera);

    auto planet = _planets.begin();
    for (int i = 0; i < _planets.size(); i++)
    {
        ci::gl::setModelMatrix(ci::translate(glm::vec3(planet->second->_pos, 0.0)));

        ci::gl::getStockShader(ci::gl::ShaderDef().color())->bind();
        ci::gl::color(0, ((float)(i + 1)) / ((float)_planets.size()), 0, 1);
        ci::gl::drawSolidCircle({}, planet->second->_size, planet->second->_size * 12);
        planet++;
    }

    _planetPicker->unbindFramebuffer();
}

void PlanetSystem::destroy()
{
    _planetPicker.reset();

    for (auto it : _planets)
    {
        it.second->_script.destroy();
        it.second->_shader.reset();
        it.second.reset();
    }
}





void PlanetSystem::eventOnSetup() {
    for (auto i : _planets )
        auto result = i.second->callOnSetup();

}

void PlanetSystem::eventOnUpdate() {
    for (auto i : _planets )
        auto result = i.second->callOnUpdate();

}

void PlanetSystem::eventOnRender() {
    for (auto i : _planets )
        auto result = i.second->callOnRender();

}