#ifndef INTERNAL_TESTS
 #define CATCH_CONFIG_MAIN
#endif // INTERNAL_TEST
#include "catch2/catch.hpp"

#include "config/jsonConfig.h"
#include "config/jsonConfig.cpp"

TEST_CASE("JsonConfig load empty Json file to test its size", "[core][configs]" ) {
    Json::Value _config;

    std::ifstream configFile("bin/assets/emptyJson.json" );
    configFile >> _config;


    CHECKED_IF(configFile.is_open() ) {
        CHECK(_config.size() == 0 );
    }

    configFile.close();

}


TEST_CASE("JsonConfig load testPlanetSystem.json to check config tools", "[core][configs]") {
    Json::Value _config;

    std::ifstream configFile("bin/assets/testPlanetSystem.json" );
    configFile >> _config;


    CHECKED_IF(configFile.is_open() ) {
        CHECK_NOFAIL(_config.size() == 1 );
        CHECK_NOFAIL(_config["planets"].size() == 2 );
    }

    configFile.close();


    SECTION("Check getValueExtracted tool" ) {
        REQUIRE_THAT(Json::getValueExtracted(_config["planets"][0]["label"], std::string()), Catch::Equals("Sun") );
        CHECK_NOFAIL((int)Json::getValueExtracted(_config["planets"][0]["size"], 0.0) == 7 );

        REQUIRE_THAT(Json::getValueExtracted(_config["planets"][1]["label"], std::string()), Catch::Equals("Earth") );
        CHECK_NOFAIL((int)Json::getValueExtracted(_config["planets"][1]["size"], 0.0) == 2.4 );

        CHECK_NOFAIL(Json::getValueExtracted(_config["planets"][0]["pos"][0], 0.0f) == 0.0 );
        CHECK_NOFAIL(Json::getValueExtracted(_config["planets"][0]["pos"][1], 0.0f) == 0.0 );

        CHECK_NOFAIL(Json::getValueExtracted(_config["planets"][1]["pos"][0], 0.0f) == 26.0 );
        CHECK_NOFAIL(Json::getValueExtracted(_config["planets"][1]["pos"][1], 0.0f) == 0.0 );
    }


    SECTION("Check getValueByLabel tool" ) {
        REQUIRE_THAT(Json::getValueByLabel(_config["planets"][0], Labels_ID, std::string()), Catch::Equals("Sun") );
        CHECK((int)Json::getValueByLabel(_config["planets"][0], Labels_Radius, 0.0f) == 7 );

        REQUIRE_THAT(Json::getValueByLabel(_config["planets"][1], Labels_ID, std::string()), Catch::Equals("Earth") );
        CHECK_NOFAIL((int)Json::getValueByLabel(_config["planets"][1], Labels_Radius, 0.0f) == 2.4 );

        CHECK(Json::getValueByLabel(_config["planets"][0], Labels_Pos, glm::vec2()) == glm::vec2() );
        CHECK(Json::getValueByLabel(_config["planets"][1], Labels_Pos, glm::vec2()) == glm::vec2(26,0) );
    }
}