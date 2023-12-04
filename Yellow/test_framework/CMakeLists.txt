cmake_minimum_required(VERSION 3.26) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(test_runner LANGUAGES CXX)				# Название проекта

set(SOURCE_LIB test_runner.cpp)		# Установка переменной со списком исходников

add_library(test_runner STATIC ${SOURCE_LIB})# Создание статической библиотеки
add_compile_options(-g)

