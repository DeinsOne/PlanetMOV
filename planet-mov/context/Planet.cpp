#include "Planet.h"

extern "C" {
    #include "lualib.h"
    #include "lauxlib.h"
    #include "luaconf.h"
}
#include "LuaBridge/LuaBridge.h"
#include "cinder/Log.h"

Planet::Planet(glm::vec2 pos, float size) : _pos(pos), _size(size)
{
}


static void setFields(Planet* pl, luabridge::LuaRef result ) {
    // printf("Info about onSetup output : type - %d | str - %s\n", result.type(), result.tostring().c_str() );

    pl->_size = static_cast<Planet>(result)._size;
    pl->_pos = static_cast<Planet>(result)._pos;

}

void Planet::BindShader(float elapsedTime, float deltaTime)
{
    _shader->bind();

    _shader->uniform("elapsedTime", elapsedTime);
    _shader->uniform("deltaTime", deltaTime);

    _shader->uniform("planetRadius", _size);
}



int Planet::callOnSetup() {
    if (this->_script._scriptText.empty() ) return 0;

    try {
        auto pt = luabridge::getGlobal(_script._luaState, "onSetup" )();

        setFields(this, pt ); // Set result of script call to current planet
    }
    catch (luabridge::LuaException& e ) {
        CI_LOG_EXCEPTION("", e );
        return 1;
    }

    catch (...) { 
        CI_LOG_E("Err unknown[" <<  __LINE__ << "]");
    }

    return 0;
}



int Planet::callOnUpdate() {
    if (this->_script._scriptText.empty() ) return 0;

    try {
        auto pt = luabridge::getGlobal(_script._luaState, "onUpdate" )();

        setFields(this, pt ); // Set result of script call to current planet
    }
    catch (luabridge::LuaException& e ) {
        CI_LOG_EXCEPTION("", e );
        return 1;
    }

    catch (...) { 
        CI_LOG_E("Err unknown[" <<  __LINE__ << "]");
    }

    return 0;
}


int Planet::callOnRender() {
    if (this->_script._scriptText.empty() ) return 0;

    try {
        auto pt = luabridge::getGlobal(_script._luaState, "onRender" )();

        // setFields(this, pt ); // Set result of script call to current planet
    }
    catch (luabridge::LuaException& e ) {
        CI_LOG_EXCEPTION("", e );
        return 1;
    }

    catch (...) { 
        CI_LOG_E("Err unknown[" <<  __LINE__ << "]");
    }

    return 0;
} 
