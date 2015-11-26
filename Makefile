GCC=g++
OPTIONS= -g -std=gnu++0x
CFLAGS=
INC_DIR=include/
LIB_DIR=lib/
MAINFILE=main
LIBS=-lFireDoorEscaper -lboost_random

all: $(MAINFILE)

$(MAINFILE): $(MAINFILE).cpp
	$(GCC) $(OPTIONS) $(CFLAGS) $(MAINFILE).cpp -o $(MAINFILE) -I$(INC_DIR) -L$(LIB_DIR) $(LIBS)
