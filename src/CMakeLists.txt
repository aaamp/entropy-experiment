set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(entropy_experiment main.cpp)

#find_package(OpenMP REQUIRED)

target_include_directories(entropy_experiment PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(entropy_experiment sfml-graphics sfml-window sfml-audio sfml-network sfml-system)# OpenMP::OpenMP_CXX)
target_compile_definitions(entropy_experiment PRIVATE SFML_STATIC)
#set_target_properties(test PROPERTIES LINK_FLAGS_RELEASE /SUBSYSTEM:WINDOWS)
