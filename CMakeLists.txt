cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set(CMAKE_VERBOSE_MAKEFILE ON )
set(CMAKE_CXX_STANDARD 17)

project(PlanetMOV )

get_filename_component(CINDER_PATH "$ENV{HOME}/Cinder" ABSOLUTE )
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )


include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )


# libjsoncpp.so
add_library(jsnocpp SHARED
	${APP_PATH}/planet-mov/utils/jsoncpp/src/lib_json/json_reader.cpp
	${APP_PATH}/planet-mov/utils/jsoncpp/src/lib_json/json_value.cpp
	${APP_PATH}/planet-mov/utils/jsoncpp/src/lib_json/json_writer.cpp
)
target_include_directories(jsnocpp PRIVATE ${APP_PATH}/planet-mov/utils/jsoncpp/include )

# liblua.so
add_library(lua SHARED
	${APP_PATH}/planet-mov/utils/Lua/lapi.c
	${APP_PATH}/planet-mov/utils/Lua/lauxlib.c
	${APP_PATH}/planet-mov/utils/Lua/lbaselib.c
	${APP_PATH}/planet-mov/utils/Lua/lbitlib.c
	${APP_PATH}/planet-mov/utils/Lua/lcode.c
	${APP_PATH}/planet-mov/utils/Lua/lcorolib.c
	${APP_PATH}/planet-mov/utils/Lua/lctype.c
	${APP_PATH}/planet-mov/utils/Lua/ldblib.c
	${APP_PATH}/planet-mov/utils/Lua/ldebug.c
	${APP_PATH}/planet-mov/utils/Lua/ldo.c
	${APP_PATH}/planet-mov/utils/Lua/ldump.c
	${APP_PATH}/planet-mov/utils/Lua/lfunc.c
	${APP_PATH}/planet-mov/utils/Lua/lgc.c
	${APP_PATH}/planet-mov/utils/Lua/linit.c
	${APP_PATH}/planet-mov/utils/Lua/liolib.c
	${APP_PATH}/planet-mov/utils/Lua/llex.c
	${APP_PATH}/planet-mov/utils/Lua/lmathlib.c
	${APP_PATH}/planet-mov/utils/Lua/lmem.c
	${APP_PATH}/planet-mov/utils/Lua/loadlib.c
	${APP_PATH}/planet-mov/utils/Lua/lobject.c
	${APP_PATH}/planet-mov/utils/Lua/lopcodes.c
	${APP_PATH}/planet-mov/utils/Lua/loslib.c
	${APP_PATH}/planet-mov/utils/Lua/lparser.c
	${APP_PATH}/planet-mov/utils/Lua/lstate.c
	${APP_PATH}/planet-mov/utils/Lua/lstring.c
	${APP_PATH}/planet-mov/utils/Lua/lstrlib.c
	${APP_PATH}/planet-mov/utils/Lua/ltable.c
	${APP_PATH}/planet-mov/utils/Lua/ltablib.c
	${APP_PATH}/planet-mov/utils/Lua/ltests.c
	${APP_PATH}/planet-mov/utils/Lua/ltm.c
	${APP_PATH}/planet-mov/utils/Lua/lundump.c
	${APP_PATH}/planet-mov/utils/Lua/lutf8lib.c
	${APP_PATH}/planet-mov/utils/Lua/lvm.c
	${APP_PATH}/planet-mov/utils/Lua/lzio.c
)
target_include_directories(lua PRIVATE ${APP_PATH}/planet-mov/utils/Lua )



set(SRC_PLANET_MOVE
	${APP_PATH}/planet-mov/config/jsonConfig.cpp
	${APP_PATH}/planet-mov/config/stringFunctions.cpp

	# Main files
	${APP_PATH}/planet-mov/PlanetMOV.cpp
	${APP_PATH}/planet-mov/EveryTick.cpp
	${APP_PATH}/planet-mov/AppGui.cpp
	${APP_PATH}/planet-mov/Setup.cpp

	${APP_PATH}/planet-mov/context/PlanetSystem.cpp
	${APP_PATH}/planet-mov/CameraControl.cpp

	${APP_PATH}/planet-mov/utils/Lua
	${APP_PATH}/planet-mov/utils/LuaBridge/Source
)
set(INC_PLANET_MOVE
	${CINDER_PATH}/include
	${APP_PATH}/planet-mov
	${APP_PATH}/planet-mov/config
	${APP_PATH}/planet-mov/context

	# Utils
	${APP_PATH}/planet-mov/utils/jsoncpp/include
	${APP_PATH}/planet-mov/utils/Catch2/include
)


ci_make_app(
	APP_NAME    "PlanetMOV"
	CINDER_PATH ${CINDER_PATH}
	SOURCES     ${SRC_PLANET_MOVE}
	INCLUDES    ${INC_PLANET_MOVE}
	LIBRARIES	${jsnocpp} ${lua}
	ASSETS_PATH	"assets"
)
