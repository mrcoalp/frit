cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(frit SHARED src/lexer.cpp)

include(GenerateExportHeader)

generate_export_header(frit EXPORT_FILE_NAME exports/frit_export.h)

target_include_directories(frit PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/exports>
        $<INSTALL_INTERFACE:include/frit>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/FritConfigVersion.cmake
        VERSION 0.0.1
        COMPATIBILITY AnyNewerVersion)

install(TARGETS frit
        EXPORT FritTargets
        LIBRARY DESTINATION lib COMPONENT Runtime
        ARCHIVE DESTINATION lib COMPONENT Development
        RUNTIME DESTINATION bin COMPONENT Runtime
        PUBLIC_HEADER DESTINATION include/frit COMPONENT Development
        BUNDLE DESTINATION bin COMPONENT Runtime)

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FritConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/FritConfig.cmake
        INSTALL_DESTINATION lib/cmake/Frit)

install(EXPORT FritTargets DESTINATION lib/cmake/Frit)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/FritConfigVersion.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/FritConfig.cmake
        DESTINATION lib/cmake/Frit)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/exports/frit_export.h DESTINATION include/frit)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/public/ DESTINATION include/frit)
