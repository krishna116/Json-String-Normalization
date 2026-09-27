cmake_minimum_required(VERSION 4.0)

project(JsonSringNormalizationLib VERSION 1.0.0 LANGUAGES C CXX)

if(MSVC)
  add_compile_options(/utf-8)
endif()

add_library(JsonSringNormalizationLib INTERFACE)

target_include_directories(JsonSringNormalizationLib INTERFACE
src
)

add_subdirectory(tests)