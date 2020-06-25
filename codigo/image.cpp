#include<iostream>
#include "image.h"

using namespace std;

// Constructor por defecto
image::image(){
  width=0;      // Ancho
  height=0;     // Alto
  greyscale=0;  // Escala de grises
  matrix=NULL;  // Matriz
}

// Constructor por parametro
image::image(const int w, const int h, const int gs){

  int max = 0;
  width = w;
  height = h;
  greyscale = gs;
  if(w<h){max = h;} else{max = w;}

  this->matrix = new int*[max+1];
  for (int i = 0; i < max; i++){  // Pide memoria para crear la matriz cuadrada
    this->matrix[i] = new int[max+1];
  }

  for (int i = 0; i < max; i++){     
    for (int j = 0; j < max; j++){
      this->matrix[i][j] = 0;     // Rellena la matriz con color negro
    }
  }
}


// Destructor
image::~image(){ 

  int max = this->get_max_dim();

  if (matrix){                
    for (int i = 0; i<max; i++){    
      if (matrix[i]){          
        delete[] matrix[i]; // Libera la memoria pedida para crear la matriz
      }
    }
  }
  delete[] matrix;
}

// Setter y getters

void image::set_width(const int A){  // Setea el ancho
  width = A;
}

int image::get_width(){ // Obtiene el ancho
  return width;
}

void image::set_height(const int A){ // Setea el alto
  height = A;
}

int image::get_height(){  // Obtiene el alto
  return height;
}

void image::set_greyscale(const int A){ // Setea la escala de grises
  greyscale = A;
}

int image::get_greyscale(){ // Setea la escala de grises
  return greyscale;
}

int image::get_max_dim(){ // Obtiene la dimension mayor
  if(width < height) {return height;}
  else{return width;}
}

void image::set_matrix_value(const int & i,const int & j,const int & aux_color){ // Setea un valor específico de la matriz en la posición i,j
  matrix[i][j]=aux_color;
}

int image::get_matrix_value(const int & i,const int & j){ // Obtiene un valor específico de la matriz en la posición i,j
  return matrix[i][j];
}

void image::print_matrix(){ // Imprime la matriz por cout
  int max=0;

  if(width<height){max = height;} else{max = width;}

  for(int x=0 ; x<max ; x++){
    for(int y=0 ; y<max ; y++) {
      cout << this->matrix[x][y] << " ";
    }
    cout << endl;
  }
}

void image::print_image(ostream *os){ // Imprime la imagen por ostrem

  int max=0;
  if(width<height){max = height;} else{max = width;}

  *os << "P2"<<'\n'<<max<<" "<<max<<'\n'<<greyscale<<'\n';
  if (os->bad()) {
    cerr << "cannot write to output stream."
    << endl;
    exit(1);
  }

  for(int x=0;x<max;x++)
  {
    for(int y=0;y<max;y++) {
      *os << this->matrix[x][y];
      *os << " ";
      if (os->bad()) {
        cerr << "cannot write to output stream."
        << endl;
        exit(1);
      }            
    }

    *os<<endl;
    if (os->bad()) {
        cerr << "cannot write to output stream."
        << endl;
        exit(1);
    } 
  }
}

// Este método pide memoria y llena la matriz pasada como argumento.
void image::fill_matrix(int ** matrix){

  int max=0;
  bool IS_VERTICAL = true;
 
  max = get_max_dim();
  if (width>height)
    IS_VERTICAL=false;


  this->matrix = new int*[max]; // Se pide memoria para la matriz cuadrada de lado mayor.
  for (int i=0 ; i<max ; i++){
    this->matrix[i] = new int[max];
  }

  if (width == height){ // Para imagenes cuadradas
    for (int i = 0; i < max; i++){
      for (int j = 0; j < max; j++){
        this->matrix[i][j] = matrix[i][j];
      }
    }
  }
  
  for (int i = 0; i < max; i++){
    for (int j = 0; j < max; j++){
      if (IS_VERTICAL){ // Para imagenes vertical          
        if ( j<((max-width)/2) || j>((max+width)/2)-1 )
          this->matrix[i][j] = 0;
        else{
          this->matrix[i][j] = matrix[i][j-(max-width)/2];
        }
      }
      else{    // Para imagenes horizontal          
        if ( i<((max-height)/2) || i>((max+height)/2)-1 )
          this->matrix[i][j] = 0;
        else
          this->matrix[i][j] = matrix[i-(max-height)/2][j];
      } 
    }
  }
  height = max;
  width = max;
}

// Imprime la imagen en un ostream
ostream & operator << (ostream *os, const image & c){

  int max=0;
  if(c.width<c.height){max = c.height;} else{max = c.width;}

  *os << "P2"<<'\n'<<max<<" "<<max<<'\n'<<c.greyscale<<'\n';
  if (os->bad()) {
    cerr << "cannot write to output stream."
    << endl;
    exit(1);
  }

  for(int x=0;x<max;x++)
  {
    for(int y=0;y<max;y++) {
      *os << c.matrix[x][y];
      *os << " ";
      if (os->bad()) {
        cerr << "cannot write to output stream."
        << endl;
        exit(1);
      }            
    }

    *os<<endl;
    if (os->bad()) {
        cerr << "cannot write to output stream."
        << endl;
        exit(1);
    } 
  }
  return *os;

}
