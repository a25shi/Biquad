CXX=g++
CXXFLAGS=-std=c++14
OBJECTS=test.o board.o decorator.o basecell.o cell.o block.o blockL.o blockO.o blockI.o blockS.o blockZ.o blockT.o blockJ.o
EXEC=test

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -g -o ${EXEC}

test.o: test.cc
board.o: board.cc board.h
basecell.o: basecell.cc basecell.h
decorator.o: decorator.cc decorator.h
cell.o: cell.cc cell.h
block.o: block.cc block.h
blockL.o: blockL.cc blockL.h
blockO.o: blockO.cc blockO.h
blockI.o: blockI.cc blockI.h
blockS.o: blockS.cc blockS.h
blockZ.o: blockZ.cc blockZ.h
blockT.o: blockT.cc blockT.h
blockJ.o: blockJ.cc blockJ.h
