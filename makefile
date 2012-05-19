CFLAGS = -g #-std=c++0x 
TARGETS = neighbor
BASICS = STLExtends.hpp Vector.h Vector.cpp

output : $(TARGETS)

clean :
	-rm *.o
	-rm $(TARGETS)

neighbor : neighbor.cpp $(BASICS)
	g++ $(CFLAGS) -o $@ $^



