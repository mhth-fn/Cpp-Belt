cmake_minimum_required(VERSION 3.8)

project(personal_budget)

add_executable(main main.cpp)
set(SOURCE_LIB date.cpp budget.cpp tests.cpp ../../test_framework/test_runner.cpp)
add_library(Library STATIC ${SOURCE_LIB})

add_compile_options(-g)
target_link_libraries(main Library)
