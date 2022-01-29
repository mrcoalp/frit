include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.10.x)

set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(frit_test dummy.cpp)

target_link_libraries(frit_test frit gtest_main)

include(GoogleTest)

gtest_discover_tests(frit_test)
