# SPDX-FileCopyrightText: 2020-2025 David Rabkin
# SPDX-License-Identifier: 0BSD
.PHONY: all clean test
cmake_minimum_required(VERSION 3.10)

project(atm CXX)

include(cmake/CompilerWarnings.cmake)

add_library(projectDefs INTERFACE)
set_project_warnings(projectDefs)
target_include_directories(projectDefs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(projectDefs INTERFACE cxx_std_17)

add_subdirectory(src)
