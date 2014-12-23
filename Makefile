all: driver.o tiler.o
	g++ -o build/test build/driver.o build/tiler.o -lSDL2

driver.o: test/driver.cpp
	g++ -o build/driver.o test/driver.cpp -c

tiler.o: src/tiler.o
	g++ -o build/tiler.o src/tiler.cpp -c

clean:
	rm build/*
