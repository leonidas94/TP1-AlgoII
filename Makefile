CXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)

all: prueba1
	
prueba1: main_tp1.cpp shunting_yard.cpp complejo.cpp parser.cpp image.cpp is_functions.cpp main_tp1.h shunting_yard.h complejo.h parser.h image.h is_functions.h stk.h 
	$(CXX) $(CXXFLAGS) -o prueba1 main_tp1.cpp shunting_yard.cpp complejo.cpp parser.cpp image.cpp is_functions.cpp

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err