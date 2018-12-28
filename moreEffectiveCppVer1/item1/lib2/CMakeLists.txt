# Collect sources into the variable MATH_SOURCES without
# having to explicitly list each header and source file.
#
# CMake documentation states "We do not recommend using GLOB to collect a
# list of source files from your source tree. If no CMakeLists.txt file
# changes when a source is added or removed then the generated build system
# cannot know when to ask CMake to regenerate".
# Collect sources into the variable SIMPLE_FUNCTION_SOURCES
file (GLOB LIB2_SOURCES
      "*.h"
      "*.cpp")
 
# The recommended way to collect sources in variable 
# LIB2_SOURCES by explicitly specifying the source files
#set(LIB2_SOURCES
#      "classB.h"
#      "classB.cpp")
 
# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
# source_group("" FILES ${GENERAL_SOURCES})
source_group("lib2" FILES ${LIB2_SOURCES})
 
# Properties->C/C++->General->Additional Include Directories
include_directories (.)
 
# Set Properties->General->Configuration Type to Static (.lib)
# Creates lib2.lib with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
add_library(lib2 STATIC ${LIB2_SOURCES})
 
# Creates folder "libraries" and adds target project (lib1.vcproj)
set_property(TARGET lib2 PROPERTY FOLDER "libs")
 
# Properties->General->Output Directory
set_target_properties(lib2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
 
# Adds logic to INSTALL.vcproj to copy lib1.dll to the destination directory
install (TARGETS lib2
		 ARCHIVE DESTINATION lib2
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install
         LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/_install)