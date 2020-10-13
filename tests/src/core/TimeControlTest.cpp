#ifndef INTERNAL_TESTS
 #define CATCH_CONFIG_MAIN
#endif // INTERNAL_TEST
#include "catch2/catch.hpp"

#include "TimeControl.h"

#include <thread>

TEST_CASE("Time control tests", "[TimeControl]" ) {
    TimeControl::Get().initTimeControl();
    TimeControl::Get()._play = true;
    float _oldTime = 0.0;

    std::this_thread::sleep_for(std::chrono::milliseconds(10) );

    TimeControl::Get().updateTimeControl();
    _oldTime = TimeControl::Get()._elapsedTime;

    SECTION("Test elapsed time" ) {
        REQUIRE(TimeControl::Get()._elapsedTime > 0.0 );
    }
    SECTION("Test delta time" ) {
        REQUIRE(TimeControl::Get().getDeltaTime() > 0.0 );
    }


    SECTION("Stop play" ) {
        TimeControl::Get()._play = false;
        TimeControl::Get().updateTimeControl();


        CHECK((TimeControl::Get()._elapsedTime == _oldTime) );
    }

}
