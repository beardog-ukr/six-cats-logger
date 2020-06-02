cmake_minimum_required(VERSION 3.14)

add_executable(demo_app_basic)
target_sources(demo_app_basic PRIVATE src/BigSmoke.h)
target_sources(demo_app_basic PRIVATE src/BigSmoke.cpp)
target_sources(demo_app_basic PRIVATE src/main.cpp)

target_link_libraries(demo_app_basic PRIVATE command_line_options_processor)
target_link_libraries(demo_app_basic PRIVATE c6_lib)
target_link_libraries(demo_app_basic PRIVATE c6_basic_macro_demo)

target_compile_features(demo_app_basic PRIVATE cxx_final)

