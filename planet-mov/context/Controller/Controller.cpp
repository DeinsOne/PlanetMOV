#include "Controller.h" 
#include "PlanetSystem.h"
#include "TimeControl.h"

#include "cinder/Log.h"


void Controller::_encodeArgs(luabridge::LuaRef* planets) {
    if (!planets->isTable()) {
        throw std::runtime_error(_script._pathSEntt + std::string(" -> ") + std::string("onUpdate returned no table"));
    }

    planets->push(planets->state());
    luabridge::push(planets->state(), luabridge::Nil());

    while (lua_next(planets->state(), -2)) {
        // Planet's name
        luabridge::LuaRef key = luabridge::LuaRef::fromStack(planets->state(), -2);
        // Planet's table
        luabridge::LuaRef val = luabridge::LuaRef::fromStack(planets->state(), -1);
        if (!val.isTable()) goto cnt;


        // val.push(val.state());
        luabridge::push(val.state(), luabridge::Nil());

        while (lua_next(val.state(), -2)) {
            // Field's name
            luabridge::LuaRef key1 = luabridge::LuaRef::fromStack(val.state(), -2);
            // Field's value
            luabridge::LuaRef val1 = luabridge::LuaRef::fromStack(val.state(), -1);

            if (val1.isBool())
                PlanetSystem::Get()._planets[key.tostring()]->_args[key1.tostring()] = val1.cast<bool>();
            else if (val1.isNumber())
                PlanetSystem::Get()._planets[key.tostring()]->_args[key1.tostring()] = val1.cast<float>();
            else if (val1.isString())
                PlanetSystem::Get()._planets[key.tostring()]->_args[key1.tostring()] = val1.cast<const char*>();
            else if (val1.isInstance<glm::vec2>()) {
                glm::vec2 vector = val1.cast<glm::vec2>();
                PlanetSystem::Get()._planets[key.tostring()]->_args[key1.tostring()][0] = vector.x;
                PlanetSystem::Get()._planets[key.tostring()]->_args[key1.tostring()][1] = vector.y;
            }

            lua_pop(val1.state(), 1);
        }



        cnt:
        lua_pop(planets->state(), 1);
    }
}


void Controller::onUpdate() {
    try {
        // Bind variables
        luabridge::setGlobal<float>(_script._luaState, TimeControl::Get().getDeltaTime(), "deltaTime" );
        luabridge::setGlobal<float>(_script._luaState, TimeControl::Get()._elapsedTime, "elapsedTime" );

        // Pass planets list
        auto planets = luabridge::newTable(_script._luaState);
        for (auto c : PlanetSystem::Get()._planets ) {
            planets[c.first.c_str()] = Planet::_bindTable(c.second.get(), _script._luaState);
        }

        // Call onUpdate
        auto onUpdate = luabridge::getGlobal(_script._luaState, Labels[Labels_OnUpdate].first );
        auto planetsTable = onUpdate(planets);

        _encodeArgs(&planetsTable);
    }
    catch (std::exception& e ) {
        CI_LOG_EXCEPTION("", e);
        ErrorHandler::Get().push(Error(ErrorType::Error_Script, "Script: onUpdate", e.what()) );

        TimeControl::Get()._play = false;
    }

}