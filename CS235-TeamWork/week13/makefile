###############################################################
# Program:
#     Week 13, Graph
#     Brother JonesL, CS235

# Author:
#      Makram Ibrahim, Jefferson Santos, Andrew Larsen
#
# Time: About 16 hours combined. 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week13.o graph.o maze.o
	g++ -o a.out week13.o graph.o maze.o -g
	tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week13.o     : the driver program
##############################################################
week13.o: graph.h vertex.h week13.cpp
	g++ -std=c++11 -c week13.cpp -g

graph.o: graph.h set.h vertex.h graph.cpp
	g++ -std=c++11 -c graph.cpp -g

maze.o: maze.cpp maze.h vertex.h graph.h
	g++ -std=c++11 -c maze.cpp -g
