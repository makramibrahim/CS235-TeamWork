###############################################################
# Program:
#     Week 07, LIST
#     Brother XXXXX, CS235
# Author:
#     <Makram Ibrahim>
# Summary:
#     <put a description here>
# Time:
#     <how long did it take to complete this program>?
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h week07.o fibonacci.o
	g++ -o a.out week07.o fibonacci.o
	tar -cf week07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week07.o       : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
week07.o: list.h week07.cpp
	g++ -c week07.cpp

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	g++ -c fibonacci.cpp

