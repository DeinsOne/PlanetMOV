extern "C" {
    #include "lualib.h"
    #include "lauxlib.h"
    #include "luaconf.h"
}

#include "LuaScript.h"
#include "LuaContext.h"
#include "LuaBridge/LuaBridge.h"
#include "labels.h"

#include "cinder/Log.h"

void LuaScript::destroy() {
    _pathSEntt.clear();
    _textSEntt.clear();
}


int LuaScript::bind() {
    _luaState = luaL_newstate();
    luaL_openlibs(_luaState );

    LuaContext::_luaBindAll(_luaState );


    auto has_fails = luaL_dofile(_luaState, _pathSEntt.c_str() );
    if (has_fails ) {
        throw std::runtime_error(lua_tostring(_luaState, -1 ));
    }

    return 0;
}

Error LuaScript::load(std::string path ) {
    _pathSEntt = path;

    try {
        if (!_pathSEntt.empty()) {
            std::ifstream ifs(_pathSEntt);
            _textSEntt = std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
            ifs.close();

            bind();
        }
    } catch (std::exception& e ) {
        lua_pop(_luaState, 1 );
        CI_LOG_EXCEPTION("", e );

        return Error(ErrorType::Error_Script, "Script", e.what() );
    }

    return Error(ErrorType::Error_None, "", "" );
}



int LuaScript::check() {
    if (_textSEntt.empty() ) return 0;
    std::string _beg = _pathSEntt;

    try {
        auto onSetup = luabridge::getGlobal(_luaState, Labels[Labels_OnSetup].first );
        if (!onSetup.isFunction() ) throw std::runtime_error(_beg + std::string(": onSetup is not a function") );
    } catch (std::exception& e ) {
        CI_LOG_EXCEPTION(_pathSEntt, e );
        ErrorHandler::Get().push(Error(ErrorType::Error_Script, "Script", e.what()) );
    }


    try {
        auto onUpdate = luabridge::getGlobal(_luaState, Labels[Labels_OnUpdate].first );
        if (!onUpdate.isFunction() ) throw std::runtime_error(_beg + std::string(": onUpdate is not a function") );
    } catch (std::exception& e ) {
        CI_LOG_EXCEPTION(_pathSEntt, e );
        ErrorHandler::Get().push(Error(ErrorType::Error_Script, "Script", e.what()) );
    }


    return 0;
}