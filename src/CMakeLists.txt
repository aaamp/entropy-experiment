set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Release)
add_executable(entropy_experiment main.cpp symul.cpp)

target_include_directories(entropy_experiment PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(entropy_experiment sfml-graphics sfml-window sfml-system)
# sfml-audio sfml-network są raczej niepotrzebne
target_compile_definitions(entropy_experiment PRIVATE SFML_STATIC)

if(MSVC)
    # Gdybyśmy nie chcieli okienka konsoli pod windowsem:
    # target_link_libraries(entropy_experiment sfml-main)
    # set_target_properties(entropy_experiment PROPERTIES LINK_FLAGS_RELEASE /SUBSYSTEM:WINDOWS)
endif()

# Gdybyśmy chcieli wielowątkowość z OpenMP, ponoć fajne:
# find_package(OpenMP REQUIRED)
# target_link_libraries(entropy_experiment OpenMP::OpenMP_CXX)
