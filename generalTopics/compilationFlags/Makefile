
#For simplicity gather the files to be compiled "hard-coded" here
#src_files := file1.cpp file2.cpp
CC_FLAGS="-D ECI_TP_ADD"

#library1
lib1.a: file1.cpp
	echo "building lib1"
	g++ -o file1.o -c file1.cpp
	ar -crs lib1.a file1.o

main: main.cpp lib1.a
	echo "building main"
	g++ main.cpp lib1.a -o main

all:
	make CC_FLAGS="-D ECI_TP_ADD" lib1.a
	make CC_FLAGS="-D ECI_TP_ADD" $(CC_FLAGS) main

#Compose the make command
#MAKE=make $(DEP_MAKE_ARGS) 

