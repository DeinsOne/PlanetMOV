cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set(CMAKE_VERBOSE_MAKEFILE ON )
set(CMAKE_CXX_STANDARD 17)

project(PlanetMOVTests )

get_filename_component(CINDER_PATH "$ENV{HOME}/Cinder" ABSOLUTE )
get_filename_component(CURRENT_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )


include_directories(
    ${CINDER_PATH}/include
    ${CURRENT_FOLDER}/../planet-mov
    ${CURRENT_FOLDER}/../planet-mov/utils/Catch2/single_include
    ${CURRENT_FOLDER}/../planet-mov/utils/jsoncpp/include
    ${CURRENT_FOLDER}/../planet-mov/config
)


# Core Tests
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CURRENT_FOLDER}/bin")
add_executable(TimeControlTest "core/TimeControlTest.cpp" )