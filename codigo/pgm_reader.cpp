#include "pgm_reader.h"

static string PGM_IDENTIFIER = "P2";
static char SKIP_LINE_IDENTIFIER = '#';

using namespace std;

// Esta funcion lee del archivo de input y llena la imagen VACIA que se le pasa como argumento 
bool read_pgm(istream * iss, image & img_arg){	

  if (!read_identifier(iss)){
    cerr << "No es PGM" <<endl;
    return false;
  }

  if (!read_size(iss, img_arg)){
    cerr << "Error en el formato" <<endl;
    return false;
  }

  read_greyscale(iss, img_arg);

  // Crea la matriz de enteros y los llena con ceros
  // Como la matriz va a ser cuadrada, se pide dos veces de dimension "max"

  if (!read_matrix (iss, img_arg)){
    cerr<<"Error leyendo matriz de imagen"<<endl;
    return false;
  }

  return true;
}


bool read_identifier(istream * iss){
  string in_string;

  getline(*iss, in_string); // Identificador PGM

  if (in_string[0] == PGM_IDENTIFIER[0]){
    if (in_string[1] != PGM_IDENTIFIER[1]){ // En caso que el identificador sea incorrecto
      return false;
    }
  }
  else { return false;}
  return true;
}


bool read_size(istream * iss, image & img_arg){
  int aux_int, i=0, aux_size[2];
  string in_string, temp;

  getline(*iss, in_string);
  if (in_string[0] == SKIP_LINE_IDENTIFIER){ // Se detecta si se leyó un comentario
    getline(*iss, in_string); // Se leen las dimensiones de la matriz
  }

  stringstream ss (in_string); 
  
  while (i < 2 && !ss.eof()){
    ss >> temp;
    if(stringstream(temp) >> aux_int){  // Si se pudo convertir se guarda en el arreglo
      aux_size[i] = aux_int;
      i++;
    }
    temp = "";
  }
  if (i == 1){
    return false;
  }

  ss >> temp;
  if(stringstream(temp) >> aux_int){  // Si se pudo convertir es un error
    return false;
  }

  img_arg.set_width(aux_size[0]);  // Se guarda el ancho de la matriz
  img_arg.set_height(aux_size[1]); // Se guarda el alto de la matriz

  return true;
}


void read_greyscale(istream * iss, image & img_arg){
  string in_string;
  int aux_greyscale;

  getline(*iss, in_string);
  aux_greyscale = stoi(in_string);
  img_arg.set_greyscale(aux_greyscale); // Se guarda el valor de la escala de grises
}


bool read_matrix (istream * iss, image & img_arg){
  int aux_int, aux_size;	// aux_size es para poder borrar la matriz auxiliar luego
  int ** aux_matrix;

	aux_size = img_arg.get_height();

  aux_matrix = new int*[img_arg.get_height()]; 
  for (int i = 0; i < img_arg.get_height(); i++){  
      aux_matrix[i] = new int[img_arg.get_width()]; 
  }

  for (int i = 0; i < img_arg.get_height(); i++){
    for (int j = 0; j < img_arg.get_width(); j++){
      *iss >> aux_int;
      if (!(iss->eof())){  // Se evalúa si los elementos que esta leyendo corresponde a la cantidad de la dimensión

        if (aux_int <= img_arg.get_greyscale() && aux_int >= 0)
        {
          aux_matrix[i][j] = aux_int;
        }else{
          cerr<<"Error. Elemento de fuera de rango."<<endl; // En caso que haya menos elementos,
          delete_matrix(aux_matrix, img_arg.get_height());
          return false;
        }

      }else{
        cerr<<"Error. Cantidad insuficiente de elementos."<<endl; // En caso que haya menos elementos,
        delete_matrix(aux_matrix, img_arg.get_height());
        return false;
      }   
    }
  }
  *iss >> aux_int; 

  if (!iss->eof()){ // Se evalúa si el siguiente elemento es eof.
    cerr<<"Error. Cantidad excesiva de elementos."<<endl; // En caso que haya más elementos,
    delete_matrix(aux_matrix, img_arg.get_height());
    return false;
  }

  img_arg.fill_matrix(aux_matrix);  // Se llena la matriz de imagen

  delete_matrix(aux_matrix, aux_size);

  return true;
}

// Se destruye la matriz
bool delete_matrix(int ** & matrix, int size){

  for (int i = 0; i<size; i++)              
        delete[] matrix[i];
  delete[] matrix;

  return true;
}