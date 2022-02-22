cmake_minimum_required(VERSION 3.8)

enable_testing()

add_executable(lexer-test lexer.test.cpp)

target_link_libraries(lexer-test frit)

set_target_properties(lexer-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_test(NAME lexer-test COMMAND $<TARGET_FILE:lexer-test>)
