# =====================================================================================================================================
# general project settings
# =====================================================================================================================================

cmake_minimum_required(VERSION 3.9)

project("stlUsagesExample")

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

# enable c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ======================================================================================================================================
# disable specific warnings
# ======================================================================================================================================

# used to enable (almost) all warnings
set(CPP_STUFF_WARNINGS "-Werror -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS ${CPP_STUFF_WARNINGS}) # use this setting in order to disable a certain warning: -Wno-pmf-conversions
endif()

# ======================================================================================================================================
# include directories
# ======================================================================================================================================
include_directories("${CMAKE_CURRENT_LIST_DIR}/vector"
		    "${CMAKE_CURRENT_LIST_DIR}/map")

# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================

# std::vector
file(GLOB_RECURSE VECTOR_USAGES_SRC
    "${CMAKE_CURRENT_LIST_DIR}/vector/vector.cpp")

# std::map
file(GLOB_RECURSE MAP_USAGES_SRC
    "${CMAKE_CURRENT_LIST_DIR}/map/stdMapUsages.cpp")

# ======================================================================================================================================
# add relevant sub directories -- invoke their CMakeLists.txt files
# ======================================================================================================================================


# ======================================================================================================================================
# create the main executable (and samples as well)
# ======================================================================================================================================
   
add_executable(vectorUsagesExe ${VECTOR_USAGES_SRC})

add_executable(mapUsagesExe ${MAP_USAGES_SRC})

# ======================================================================================================================================
# link the executable(s) with all relevant libraries
# ======================================================================================================================================

