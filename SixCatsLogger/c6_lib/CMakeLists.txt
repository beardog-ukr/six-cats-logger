
cmake_minimum_required(VERSION 3.14)

add_library(c6_lib STATIC)
target_sources(c6_lib PUBLIC  include/SixCatsLogger.h)
target_sources(c6_lib PRIVATE src/SixCatsLogger.cpp)

target_include_directories(c6_lib PUBLIC include)


target_compile_features(c6_lib PRIVATE cxx_final)
# target_compile_features(c6_lib PRIVATE cxx_range_for)