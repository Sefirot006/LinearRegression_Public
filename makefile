.PHONY= clean

CC=g++
OPTIONS= -g -std=gnu++0x
DEBUG= #-D DEBUG
LIBDIR=lib/
SRCDIR=src/
INCLUDEDIR=include/
_OBJ= linearRegression.o trainningSet.o perceptron.o logRegression.o neuralNetwork.o
OBJ = $(patsubst %,$(LIBDIR)%,$(_OBJ))
LIBS =

all: main

main:    main.cpp $(OBJ)
	$(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) main.cpp $(OBJ) -o main # -L$(LIBDIR) $(LIBS)

$(LIBDIR)%.o : $(SRCDIR)%.cpp $(INCLUDEDIR)%.h
	$(CC) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<

clean:
	rm -f $(OBJ) main
