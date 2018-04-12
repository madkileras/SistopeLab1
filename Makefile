TARGET=imagecontrol

CXX=g++
CXXFLAGS=-std=c++11 -g -ggdb -Wall -O3
OBJS=obj/imagecontrol.o obj/main.o

all:
	 make $(TARGET)

$(TARGET):$(OBJS)
		    $(CXX) $^ -o $@ $(CXXFLAGS)

obj/imagecontrol.o:imageControl.cpp imageControl.hpp 
				$(CXX) $< -c -o $@ $(CXXFLAGS)
obj/main.o:main.cpp
				$(CXX) $< -c -o $@ $(CXXFLAGS)
				
clean:
	${RM} $(OBJS) $(TARGET) 