cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(entropy-experiment)

if(MSVC)
    add_compile_options(/W3 /MT)
else()
    add_compile_options(-O3) 
endif()

set(BUILD_SHARED_LIBS FALSE)

set(SFML_USE_STATIC_STD_LIBS TRUE)
set(SFML_BUILD_NETWORK FALSE)
set(SFML_BUILD_AUDIO FALSE)

add_subdirectory(thirdparty/SFML)
add_subdirectory(src)

