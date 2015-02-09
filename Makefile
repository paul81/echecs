CC = gcc
CFLAGS = -g -Wall -pedantic -Wmissing-prototypes -isystem ./lib/fann -L ./bin -lcef -Wl,-rpath,./bin -isystem ./lib `pkg-config --cflags --libs gtk+-2.0` -l:lib/libfann.a -lm
EXEC=install echecs
SRC = $(wildcard src/*.c) $(wildcard src/cef/*.c)
HEAD = $(wildcard src/*.h)
OBJ = $(SRC:src/.c=src/.o)
DIR = bin

all: $(EXEC)

%.o: %.c 
	$(CC) -o $@ $^

echecs: $(OBJ)
	gcc -o $(DIR)/$@ $^ $(CFLAGS)

.PHONY: clean distclean

clean: 
	@rm -rf src/*.o src/*.uncrustify

distclean: clean
	@rm -rf $(EXEC)

format: $(SRC)
	uncrustify -c uncrustify.cfg $(SRC) $(HEAD) 

doc: 
	doxygen Doxyfile

install:
	mkdir -p $(DIR)
	

