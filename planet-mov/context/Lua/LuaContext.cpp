#include "LuaContext.h"

extern "C" {
    #include "lualib.h"
    #include "lauxlib.h"
    #include "luaconf.h"
}

#include "LuaBridge/LuaBridge.h"
#include "cinder/Log.h"

// #include "Planet.h"

#include "PlanetSystem.h"

Planet* getPlanet(std::string name ) { return PlanetSystem::Get()._planets[name].get(); }

// TODO:
void LuaContext::_luaBindCore(lua_State* L ) {


    luabridge::getGlobalNamespace(L)
        .beginClass<Planet>("Planet")
            .addConstructor<void (*)(glm::vec2, float)>()

            .addProperty("size", &Planet::_size )
            .addProperty("pos", &Planet::_pos )

            .addFunction("printFields", &Planet::printFields )
            /* ... */

        .endClass()

        .addFunction("getPlanet", getPlanet )
    ;


}

// TODO:
void LuaContext::_luaBindGlm(lua_State* L ) {
    luabridge::getGlobalNamespace(L)
        .beginClass<glm::vec2>("vec2")
            .addConstructor<void (*)(float, float)>()

            .addProperty("x", &glm::vec2::x )
            .addProperty("y", &glm::vec2::y )

            /* ... */

        .endClass()
    ;
}


void LuaContext::_luaBindAll(lua_State* L ) {
    _luaBindGlm(L );
    _luaBindCore(L );
}



