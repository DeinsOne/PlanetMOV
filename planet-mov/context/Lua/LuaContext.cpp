#include "LuaContext.h"

extern "C" {
    #include "lualib.h"
    #include "lauxlib.h"
    #include "luaconf.h"
}

#include "LuaBridge/LuaBridge.h"
#include "cinder/Log.h"
#include "array"

#include "PlanetSystem.h"

Planet* getPlanet(std::string name ) {
    auto it = PlanetSystem::Get()._planets.find(name);
    if (it->second )
        return PlanetSystem::Get()._planets[name].get();
    else
        return nullptr;
}

luabridge::LuaRef getPlanets(lua_State* L ) {
    luabridge::LuaRef planets = luabridge::newTable(L );

    std::map<std::string, std::shared_ptr<Planet>>::iterator iter;
    for (iter = PlanetSystem::Get()._planets.begin(); iter != PlanetSystem::Get()._planets.end(); iter++) {
        std::string id = iter->first;
        Planet* planet = iter->second.get();
        planets[id] = planet;
    }

    return planets;
}

// TODO:
void LuaContext::_luaBindCore(lua_State* L ) {
    luabridge::getGlobalNamespace(L)
        .beginClass<Planet>("Planet")
            .addConstructor<void (*)(glm::vec2, float)>()
            .addProperty("size", &Planet::_size )
            .addProperty("pos", &Planet::_pos )
            .addProperty("mass", &Planet::_mass )
            .addFunction("printFields", &Planet::printFields )
            .addFunction("onSetup", &Planet::onSetup )
            .addFunction("onUpdate", &Planet::onUpdate )

        .endClass()

        .addFunction("getPlanet", getPlanet )
        .addFunction("getPlanets", getPlanets )
    ;

}


// TODO:
void LuaContext::_luaBindGlm(lua_State* L ) {

    luabridge::getGlobalNamespace(L)
        .beginClass<glm::vec2>("vec2")
            .addConstructor<void (*)(float, float)>()
            .addData("x", &glm::vec2::x )
            .addData("y", &glm::vec2::y )
            .addFunction("__add", std::function<glm::vec2 (glm::vec2*, glm::vec2)> ( [](glm::vec2* a, glm::vec2 b) { return *a + b; } ) )
            .addFunction("__sub", std::function<glm::vec2 (glm::vec2*, glm::vec2)> ( [](glm::vec2* a, glm::vec2 b) { return *a - b; } ) )
            .addFunction("__mul", std::function<glm::vec2 (glm::vec2*, float)> ( [](glm::vec2* a, float b) { return *a * b; } ) )
            .addFunction("__div", std::function<glm::vec2 (glm::vec2*, float)> ( [](glm::vec2* a, float b) { return *a / b; } ) )
        .endClass()

        .beginNamespace("glm")
            //  Geometry functions
            .addFunction("cross", std::function<glm::vec2 (glm::vec2)> ( [](glm::vec2 a) { return glm::vec2(a.y, -a.x); } ))
            .addFunction("distance", std::function<float (glm::vec2, glm::vec2)> ( [](glm::vec2 a, glm::vec2 b) { return glm::distance(a,b); } ))
            .addFunction("dot", std::function<float (glm::vec2, glm::vec2)> ( [](glm::vec2 a, glm::vec2 b) { return glm::dot(a,b); } ))
            .addFunction("faceforward", std::function<glm::vec2 (glm::vec2, glm::vec2, glm::vec2)> ( [](glm::vec2 a, glm::vec2 b, glm::vec2 c) { return glm::faceforward(a,b, c); } ))
            .addFunction("length", std::function<float (glm::vec2)> ( [](glm::vec2 a) { return glm::length(a ); }))
            .addFunction("normalize", std::function<glm::vec2 (glm::vec2)> ( [](glm::vec2 a) { return glm::normalize(a ); } ))
            .addFunction("reflect", std::function<glm::vec2 (glm::vec2, glm::vec2)> ( [](glm::vec2 a, glm::vec2 b) { return glm::reflect(a,b); } ))
            // Common functions
            .addFunction("abs", std::function<float (float)> ( [](float a ) { return glm::abs(a ); }))
            .addFunction("clamp", std::function<float (float, float, float)> ( [](float a, float b, float c ) { return glm::clamp(a, b, c ); }))
        .endNamespace()
    ;

}


void LuaContext::_luaBindAll(lua_State* L ) {
    _luaBindGlm(L );
    _luaBindCore(L );
}



