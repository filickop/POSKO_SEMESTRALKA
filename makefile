LDFLAGS = -pthread
LIBS = -lncurses

all: SEMESTRALKA_POSKO

SEMESTRALKA_POSKO: main.c
        gcc $^ -o $@  $(LDFLAGS) $(LIBS)

clean:
        rm -f SEMESTRALKA_POSKO
