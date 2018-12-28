:: Disable the need to prefix echo using the @ symbol (i.e.- no need to write @echo "something to echo", simply wirte: echo "something to echo")
@echo off

:: get the name of the item to build (for instance - item8) as the first argument for this script
set projectName=%1
echo "building project %projectName%"

set currDir=%cd%
echo "current directory is:%currDir%"

:: navigate to the respective "project" (specific item folder)
cd %projectName%

set cmakeFileFullPath=%cd%
echo "The full path to the cmake file we are about to invoke is:%cmakeFileFullPath%"

:: remove old build folder and all its content
rmdir /Q /S build

:: create a new one
mkdir build

:: navigate to the build fodler so that the build output will go there
cd build

:: invoke the cmake command to create the desired Visual Studio solutions  
echo "Invoking cmake on the desired CMakeLists file"
cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 %cmakeFileFullPath%

:: stop the batch and ask for us to enter any key before terminating, this (built in) command
:: will prompt the user to:
:: "Press any key to continue. . . "
pause

:: navigate back out of the build folder
cd ..

:: enable back the @in echo
echo on