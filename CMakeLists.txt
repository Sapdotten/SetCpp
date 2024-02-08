# CMakeList.txt : CMake project for SetCpp, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.13)

project (SetCpp VERSION 1.0 LANGUAGES CXX)

if(MSVC)
    # Генерируем статическую заглушку для динамических библиотек
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

    # Включаем высокий уровень предупреждений
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

add_library(Set STATIC "src/include/set.h" "src/include/set.cc")
target_include_directories(Set PUBLIC "include")
# Add source to this project's executable.
add_executable (SetCpp  "src/main.cpp")

target_link_libraries(SetCpp Set)
# Подключаем googletest
#include(FetchContent)
#FetchContent_Declare(googletest URL "https://github.com/google/googletest/archive/refs/heads/main.zip")
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)

# TODO: Add tests and install targets if needed.
