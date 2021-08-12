CXX=g++
CXXFLAGS=-std=c++14
OBJECTS=test.o board.o block.o generation.o level0.o level1.o level2.o level3.o level4.o RAIILevel.o controller.o
EXEC=test

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -g -o ${EXEC}

test.o: test.cc
board.o: board.cc board.h
block.o: block.cc block.h
generation.o: generation.cc generation.h
level0.o: level0.cc level0.h
level1.o: level1.cc level1.h
level2.o: level2.cc level2.h
level3.o: level3.cc level3.h
level4.o: level4.cc level4.h
RAIILevel.o: RAIILevel.cc RAIILevel.h
controller.o: controller.cc controller.h
window.o: window.cc window.h
tetris_graphics.o: tetris_graphics.cc tetris_graphics.h