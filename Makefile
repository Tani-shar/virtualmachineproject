flags=-O0 -std=c23
ldflags=

.PHONY: all clean

all: virmac  # Change the output name from birdnest to virmac

virmac: virmac.o
	cc $(flags) $^ -o $@ $(ldflags)  # Compile virmac.o into the virmac executable

virmac.o: virmac.c  # Specify your source file
	cc $(flags) -c $<  # Compile virmac.c into virmac.o

clean:
	rm -f *.o virmac  # Remove all object files and the virmac executable
