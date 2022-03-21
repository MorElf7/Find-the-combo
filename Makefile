_DEP = items.h room.h
_OBJ = items.o room.o
_MOBJ = adventure.o

CFLAGS = -I$(IDIR)
SDIR = src
ODIR = obj
IDIR = include
SRC = $(wildcard $(SDIR)/*.c)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
MOBJ = $(patsubst %,$(ODIR)/%,$(_MOBJ))
DEPS = $(patsubst %,$(IDIR)/%,$(_DEP))

app: adventure

adventure: $(MOBJ) $(OBJ)
	gcc -g -o $@ $^

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS) $(ODIR)
	gcc -g -c -o $@ $< $(CFLAGS)

$(ODIR): 
	mkdir $@

clean:
	rm -r obj
	rm -f adventure
