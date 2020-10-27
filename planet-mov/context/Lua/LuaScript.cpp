extern "C" {
    #include "lualib.h"
    #include "lauxlib.h"
    #include "luaconf.h"
}

#include "LuaScript.h"
#include "cinder/Log.h"
#include "LuaBridge/LuaBridge.h"

void LuaScript::destroy() {
    _pathToScript.clear();
    _scriptText.clear();
}


void LuaScript::initLuaState() {
    _luaState = luaL_newstate();
    luaL_openlibs(_luaState );

    LuaContext::_luaBindAll(_luaState );


    auto has_fails = luaL_dofile(_luaState, _pathToScript.c_str() );
    if (has_fails ) {
        throw std::runtime_error(lua_tostring(_luaState, -1 ));
    }

}

void LuaScript::loadScript(std::string path ) {
    if (!path.empty() )
        _pathToScript = path;
        loadScript();
}

void LuaScript::loadScript() {
    if (!_pathToScript.empty() ) {
        try {
            std::ifstream ifs(_pathToScript);
            _scriptText = std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
            ifs.close();

            initLuaState();
        } catch (std::exception& e ) {
            lua_pop(_luaState, 1 );
            CI_LOG_EXCEPTION("", e );
            destroy();
        }
    }
}