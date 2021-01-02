#ifndef _PLANET_MOV_PLANET_H
#define _PLANET_MOV_PLANET_H

#include <string>

#include "LuaScript.h"
#include "Shader.h"

#include "jsonConfig.h"

class Planet {
    public :
        Shader                  _shader;
        LuaScript               _script;

        Json::Value             _args;

        Planet() { }


        // Fills p->_args with value
        static void _transferArgs(Planet* p, Json::Value& value);

        // Fills p->_args with lua table
        static void _encodeArgs(Planet* p, luabridge::LuaRef table);

        // Allocates new table on L and fills it with p->_args
        static luabridge::LuaRef _bindTable(Planet* p, lua_State* L ); // Creates and returns lua table

};


#endif // _PLANET_MOV_PLANET_H