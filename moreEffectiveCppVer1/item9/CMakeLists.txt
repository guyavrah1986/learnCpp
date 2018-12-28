cmake_minimum_required (VERSION 3.10)

# Maps to Visual Studio solution file (item9.sln)
# The solution will have all targets (exe, lib, dll) 
# as Visual Studio projects (.vcproj)
project(item9)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Properties->C/C++->General->Additional Include Directories
include_directories(.)
 
# Set Properties->General->Configuration Type to Application(.exe)
# Creates item1Exe.exe with the listed sources (item9.cpp)
# Adds sources to the Solution Explorer
add_executable(item9Exe item9.cpp)
 
# Properties->Linker->Input->Additional Dependencies
# target_link_libraries(item9Exe)
 
# Creates a folder "executables" and adds target 
# project (item9Exe.vcproj) under it
set_property(TARGET item9Exe PROPERTY FOLDER "executables")
 
# Properties->General->Output Directory
set_target_properties(item9Exe PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
 
# Solution Properties->Startup Project->Single Startup project 
# Set this executable to be the startup project of the item9 solution (availble from cmake 3.6)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT item9Exe)
 
# Adds logic to INSTALL.vcproj to copy item9.exe to destination directory
install (TARGETS item9Exe
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)