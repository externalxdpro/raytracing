linkTarget = bin/ray

LIBS = -lSDL2

CFLAGS = -std=c++20

objects = main.o \
		  App.o \
		  $(patsubst %.cpp,%.o,$(wildcard ./src/*.cpp))

rebuildables = $(objects) $(linkTarget)

# Build
$(linkTarget): $(objects)
	mkdir bin
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)

# Create object files
%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

.PHONEY:
clean:
	rm $(rebuildables)
	rmdir bin
