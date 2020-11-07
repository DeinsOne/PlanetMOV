cmake_minimum_required( VERSION 2.8 FATAL_ERROR )

get_filename_component(TESTS_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TESTS_FOLDER}/bin )

project(PlanetMOVTests )

# General include directories for all tests
set(TEST_GENERAL_INCLUDE
    ${TESTS_FOLDER}/../planet-mov
    ${TESTS_FOLDER}/../planet-mov/utils/Catch2/single_include
)



# General linck libraries for tests
set(LIB_JSONCPP "${TESTS_FOLDER}/../build/libjsnocpp.so" )
set(LIB_LUA "${TESTS_FOLDER}/../build/liblua.so" )



# Core tests
set(TEST_CORE_SOURCES
    ${TESTS_FOLDER}/src/core/JsonConfigTest.cpp
    ${TESTS_FOLDER}/src/core/TimeControlTest.cpp
)
set(TEST_CORE_INCLUDE
    $ENV{HOME}/Cinder/include
)

foreach( SourceFile ${TEST_CORE_SOURCES} )
    get_filename_component(SourceFileName ${SourceFile} NAME_WLE )

    include_directories(${TEST_GENERAL_INCLUDE} ${TEST_CORE_INCLUDE} )
    add_executable(${SourceFileName} ${SourceFile} )
    set_target_properties(${SourceFileName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TESTS_FOLDER}/bin/core")
    target_link_libraries(${SourceFileName} ${LIB_JSONCPP} )

endforeach()



# Lua tests
set(TEST_LUA_SOURCES
    ${TESTS_FOLDER}/src/lua/luaContext.cpp
)
set(TEST_LUA_INCLUDE
    ${TESTS_FOLDER}/../planet-mov/utils/Lua
)

foreach( SourceFile ${TEST_LUA_SOURCES} )
    get_filename_component(SourceFileName ${SourceFile} NAME_WLE )

    include_directories(${TEST_GENERAL_INCLUDE} ${TEST_LUA_INCLUDE} )
    add_executable(${SourceFileName} ${SourceFile} )
    set_target_properties(${SourceFileName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TESTS_FOLDER}/bin/lua")
    target_link_libraries(${SourceFileName} ${LIB_LUA} )

endforeach()



# Universal executable to run all tests
add_executable(TestExecutor "${TESTS_FOLDER}/src/TestExecutor.cpp" )
set_target_properties(TestExecutor PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TESTS_FOLDER}/bin")
target_include_directories(TestExecutor 
    PRIVATE ${TEST_GENERAL_INCLUDE}
    PRIVATE ${TEST_CORE_INCLUDE}
    PRIVATE ${TEST_LUA_INCLUDE}
)
target_link_libraries(TestExecutor ${LIB_JSONCPP} ${LIB_LUA} )
