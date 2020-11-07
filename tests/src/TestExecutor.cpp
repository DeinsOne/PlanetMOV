#include <iostream>
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#define INTERNAL_TESTS
#include "core/JsonConfigTest.cpp"
#include "core/TimeControlTest.cpp"

#include "lua/luaContext.cpp"
