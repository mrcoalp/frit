cmake_minimum_required(VERSION 3.8)

project(frit-language)

option(FRIT_BUILD_TESTS "Build Frit tests" OFF)

set(CMAKE_MACOSX_RPATH 1)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

add_subdirectory(lib)

add_executable(frit-bin src/main.cpp)

target_link_libraries(frit-bin frit)

set_target_properties(frit-bin PROPERTIES OUTPUT_NAME frit)

if (FRIT_BUILD_TESTS)
    add_subdirectory(test)
endif ()

install(TARGETS frit-bin
        LIBRARY DESTINATION lib COMPONENT Runtime
        ARCHIVE DESTINATION lib COMPONENT Development
        RUNTIME DESTINATION bin COMPONENT Runtime
        PUBLIC_HEADER DESTINATION include/frit COMPONENT Development
        BUNDLE DESTINATION bin COMPONENT Runtime)
