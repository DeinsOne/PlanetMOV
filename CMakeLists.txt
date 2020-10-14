cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
# set(CMAKE_VERBOSE_MAKEFILE ON )
set(CMAKE_CXX_STANDARD 17)

project(PlanetMOV VERSION 0.0.1 )

get_filename_component(CINDER_PATH "$ENV{HOME}/Cinder" ABSOLUTE )
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )


include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )


set(SRC_PLANET_MOVE
	# Utils
	${APP_PATH}/planet-mov/utils/jsoncpp/src/lib_json/json_reader.cpp
	${APP_PATH}/planet-mov/utils/jsoncpp/src/lib_json/json_value.cpp
	${APP_PATH}/planet-mov/utils/jsoncpp/src/lib_json/json_writer.cpp


	${APP_PATH}/planet-mov/config/jsonConfig.cpp
	${APP_PATH}/planet-mov/config/stringFunctions.cpp

	# Main files
	${APP_PATH}/planet-mov/PlanetMOV.cpp
	${APP_PATH}/planet-mov/EveryTick.cpp
	${APP_PATH}/planet-mov/AppGui.cpp
	${APP_PATH}/planet-mov/Setup.cpp

	${APP_PATH}/planet-mov/context/PlanetSystem.cpp
	${APP_PATH}/planet-mov/CameraControl.cpp
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
	ASSETS_PATH	"assets"
)
