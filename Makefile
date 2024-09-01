CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: cipher

cipher: cipher.o
	$(CXX) $(CXXFLAGS) -o cipher cipher.o

cipher.o: cipher.cc cipher.h
	$(CXX) $(CXXFLAGS) -c cipher.cc

clean:
	rm -f cipher cipher.o
