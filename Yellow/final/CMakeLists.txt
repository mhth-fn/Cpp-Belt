cmake_minimum_required(VERSION 3.8) # Проверка версии CMake. Если версия установленой программы старее указаной, произайдёт аварийный выход.

project (main)
set(SOURCE_LIB node.cpp condition_parser.cpp condition_parser_test.cpp database.cpp date.cpp token.cpp) 
add_library(hello_world STATIC ${SOURCE_LIB})
add_executable(main main.cpp)		# Создает исполняемый файл с именем main # из исходника main.cpp
add_compile_options(-g)
target_link_libraries(main hello_world)
