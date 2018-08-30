
CC = g++
CFLAGS = --std=c++11 -Wall -c
LFLAGS = --std=c++11
SRC = src
OBJ = obj
DOC = doc
OSM = osm
IMG = images

all: maps

maps: $(OBJ)/maps.o $(OBJ)/matrix_rev.o $(OBJ)/node.o $(OBJ)/point2d.o  $(OBJ)/osm_rev.o $(OBJ)/way.o
	$(CC) $(LFLAGS) $(OBJ)/maps.o $(OBJ)/matrix_rev.o $(OBJ)/node.o $(OBJ)/point2d.o $(OBJ)/osm_rev.o $(OBJ)/way.o -o maps

$(OBJ)/maps.o: $(SRC)/maps.cpp $(SRC)/matrix_rev.hpp $(SRC)/node.hpp $(SRC)/point2d.hpp  $(SRC)/osm_rev.hpp $(SRC)/way.hpp
	$(CC) $(CFLAGS) $(SRC)/maps.cpp -o $(OBJ)/maps.o

$(OBJ)/matrix_rev.o: $(SRC)/matrix_rev.cpp $(SRC)/matrix_rev.hpp
	$(CC) $(CFLAGS) $(SRC)/matrix_rev.cpp -o $(OBJ)/matrix_rev.o

$(OBJ)/node.o: $(SRC)/node.cpp $(SRC)/node.hpp
	$(CC) $(CFLAGS) $(SRC)/node.cpp -o $(OBJ)/node.o

$(OBJ)/point2d.o: $(SRC)/point2d.cpp $(SRC)/point2d.hpp
	$(CC) $(CFLAGS) $(SRC)/point2d.cpp -o $(OBJ)/point2d.o

$(OBJ)/osm_rev.o: $(SRC)/osm_rev.cpp $(SRC)/osm_rev.hpp
	$(CC) $(CFLAGS) $(SRC)/osm_rev.cpp -o $(OBJ)/osm_rev.o

$(OBJ)/way.o: $(SRC)/way.cpp $(SRC)/way.hpp
	$(CC) $(CFLAGS) $(SRC)/way.cpp -o $(OBJ)/way.o

.PHONY: all clean doc

doc:
	doxygen doxyfile

clean:
	rm -rf $(DOC)/* $(IMG)/*.pgm $(OBJ)/* maps 


	

