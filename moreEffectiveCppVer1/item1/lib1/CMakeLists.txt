# Collect sources into the variable MATH_SOURCES without
# having to explicitly list each header and source file.
#
# CMake documentation states "We do not recommend using GLOB to collect a
# list of source files from your source tree. If no CMakeLists.txt file
# changes when a source is added or removed then the generated build system
# cannot know when to ask CMake to regenerate".
# Collect sources into the variable SIMPLE_FUNCTION_SOURCES
file (GLOB LIB1_SOURCES
      "*.h"
      "*.cpp")
 
# The recommended (!!) way to collect sources in variable 
# ADVANCED_FUNCTION_SOURCES by explicitly specifying the source files
#set(ADVANCED_FUNCTION_SOURCES
#      "classA.h"
#      "classA.cpp")
 
# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
# source_group("" FILES ${LIB1_SOURCES})
source_group("lib1" FILES ${LIB1_SOURCES})
 
# Properties->C/C++->General->Additional Include Directories
include_directories (.
					 "{CMAKE_CURRENT_LIST_DIR}/../lib2")
 
# Set Properties->General->Configuration Type to Static Library(.lib)
# Creates lib1.lib with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
add_library(lib1 STATIC ${LIB1_SOURCES})
 
# Creates folder "libraries" and adds target project (lib1.vcproj)
set_property(TARGET lib1 PROPERTY FOLDER "libs")
 
# Properties->General->Output Directory
set_target_properties(lib1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
 
# TODO: !!
# Link lib1 against lib2
#target_link_libraries(lib1 lib2)
 
# Adds logic to INSTALL.vcproj to copy lib1.dll to the destination directory
install(TARGETS lib1
		ARCHIVE DESTINATION lib1
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/_install)