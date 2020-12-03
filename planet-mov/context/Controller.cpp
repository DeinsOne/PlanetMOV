#include "Controller.h"
#include "labels.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
    #include "luaconf.h"
}

#include "LuaBridge/LuaBridge.h"
#include "PlanetSystem.h"

#include "cinder/Log.h"

void Controller::check() {
    try {
        auto onUpdate = luabridge::getGlobal(_script._luaState, Labels[Labels_OnUpdate].first );
        if (!onUpdate.isFunction() ) throw std::runtime_error(_script._pathSEntt + std::string(": onUpdate is not a function") );
    } catch (std::exception& e ) {
        CI_LOG_EXCEPTION(_script._pathSEntt, e );
        ErrorHandler::Get().push(Error(ErrorType::Error_Script, "Controller Script", e.what()) );
    }
}

bool Controller::empty() {
    try {
        auto onUpdate = luabridge::getGlobal(_script._luaState, Labels[Labels_OnUpdate].first );
        if (!onUpdate.isFunction() || _script._textSEntt.empty() ) throw std::runtime_error(_script._pathSEntt + std::string(": onUpdate is not a function") );
    } catch (std::exception& e ) {
        return true;
    }

    return false;
}

void Controller::onUpdate() {
    auto onUpdate = luabridge::getGlobal(_script._luaState, Labels[Labels_OnUpdate].first );
    auto planets = onUpdate();

    if (planets.isTable() ) {
        for (auto i : PlanetSystem::Get()._planets ) {
            luabridge::LuaRef planet = planets.rawget(i.first );

            i.second->_pos = static_cast<Planet>(planet)._pos;
            i.second->_size = static_cast<Planet>(planet)._size;
            i.second->_mass = static_cast<Planet>(planet)._mass;
        }
    }

}

