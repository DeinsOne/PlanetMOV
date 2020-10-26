#ifndef _PLANET_MOV_LUA_SCRIPT_H
#define _PLANET_MOV_LUA_SCRIPT_H

extern "C" {
    #include "lua.h"
}

#include "LuaContext.h"

#include <string>
#include <fstream>
#include <stdexcept>

class LuaScript {
    private :
        void initLuaState();

    public : // Functions
        LuaScript() { }
        LuaScript(std::string script) { loadScript(); }

        ~LuaScript() { destroy(); }

        void destroy();


        // loads script by "_pathToScript" path. if _pathToScript is empty or refers nonexisting file LuaScript destroys all fields
        void loadScript();

        // loads script by given path
        void loadScript(std::string path );

        void reloadScript() { loadScript(); }

    public : // Variables
        std::string     _pathToScript;
        std::string     _scriptText;

        lua_State*      _luaState;

};


#endif // _PLANET_MOV_LUA_SCRIPT_H 
