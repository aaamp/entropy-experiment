cmake_minimum_required(VERSION 3.10)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(entropy-experiment)

if(MSVC)
    add_compile_options(/W3 /O2 /MT)
endif()

set(BUILD_SHARED_LIBS FALSE)

# idk what this line was for, removing as it compiled without it
# set(SFML_USE_STATIC_STD_LIBS TRUE)

add_subdirectory(thirdparty/SFML)
add_subdirectory(src)
