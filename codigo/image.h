#ifndef _IMAGE_H_INCLUIDO_
#define _IMAGE_H_INCLUIDO_

#include <iostream>
#include "complejo.h"

using namespace std;

class image{
  private:
    int width; // Ancho y alto
    int height;
    int greyscale;
    int **matrix;

	public:

  // Contructores
	image(); // Por defecto
	image(const int, const int, const int);  // Constructor por argumento
	~image();  // Destructor
	
	// Setters y getters
  void set_width(const int);
 	int get_width();
  void set_height(const int);
  int get_height();
  void set_greyscale(const int );
  int get_greyscale();
  int get_max_dim();
  void set_matrix_value(const int &,const int &,const int &);
  int get_matrix_value(const int &,const int &);

  // Printers
  void print_matrix();
  void print_image(ostream*);

  void fill_matrix(int **);
};

#endif