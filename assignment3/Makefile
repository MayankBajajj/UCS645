CXX = g++
CXXFLAGS = -O3 -fopenmp

all: program

program: main.o correlate.o
	$(CXX) $(CXXFLAGS) -o program main.o correlate.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

correlate.o: correlate.cpp
	$(CXX) $(CXXFLAGS) -c correlate.cpp

clean:
	rm -f *.o program