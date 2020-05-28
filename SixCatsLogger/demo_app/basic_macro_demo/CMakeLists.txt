
cmake_minimum_required(VERSION 3.14)

add_library(c6_basic_macro_demo STATIC)
target_sources(c6_basic_macro_demo PUBLIC  include/BasicC6MacroDemo.h)
target_sources(c6_basic_macro_demo PRIVATE src/BasicC6MacroDemo.cpp)

target_link_libraries(c6_basic_macro_demo PUBLIC c6_lib)

target_include_directories(c6_basic_macro_demo PUBLIC include)

target_compile_features(c6_basic_macro_demo PRIVATE cxx_final)
