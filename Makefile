SOURCES = test/driver.cpp src/tiler.cpp 
OBJECTS = $(SOURCES:.cpp=.o)
LIBRARIES = -framework SDL2 -framework SDL2_image -ltmxparser

all: test

test: $(OBJECTS)
	g++ -o test/test $(INCLUDES) $(LIBRARIES) $(OBJECTS)

.cpp.o: $(SOURCES)
	g++ -o $(<:.cpp=.o) -c $<

clean:
	rm build/* ./src/*.o ./test/*.o
	rm test/test
