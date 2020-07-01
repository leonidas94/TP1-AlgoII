CXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)

all: image_transformer
	
image_transformer: main_tp1.cpp shunting_yard.cpp complejo.cpp parser.cpp image.cpp is_functions.cpp pgm_reader.cpp main_tp1.h shunting_yard.h complejo.h parser.h image.h is_functions.h pgm_reader.h stack.h 
	$(CXX) $(CXXFLAGS) -o ../image_transformer main_tp1.cpp shunting_yard.cpp complejo.cpp parser.cpp image.cpp is_functions.cpp pgm_reader.cpp

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err