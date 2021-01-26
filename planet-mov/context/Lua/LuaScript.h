#ifndef _PLANET_MOV_LUA_SCRIPT_H
#define _PLANET_MOV_LUA_SCRIPT_H

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
    #include "luaconf.h"
}

#include "LuaBridge/LuaBridge.h"
#include "ScriptableEntt.h"

class LuaScript : public ScriptableEntt {
    public : // Functions
        LuaScript() { }
        LuaScript(std::string script) { load(script ); }

        ~LuaScript() { destroy(); }
        virtual void destroy() override;


        virtual Error load(std::string path ) override;

        virtual int bind() override;
        virtual Error check() override;


    public :
        lua_State*      _luaState;

};


#endif // _PLANET_MOV_LUA_SCRIPT_H 
