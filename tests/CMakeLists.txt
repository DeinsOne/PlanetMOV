cmake_minimum_required( VERSION 2.8 FATAL_ERROR )

get_filename_component(TESTS_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

project(PlanetMOVTests )

set(TEST_GENERAL_INCLUDE
    ${TESTS_FOLDER}/../planet-mov/utils/Catch2/single_include
)



# Core tests
set(TEST_CORE_SOURCES
    ${TESTS_FOLDER}/src/core/TimeControlTest.cpp
)
set(TEST_CORE_INCLUDE
    $ENV{HOME}/Cinder/include
    ${TESTS_FOLDER}/../planet-mov
)

foreach( SourceFile ${TEST_CORE_SOURCES} )
    get_filename_component(SourceFileName ${SourceFile} NAME_WLE )

    include_directories(${TEST_GENERAL_INCLUDE} ${TEST_CORE_INCLUDE} )
    add_executable(${SourceFileName} ${SourceFile} )
    set_target_properties(${SourceFileName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TESTS_FOLDER}/bin/core")

endforeach()



# Universal executable to run all tests
add_executable(TestExecutor "${TESTS_FOLDER}/src/TestExecutor.cpp" )
set_target_properties(TestExecutor PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TESTS_FOLDER}/bin")
# target_compile_definitions(TestExecutor PRIVATE INTERNAL_TESTS)
