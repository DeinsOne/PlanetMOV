#include "PlanetSystem.h"
#include <cinder/gl/gl.h>
#include <cinder/gl/Batch.h>
#include <iostream>

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

float lodExponent(float size ) {
    // float t = pow(size, 2) - (8.3 * size) -1500 + 9.1;
    // float sqrtD = sqrt(pow(85.0, 2) + (4 * t ));

    // float y1 = (-85 + sqrtD)/2;
    // float y2 = (-85 - sqrtD)/2;
 
    // if (y1 < 0 ) return y2;
    // else return y1;

    return 44;
}

void PlanetSystem::loadPlanets(std::string _file)
{
    Json::Value _planetsConfig;

    try {
        std::ifstream configFile(_file.c_str() );
        configFile >> _planetsConfig;
        configFile.close();
    }
    catch (std::exception& e) {
        CI_LOG_EXCEPTION("", e );
        ErrorHandler::Get().push(Error(ErrorType::Error_Config, "Config not found", e.what()) );
    }

    for (auto i : _planetsConfig["planets"].getMemberNames() ) {
        float           _size = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_Radius, 0.0f);
        glm::vec2       _pos = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_Pos, glm::vec2(0.0f, 0.0f));
        std::string     _fShader = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_FShader, "assets/shaders/default.fs.glsl");


        if (!i.empty() ) {
            _planets[i] = std::make_shared<Planet>(_pos, _size);

            // Load shader
            auto er = _planets[i]->_shader.load(_fShader );
            ErrorHandler::Get().push(er );

            // Load script
            auto er1 = _planets[i]->_script.load(Json::getValueByLabel(_planetsConfig["planets"][i], Labels_Script, "") );
            ErrorHandler::Get().push(er1 );
        } 

    }


    // FIXME: Check errors
    for (auto i : _planets ) {
        i.second->_script.check();
        i.second->_shader.check();
    }


    eventOnSetup();
}

void PlanetSystem::update()
{
    _planetPicker.reset();
    _planetPicker = ci::gl::Fbo::create(ci::app::getWindow()->getSize().x, ci::app::getWindow()->getSize().y);

    if (TimeControl::Get()._play )
        eventOnUpdate();
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

        if (planet.second->_shader._shader ) {
            planet.second->_shader._shader->bind();
            planet.second->_shader.bindArgs(TimeControl::Get()._elapsedTime, TimeControl::Get().getDeltaTime() );
            planet.second->_shader._shader->uniform("planetRadius", planet.second->_size );
        }
        else
            ci::gl::color(ci::Color::hex(0xeeeeee));

        ci::gl::drawSolidCircle({}, planet.second->_size, lodExponent(planet.second->_size) );
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
        it.second->_shader.destroy();
        it.second.reset();
    }
}





void PlanetSystem::eventOnSetup() {
    for (auto i : _planets ) {
        if (i.second->_script._textSEntt.empty() ) continue;

        try {
            auto onSetup = luabridge::getGlobal(i.second->_script._luaState, Labels[Labels_OnSetup].first );
            auto planet = onSetup();

            if (onSetup.isFunction() ) {
                i.second->_pos = static_cast<Planet>(planet)._pos;
                i.second->_size = static_cast<Planet>(planet)._size;
            }
        }
        catch (std::exception& e ) {
            CI_LOG_EXCEPTION("", e);
            ErrorHandler::Get().push(Error(ErrorType::Error_Script, "Script: onSetup", e.what()) );
        }

    }

}

void PlanetSystem::eventOnUpdate() {
    for (auto i : _planets ) {
        if (i.second->_script._textSEntt.empty() ) continue;

        try {
            lua_State* L = i.second->_script._luaState;

            // Bind variables
            luabridge::setGlobal<float>(L, TimeControl::Get().getDeltaTime(), "deltaTime" );
            luabridge::setGlobal<float>(L, TimeControl::Get()._elapsedTime, "elapsedTime" );

            // Call onUpdate
            auto onUpdate = luabridge::getGlobal(L, Labels[Labels_OnUpdate].first );
            auto planet = onUpdate();

            if (onUpdate.isFunction() ) {
                i.second->_pos = static_cast<Planet>(planet)._pos;
                i.second->_size = static_cast<Planet>(planet)._size;
            }
        }
        catch (std::exception& e ) {
            CI_LOG_EXCEPTION("", e);
            ErrorHandler::Get().push(Error(ErrorType::Error_Script, "Script: onUpdate", e.what()) );

            TimeControl::Get()._play = false;
        }

    }

}
