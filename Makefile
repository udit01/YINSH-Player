# Makefile
# Author : udit01

all: board.cpp utils.cpp game.cpp player.cpp 
	g++ -o player  board.cpp utils.cpp game.cpp player.cpp 

opt: board.cpp utils.cpp game.cpp player.cpp 
	g++ -O3 -o player  board.cpp utils.cpp game.cpp player.cpp

clean:
	find . -name '*.pyc' -delete
	find . -name '*.out' -delete

#  Flags if needed -O3 -std=c++11
	