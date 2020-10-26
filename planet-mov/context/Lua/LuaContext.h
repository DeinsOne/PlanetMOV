#ifndef _PLANET_MOV_LUA_CONTEXT_H
#define _PLANET_MOV_LUA_CONTEXT_H

#include <string>

extern "C"
{
#include "lua.h"
}

namespace LuaContext
{

    void _luaBindCore(lua_State *L);

    void _luaBindGlm(lua_State *L);

    /**
     * Binds all predefind items to lua state :
     *  - _luaBindCore
     *  - _luaBindGlm
    */
    void _luaBindAll(lua_State *L);

} // namespace LuaContext

#endif // _PLANET_MOV_LUA_CONTEXT_H