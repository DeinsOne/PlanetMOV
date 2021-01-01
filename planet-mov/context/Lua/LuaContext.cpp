#include "LuaContext.h"

extern "C" {
    #include "lualib.h"
    #include "lauxlib.h"
    #include "luaconf.h"
}

#include "LuaBridge/LuaBridge.h"
#include "cinder/Log.h"

#include "PlanetSystem.h"
#include "TimeControl.h"

luabridge::LuaRef getPlanet(std::string name ) {
    // printf("call: getPlanet(");

    auto _pl = PlanetSystem::Get()._planets.find(name);
    // auto table = Planet::_bindTable(_pl->second.get());
    // printf("%s)\n", _pl->first.c_str());
    auto table = luabridge::newTable(_pl->second->_script._luaState);
    if (name == "Sun") {
        table["pos"] = glm::vec2(0,0);
        table["size"] = 7.0f;
        table["fShader"] = "samples/shaders/sunShader.fs.glsl";
    }
    else if (name == "Earth") {
        table["script"] = "samples/scripts/earthScript.lua";
        table["fShader"] = "samples/shaders/earthShader.fs.glsl";
        table["EarthS"] = 26.0f;
        table["velocity"] = 1.0f;
    }
    else if (name == "Moon") {
        table["size"] = 1.3f;
        table["script"] = "samples/scripts/moonScript.lua";
        table["fShader"] = "samples/shaders/moonShader.fs.glsl";
        table["MoonS"] = 9.0f;
    }

    return table;
}

// luabridge::LuaRef getPlanets(lua_State* L ) {
//     luabridge::LuaRef planets = luabridge::newTable(L );
//     printf("call: getPlanets() {");

//     for (auto i : PlanetSystem::Get()._planets ) {
//         printf(" %s,", i.first.c_str());
//         planets[i.first.c_str()] = getPlanet(i.first);
//     }

//     printf(" }\n");
//     return planets;
// }

// TODO:
void LuaContext::_luaBindCore(lua_State* L ) {
    luabridge::getGlobalNamespace(L)
        .addFunction("getPlanet", getPlanet )
        // .addFunction("getPlanets", getPlanets )
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



