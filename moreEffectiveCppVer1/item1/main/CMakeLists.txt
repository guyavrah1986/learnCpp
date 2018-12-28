# Properties->C/C++->General->Additional Include Directories
include_directories ("${PROJECT_SOURCE_DIR}/lib1")
 
# Set Properties->General->Configuration Type to Application(.exe)
# Creates item1Exe.exe with the listed sources (main.cpp)
# Adds sources to the Solution Explorer
add_executable(item1Exe main.cpp)
 
# Properties->Linker->Input->Additional Dependencies
target_link_libraries(item1Exe lib1)
 
# Creates a folder "executables" and adds target 
# project (item1Exe.vcproj) under it
set_property(TARGET item1Exe PROPERTY FOLDER "executables")
 
# Properties->General->Output Directory
set_target_properties(item1Exe PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
 
# Adds logic to INSTALL.vcproj to copy app.exe to destination directory
install (TARGETS item1Exe
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)