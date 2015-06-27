cmake_minimum_required(VERSION 3.2)

include(../simplicity/simplicity-common.cmake)

# Project
#########################
project(simplicity-cef)

add_subdirectory(lib/cef_linux64)
find_library(CEF_PATH cef ${CMAKE_CURRENT_SOURCE_DIR}/lib/cef_linux64/Release)

# Source
#########################
file(GLOB_RECURSE SRC_FILES src/main/c++/simplicity/cef/main/*.cpp src/main/c++/simplicity/cef/main/*.h src/main/c++/simplicity/cef/common/*.cpp src/main/c++/simplicity/cef/common/*.h)
file(GLOB_RECURSE SRC_FILES_SUBPROCESS src/main/c++/simplicity/cef/subprocess/*.cpp src/main/c++/cef/simplicity/subprocess/*.h src/main/c++/simplicity/cef/common/*.cpp src/main/c++/simplicity/cef/common/*.h)

# Main Target
#########################
add_library(simplicity-cef STATIC ${SRC_FILES})
target_include_directories(simplicity-cef PUBLIC src/main/c++)

# Main Target Dependencies
#########################

# CEF
target_include_directories(simplicity-cef PUBLIC lib/cef_linux64)
target_include_directories(simplicity-cef PUBLIC lib/cef_linux64/include)
target_link_libraries(simplicity-cef libcef_dll_wrapper)
target_link_libraries(simplicity-cef ${CEF_PATH})

# Simplicity
target_link_libraries(simplicity-cef simplicity)

# X
target_link_libraries(simplicity-cef X11)

# Subprocess Target
#########################
add_executable(simplicity-cef-subprocess ${SRC_FILES_SUBPROCESS})

# Subprocess Target Dependencies
#########################

# CEF
target_include_directories(simplicity-cef-subprocess PUBLIC lib/cef_linux64)
target_include_directories(simplicity-cef-subprocess PUBLIC lib/cef_linux64/include)
target_link_libraries(simplicity-cef-subprocess libcef_dll_wrapper)
target_link_libraries(simplicity-cef-subprocess ${CEF_PATH})

# Simplicity
target_link_libraries(simplicity-cef-subprocess simplicity)

# X
target_link_libraries(simplicity-cef-subprocess X11)

