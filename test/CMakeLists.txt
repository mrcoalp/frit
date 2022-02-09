cmake_minimum_required(VERSION 3.14.5)

include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.10.x)

set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(frit-test lexer.test.cpp)

target_link_libraries(frit-test frit gtest_main)

include(GoogleTest)

gtest_discover_tests(frit-test)

set_target_properties(frit-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
