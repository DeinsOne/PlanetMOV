#ifndef INTERNAL_TESTS
 #define CATCH_CONFIG_MAIN
#endif // INTERNAL_TEST
#include "catch2/catch.hpp"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
    #include "luaconf.h"
}


TEST_CASE("Lua default state loading", "[lua]" ) {
    // CHECK(true );
    lua_State* L = luaL_newstate();
    luaL_openlibs(L );


    SECTION("Register function") {
        REQUIRE(!luaL_dostring(L, "print('Hi')") );

        CHECK(!luaL_dostring(L, "a = 1 + 2") );

        CHECK(!luaL_dostring(L, "b = 2^2") );
    }

}
