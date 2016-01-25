GCC=g++
CFLAGS=
OPTIONS= -g -std=gnu++0x
INC_DIR=include/
LIB_DIR=lib/
MAINFILE=main
SRCDIR=src/
LIBS=-lFireDoorEscaper -lboost_random

all: $(MAINFILE) 

$(MAINFILE): $(MAINFILE).cpp
	$(GCC) $(OPTIONS) $(CFLAGS) src/trainningSet.cpp src/logRegression.cpp $(MAINFILE).cpp -o $(MAINFILE) -I$(INC_DIR) -L$(LIB_DIR) $(LIBS)

clean:
	rm -f $(OBJ) main