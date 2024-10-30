CC = gcc
CXX = g++
CXXFLAGS = -Wall -g

INCLUDES = stb_image.h

img2ascii: %: %.o stb_image.o
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $@

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f img2ascii *.o 
