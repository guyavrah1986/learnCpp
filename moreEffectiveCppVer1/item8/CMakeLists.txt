cmake_minimum_required (VERSION 3.10)

# Maps to Visual Studio solution file (item8.sln)
# The solution will have all targets (exe, lib, dll) 
# as Visual Studio projects (.vcproj)
project(item8)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Properties->C/C++->General->Additional Include Directories
include_directories(.)
 
# Set Properties->General->Configuration Type to Application(.exe)
# Creates item1Exe.exe with the listed sources (item8.cpp)
# Adds sources to the Solution Explorer
add_executable(item8Exe item8.cpp)
 
# Properties->Linker->Input->Additional Dependencies
# target_link_libraries(item8Exe)
 
# Creates a folder "executables" and adds target 
# project (item8Exe.vcproj) under it
set_property(TARGET item8Exe PROPERTY FOLDER "executables")
 
# Properties->General->Output Directory
set_target_properties(item8Exe PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
 
# Solution Properties->Startup Project->Single Startup project 
# Set this executable to be the startup project of the item8 solution (availble from cmake 3.6)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT item8Exe)
 
# Adds logic to INSTALL.vcproj to copy app.exe to destination directory
install (TARGETS item8Exe
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)