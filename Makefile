# Makefile
# Author : udit01

all: board.cpp utils.cpp game.cpp player.cpp timing.cpp
	g++ -std=c++11 -pthread -o player  board.cpp utils.cpp game.cpp player.cpp timing.cpp

debug: board.cpp utils.cpp game.cpp player.cpp timing.cpp
	g++ -g -std=c++11 -pthread -o player  board.cpp utils.cpp game.cpp player.cpp timing.cpp

opt: board.cpp utils.cpp game.cpp player.cpp timing.cpp
	g++ -std=c++11 -pthread -O3 -o player  board.cpp utils.cpp game.cpp player.cpp timing.cpp

clean:
	find . -name '*.pyc' -delete
	find . -name '*.out' -delete

#  Flags if needed -O3 -std=c++11
	
# all: board.cpp utils.cpp game.cpp player.cpp PossibleMove.cpp
# 	g++ -std=c++11 -o player  board.cpp utils.cpp game.cpp player.cpp PossibleMove.cpp

# opt: board.cpp utils.cpp game.cpp player.cpp 
# 	g++ -std=c++11 -O3 -o player  board.cpp utils.cpp game.cpp player.cpp PossibleMove.cpp

# clean:
# 	find . -name '*.pyc' -delete
# 	find . -name '*.out' -delete
