cmake_minimum_required(VERSION 3.8) # Проверка версии CMake. Если версия установленой программы старее указаной, произайдёт аварийный выход.

project (main)
set(SOURCE_LIB parse.cpp search_server.cpp) 
add_library(lib STATIC ${SOURCE_LIB})
add_executable(main main.cpp)		# Создает исполняемый файл с именем main # из исходника main.cpp
add_compile_options(-g -O3 -pthread -Wall -Wextra -Wpedantic)
target_link_libraries(main lib)
