#include "PlanetSystem.h"
#include <cinder/gl/gl.h>
#include <cinder/gl/Batch.h>
#include <iostream>

#include "jsonConfig.h"
#include "TimeControl.h"
#include "CameraControl.h"

#include "LuaContext.h"

#include "cinder/Log.h"


float lodExponent(float size ) {
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
        return;
    }

    for (auto i : _planetsConfig["planets"].getMemberNames() ) {
        std::string     _fShader = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_FShader, "assets/shaders/default.fs.glsl");
        std::string     _script = Json::getValueByLabel(_planetsConfig["planets"][i], Labels_Script, "");


        if (!i.empty() ) {
            _planets[i] = std::make_shared<Planet>();

            // Load shader
            auto er = _planets[i]->_shader.load(_fShader );
            ErrorHandler::Get().push(er );

            // Load script
            auto er1 = _planets[i]->_script.load(_script );
            ErrorHandler::Get().push(er1 );

            // Transfer arguments to planet 
            Planet::transferArgs(_planets[i].get(), _planetsConfig["planets"][i] );
        }

    }


    // FIXME: Check errors
    for (auto i : _planets ) {
        i.second->_script.check();
        i.second->_shader.check();
    }


    eventOnSetup();
}

void Planet::transferArgs(Planet* p, Json::Value& value) {
    p->_args = value;
}

luabridge::LuaRef Planet::bindTable(Planet* p ) {
    luabridge::LuaRef _args = luabridge::newTable(p->_script._luaState );

    for (auto c : p->_args.getMemberNames()) {
        if (p->_args[c.c_str()].isBool())
            _args[c.c_str()] = p->_args[c.c_str()].asBool();
        else if (p->_args[c.c_str()].isDouble())
            _args[c.c_str()] = p->_args[c.c_str()].asFloat();
        else if (p->_args[c.c_str()].isInt())
            _args[c.c_str()] = p->_args[c.c_str()].asInt();
        else if (p->_args[c.c_str()].isString())
            _args[c.c_str()] = p->_args[c.c_str()].asCString();
        else if (p->_args[c.c_str()].isArray()) {
            if (p->_args[c.c_str()].size() > 2) {
                _args[c.c_str()] = luabridge::newTable(p->_script._luaState);

                if (p->_args[c.c_str()][0].isInt()) {
                    for (int k = 0; k < p->_args[c.c_str()].size(); k++ )
                        _args[c.c_str()][k] = p->_args[c.c_str()][k].asInt();
                }
                else if (p->_args[c.c_str()][0].isDouble()) {
                    for (int k = 0; k < p->_args[c.c_str()].size(); k++ )
                        _args[c.c_str()][k] = p->_args[c.c_str()][k].asFloat();
                }
            }
            else {
                if (p->_args[c.c_str()][0].isInt()) {
                    _args[c.c_str()] = glm::vec2(p->_args[c.c_str()][0].asInt(), p->_args[c.c_str()][1].asInt());
                }
                else if (p->_args[c.c_str()][0].isDouble()) {
                    _args[c.c_str()] = glm::vec2(p->_args[c.c_str()][0].asFloat(), p->_args[c.c_str()][1].asFloat());
                }
            }
        }
    }

    return _args;
}

void Planet::encodeArgs(Planet* p, luabridge::LuaRef table) {
    table.push(p->_script._luaState);
    luabridge::push(p->_script._luaState, luabridge::Nil());
    while (lua_next (p->_script._luaState, -2)) {
        luabridge::LuaRef key = luabridge::LuaRef::fromStack(p->_script._luaState, -2);
        luabridge::LuaRef val = luabridge::LuaRef::fromStack(p->_script._luaState, -1);
        
        if (val.isBool())
            p->_args[key.tostring().c_str()] = val.cast<bool>();
        else if (val.isNumber())
            p->_args[key.tostring().c_str()] = val.cast<float>();
        else if (val.isString())
            p->_args[key.tostring().c_str()] = val.cast<const char*>();
        else if (val.isInstance<glm::vec2>()) {
            glm::vec2 vector = val.cast<glm::vec2>();
            p->_args[key.tostring().c_str()][0] = vector.x;
            p->_args[key.tostring().c_str()][1] = vector.y;
        }
        else if (val.length() > 0 ) {            
            for (int i = 0; i < val.length(); i++ )
                p->_args[key.tostring().c_str()][i] = val.cast<float>();
        }

        lua_pop(p->_script._luaState, 1);
    }
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
        ci::gl::setModelMatrix(ci::translate(glm::vec3(Json::getValueByLabel(planet.second->_args, Labels_Pos, glm::vec2(0,0)), 0.0)));

        if (_selectedPlanet == planet.first)
        {
            ci::gl::getStockShader(ci::gl::ShaderDef().color())->bind();
            ci::gl::color(ci::Color::hex(_colorOfBorder));
            ci::gl::drawSolidCircle({}, 
                Json::getValueByLabel(planet.second->_args, Labels_Radius, 1.0f) + _radiusOfBorder, Json::getValueByLabel(planet.second->_args, Labels_Radius, 1.0f) * 12
            );
        }

        if (planet.second->_shader._shader ) {
            planet.second->_shader._shader->bind();
            planet.second->_shader.bindArgs(TimeControl::Get()._elapsedTime, TimeControl::Get().getDeltaTime() );
            planet.second->_shader._shader->uniform("planetRadius", Json::getValueByLabel(planet.second->_args, Labels_Radius, 1.0f));
        }
        else
            ci::gl::color(ci::Color::hex(0xeeeeee));

        ci::gl::drawSolidCircle({}, Json::getValueByLabel(planet.second->_args, Labels_Radius, 1.0f), lodExponent(Json::getValueByLabel(planet.second->_args, Labels_Radius, 1.0f)) );
    }

    // Draw separeate fbo to give possibility planet picking
    _planetPicker->bindFramebuffer();
    ci::gl::clear(ci::Color::hex(0x0000));
    ci::gl::setMatrices(CameraControl::Get()._camera);

    auto planet = _planets.begin();
    for (int i = 0; i < _planets.size(); i++)
    {
        ci::gl::setModelMatrix(ci::translate(glm::vec3(Json::getValueByLabel(planet->second->_args, Labels_Pos, glm::vec2(0,0)), 0.0)));

        ci::gl::getStockShader(ci::gl::ShaderDef().color())->bind();
        ci::gl::color(0, ((float)(i + 1)) / ((float)_planets.size()), 0, 1);
        ci::gl::drawSolidCircle({}, Json::getValueByLabel(planet->second->_args, Labels_Radius, 1.0f), Json::getValueByLabel(planet->second->_args, Labels_Radius, 1.0f) * 12);
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
            auto planet = onSetup(Planet::bindTable(i.second.get()) );

            Planet::encodeArgs(i.second.get(), planet);
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

            Planet::encodeArgs(i.second.get(), planet);
        }
        catch (std::exception& e ) {
            CI_LOG_EXCEPTION("", e);
            ErrorHandler::Get().push(Error(ErrorType::Error_Script, "Script: onUpdate", e.what()) );

            TimeControl::Get()._play = false;
        }

    }

}
