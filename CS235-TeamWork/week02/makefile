###############################################################
# Program:
#     Week 02, STACK
#     Brother JonesL, CS235
# Author:
#    Makram Ibrahim 
# Summary:
#     The program will demonstrate functions of a template 
#     class program and its use as part of infix to postfix 
#     equation conversion.
# Time:
#	  This assignment took me so long over 22 horus. 
#     I actually didn't finish the test 5, I tried to get hold of my 
#     group, but there was no response. I did this assignment
#     on my own. I realized I just needed to move on and call 
#     this one a wash. 
#        
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h week02.o infix.o 
	g++ -o a.out week02.o infix.o 
	tar -cf week02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week02.o       : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
week02.o: stack.h infix.h week02.cpp
	g++ -c week02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp

