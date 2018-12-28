# =====================================================================================================================================
# general project settings
# =====================================================================================================================================

cmake_minimum_required(VERSION 3.5)

project("moreEffectiveCppVer1")

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

# enable c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ======================================================================================================================================
# disable specific warnings
# ======================================================================================================================================

set(CPP_STUFF_WARNINGS "-Werror -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wold-style-cast -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option")

# TODO: was removed for item9: -Wnoexcept -Woverloaded-virtual

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS ${CPP_STUFF_WARNINGS}) # use this setting in order to disable a certain warning: -Wno-pmf-conversions
endif()

# ======================================================================================================================================
# include directories
# ======================================================================================================================================

# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================

# item1
file(GLOB_RECURSE ITEM1_SRC
    "${CMAKE_CURRENT_LIST_DIR}/item1.cpp")

# item3
file(GLOB_RECURSE ITEM3_SRC
    "${CMAKE_CURRENT_LIST_DIR}/item3.cpp")

# item4
file(GLOB_RECURSE ITEM4_SRC
    "${CMAKE_CURRENT_LIST_DIR}/item4.cpp")

# item8
file(GLOB_RECURSE ITEM8_SRC
    "${CMAKE_CURRENT_LIST_DIR}/item8.cpp")
	
# item9
file(GLOB_RECURSE ITEM9_SRC
    "${CMAKE_CURRENT_LIST_DIR}/item9.cpp")

# item19
file(GLOB_RECURSE ITEM19_SRC
    "${CMAKE_CURRENT_LIST_DIR}/item19.cpp")

# item21
file(GLOB_RECURSE ITEM21_SRC
    "${CMAKE_CURRENT_LIST_DIR}/item21.cpp")

# ======================================================================================================================================
# add relevant sub directories -- invoke their CMakeLists.txt files
# ======================================================================================================================================

# common library
# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/common ${CMAKE_CURRENT_LIST_DIR}/build/common)

# ======================================================================================================================================
# create the main executable (and samples as well)
# ======================================================================================================================================
   
add_executable(item1Exe ${ITEM1_SRC})

add_executable(item3Exe ${ITEM3_SRC})

add_executable(item4Exe ${ITEM4_SRC})

add_executable(item8Exe ${ITEM8_SRC})

add_executable(item9Exe ${ITEM9_SRC})

add_executable(item19Exe ${ITEM19_SRC})

add_executable(item21Exe ${ITEM21_SRC})

# ======================================================================================================================================
# link the executable(s) with all relevant libraries
# ======================================================================================================================================
                 

