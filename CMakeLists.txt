cmake_minimum_required(VERSION 3.2)

include(../simplicity/simplicity-common.cmake)

# Project Dependencies
#########################
project(simplicity-cef)

# Project
#########################

add_subdirectory(lib/cef_linux64)

set(CEF_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/cef_linux64/Release)
set(CEF_RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/cef_linux64/Resources)
add_library(cef SHARED IMPORTED)
set_property(TARGET cef PROPERTY IMPORTED_LOCATION ${CEF_BIN_DIR}/libcef.so)

# Source
#########################
file(GLOB_RECURSE SRC_FILES src/main/c++/simplicity/cef/main/*.cpp src/main/c++/simplicity/cef/main/*.h)
file(GLOB_RECURSE SRC_FILES_SUBPROCESS src/main/c++/simplicity/cef/subprocess/*.cpp src/main/c++/cef/simplicity/subprocess/*.h)

# Main Target
#########################
add_library(simplicity-cef STATIC ${SRC_FILES})
target_include_directories(simplicity-cef PUBLIC src/main/c++)

# Main Target Dependencies
#########################

add_dependencies(simplicity-cef simplicity-cef-subprocess)

# CEF
target_include_directories(simplicity-cef PUBLIC lib/cef_linux64)
target_include_directories(simplicity-cef PUBLIC lib/cef_linux64/include)
target_link_libraries(simplicity-cef libcef_dll_wrapper)
target_link_libraries(simplicity-cef cef)

# Simplicity
target_link_libraries(simplicity-cef simplicity)

# X
target_link_libraries(simplicity-cef X11)

# Main Target Resources
#########################
add_custom_command(TARGET simplicity-cef POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy ${CEF_BIN_DIR}/chrome-sandbox ${CMAKE_BINARY_DIR}
				   COMMAND ${CMAKE_COMMAND} -E copy ${CEF_BIN_DIR}/libcef.so ${CMAKE_BINARY_DIR}/lib
				   COMMAND ${CMAKE_COMMAND} -E copy ${CEF_BIN_DIR}/libffmpegsumo.so ${CMAKE_BINARY_DIR}/lib
				   COMMAND ${CMAKE_COMMAND} -E copy ${CEF_BIN_DIR}/libpdf.so ${CMAKE_BINARY_DIR}/lib
				   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/assets/cef
				   COMMAND ${CMAKE_COMMAND} -E copy ${CEF_RES_DIR}/cef.pak ${CMAKE_BINARY_DIR}/assets/cef
				   COMMAND ${CMAKE_COMMAND} -E copy ${CEF_RES_DIR}/cef_100_percent.pak ${CMAKE_BINARY_DIR}/assets/cef
				   COMMAND ${CMAKE_COMMAND} -E copy ${CEF_RES_DIR}/cef_200_percent.pak ${CMAKE_BINARY_DIR}/assets/cef
				   COMMAND ${CMAKE_COMMAND} -E copy ${CEF_RES_DIR}/devtools_resources.pak ${CMAKE_BINARY_DIR}/assets/cef
				   COMMAND ${CMAKE_COMMAND} -E copy ${CEF_RES_DIR}/icudtl.dat ${CMAKE_BINARY_DIR}
				   COMMAND ${CMAKE_COMMAND} -E copy ${CEF_RES_DIR}/icudtl.dat ${CMAKE_BINARY_DIR}/lib
				   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CEF_RES_DIR}/locales ${CMAKE_BINARY_DIR}/assets/cef/locales
				   COMMAND chmod 4755 ${CMAKE_BINARY_DIR}/chrome-sandbox
				   COMMENT "simplicity::cef || Copying CEF files\nsimplicity::cef || chrome-sandbox needs to have specific permissions and be owned by root, run the following commands:\nsimplicity::cef || sudo chmod 4755 ${CMAKE_BINARY_DIR}/chrome-sandbox\nsimplicity::cef || sudo chown root:root ${CMAKE_BINARY_DIR}/chrome-sandbox")

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
