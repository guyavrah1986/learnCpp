cmake_minimum_required (VERSION 3.10)

# Maps to Visual Studio solution file (item3.sln)
# The solution will have all targets (exe, lib, dll) 
# as Visual Studio projects (.vcproj)
project(item3)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Properties->C/C++->General->Additional Include Directories
include_directories ("${PROJECT_SOURCE_DIR}/lib1")
 
# Set Properties->General->Configuration Type to Application(.exe)
# Creates item1Exe.exe with the listed sources (main.cpp)
# Adds sources to the Solution Explorer
add_executable(item3Exe item3.cpp)
 
# Properties->Linker->Input->Additional Dependencies
# target_link_libraries(item3Exe)
 
# Creates a folder "executables" and adds target 
# project (item3Exe.vcproj) under it
set_property(TARGET item3Exe PROPERTY FOLDER "executables")
 
# Properties->General->Output Directory
set_target_properties(item3Exe PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
 
# Adds logic to INSTALL.vcproj to copy app.exe to destination directory
install (TARGETS item3Exe
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)