CXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)

all: prueba1
	
prueba1: main_tp1.cpp parser.cpp shunting_yard.cpp main_tp1.h parser.h shunting_yard.h
	$(CXX) $(CXXFLAGS) -o prueba1 shunting_yard.cpp parser.cpp main_tp1.cpp

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err