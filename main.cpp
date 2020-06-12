#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <math.h>

#include "image.h"
#include "complejo.h"
#include "main.h"

using namespace std; 

//*****************************VARIABLES GLOBALES*****************************//

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

static string PGM_IDENTIFIER = "P2";
static char SKIP_LINE_IDENTIFIER = '#';

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "function", NULL, opt_function, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

enum functions {z, expz, conjugar, inversa, logaritmo, seno, pow2};
static functions chosen_function = z;

// **********************************MAIN**********************************//

int main(int argc, char * const argv[]){
	image input_image;

	cmdline cmdl(options);	       // Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
	cmdl.parse(argc, argv);        // Metodo de parseo de la clase cmdline

	if(!read_pgm(input_image)){    // Se lee la imagen de intrada
		cerr<<"Fallo en el archivo"<<endl;
		return 1;
	}
	
  // Se declara la imagen de salida a partir de las dimenciones de la imagen de entrada
	image output_image(input_image.get_max_dim(),input_image.get_max_dim(),input_image.get_greyscale());

  // Switch que, a partir del parámetro ingresado por consola, define que función implementar mediante puntero a función
	switch(chosen_function){  
		case z:                  
			input_image.print_image(oss);
			return 0;
		break;
		case expz: 
      map_image(input_image, output_image, &complejo::exponencial);
    break;
		case conjugar:
			map_image(input_image, output_image, &complejo::conjugar);
			break;
		case inversa:
			map_image(input_image, output_image, &complejo::inversa);
		break;
		case logaritmo:
			map_image(input_image, output_image, &complejo::logaritmo);
		break;
		case seno:
			map_image(input_image, output_image, &complejo::seno);
		break;
		case pow2:
			map_image(input_image, output_image, &complejo::pow2);
		break;
		default: 
			cerr<< "Error en seleccion de funcion" << endl;
			return 1;
	}

  // Se imprime la imagen de salida
	output_image.print_image(oss);

	return 0;
}

//************************FUNCIONES DE CMDLINE************************//

static void opt_input(string const &arg){

	if (arg == "-") {
		iss = &cin;		// Se establece la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}
	// Verificamos que el stream este OK.
	if (!iss->good()) {
		cerr << "No se puede abrir el archivo de entrada: "<< arg<< "."<< endl;
		exit(1);
	}
}

static void opt_output(string const &arg){

	if (arg == "-") {	// Si el input es -,
		oss = &cout;	// se establece la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}
	if (!oss->good()) {
		cerr << "No se puede abrir el archivo de salida: "<< arg<< "."<< endl;
		exit(1);
	}
}

static void opt_function(string const &arg){

  if (arg == FUNCTION_Z || arg == "-") {chosen_function = z;} // Se establece la función estandar z

  else if (arg == FUNCTION_EXPZ) {chosen_function = expz; }
  else if (arg == FUNCTION_CONJUGAR) {chosen_function = conjugar; }
  else if (arg == FUNCTION_INVERSA) {chosen_function = inversa; } 
  else if (arg == FUNCTION_LOGARITMO) {chosen_function = logaritmo; }
  else if (arg == FUNCTION_SENO) {chosen_function = seno; }
  else if (arg == FUNCTION_POW) {chosen_function = pow2; }
  else {
    cerr << "Funcion invalida" << endl;
    exit(1);
  }
}

static void opt_help(string const &arg){  // La opción -h imprime el formato de ejecución
  cout << "cmdline -f function [-i file] [-o file]" << endl;
  cout << "funciones: z, expz, conjugar, inversa, log, sin, pow" << endl;
	exit(0);
}

//***********************METODOS DE CMDLINE***********************//

cmdline::cmdline(){}

cmdline::cmdline(option_t *table) : option_table(table){}

void cmdline::parse(int argc, char * const argv[]) {
#define END_OF_OPTIONS(p)       \
	((p)->short_name == 0   \
	 && (p)->long_name == 0 \
	 && (p)->parse == 0)

	for (option_t *op = option_table; !END_OF_OPTIONS(op); ++op)
		op->flags &= ~OPT_SEEN;

	for (int i = 1; i < argc; ++i) {

		if (argv[i][0] != '-') {
			cerr << "Argumento inválido." << argv[i] << endl;
			exit(1);
		}

		if (argv[i][1] == '-'
		    && argv[i][2] == 0)
			break;

		if (argv[i][1] == '-')
			i += do_long_opt(&argv[i][2], argv[i + 1]);
		else
			i += do_short_opt(&argv[i][1], argv[i + 1]);
	}

	for (option_t *op = option_table; !END_OF_OPTIONS(op); ++op) {
#define OPTION_NAME(op) \
	(op->short_name ? op->short_name : op->long_name)
		if (op->flags & OPT_SEEN)
			continue;
		if (op->flags & OPT_MANDATORY) {
			cerr << "Opción "<< "-"<< OPTION_NAME(op)<< " es obligatoria."<< "\n";
			exit(1);
		}
		if (op->def_value == 0)
			continue;
		op->parse(string(op->def_value));
	}
}

int cmdline::do_long_opt(const char *opt, const char *arg) {
	// Se recorre la tabla de opciones, y se busca la entrada larga que se corresponda 
  // con la opción de línea de comandos. De no encontrarse, se indica el error correspondiente.
	
	for (option_t *op = option_table; op->long_name != 0; ++op) {
		if (string(opt) == string(op->long_name)) {
			// Se marca esta opción como usada en forma explícita, para evitar tener que inicializarla con el valor por defecto.

			op->flags |= OPT_SEEN;

			if (op->has_arg) {
				if (arg == 0) { // Verificamos que se provea un argumento
					cerr << "La opción requiere el argumento: "<< "--"<< opt<< "\n";
					exit(1);
				}
				op->parse(string(arg));
				return 1;
			} else {
				op->parse(string("")); // Opción sin argumento.
				return 0;
			}
		}
	}
	// Error: opción no reconocida.
	cerr << "Opción desconocida: "<< "--"<< opt<< "."<< endl;
	exit(1);
	return -1;
}

int cmdline::do_short_opt(const char *opt, const char *arg) {
	option_t *op;

	for (op = option_table; op->short_name != 0; ++op) {

		if (string(opt) == string(op->short_name)) {
			op->flags |= OPT_SEEN;
			if (op->has_arg) {
				if (arg == 0) {	
					cerr << "La opción requiere el argumento: "<< "-"<< opt<< "\n";
					exit(1);
				}
				op->parse(string(arg));
				return 1;
			} else {
				op->parse(string(""));
				return 0;
			}
		}
	}
	cerr << "Opción desconocida: "<< "-"<< opt << "." << endl;
	exit(1);
	return -1;
}


// *******************************FUNCIONES**********************************//


// Esta funcion lee del archivo de input y llena la imagen VACIA que se le pasa como argumento. 

bool read_pgm(image & img_arg){
  int aux_int, aux_size[2], aux_greyscale;
  int i=0;
  int ** aux_matrix;
  string in_string, temp;		


  getline(*iss, in_string); // Identificador PGM.

  if (in_string[0] == PGM_IDENTIFIER[0]){
  	if (in_string[1] != PGM_IDENTIFIER[1]){
    	cerr<< "No es PGM" <<endl;   // En caso que el identificador sea incorrecto, imprime un mensaje de error.
    	return false;
  	}
	}
	else {cerr<< "No es PGM" <<endl; return false;}

  getline(*iss, in_string);
  if (in_string[0] == SKIP_LINE_IDENTIFIER){ // Se detecta si se leyó un comentario.
    getline(*iss, in_string); // Se leen las dimensiones de la matriz.
  }

  stringstream ss (in_string); 
  
	while (i < 2 && !ss.eof()){
  	ss >> temp;
  	if(stringstream(temp) >> aux_int){  // Si puedo convertir a int, guardo.
  	  aux_size[i] = aux_int;
  	  i++;
  	}
  	temp = "";
	}
	if (i == 1){
		cout<< "Error en el formato."<<endl;
		return false;
	}

	ss >> temp;
 	if(stringstream(temp) >> aux_int){  // Si puedo convertir a int, es un error.
 		cout<< "Error en el formato."<<endl;
 		return false;
  }

  
  img_arg.set_width(aux_size[0]);  // Se guarda el ancho de la matriz.
  img_arg.set_height(aux_size[1]); // Se guarda el alto de la matriz.
  
  // CCAMBIAR A OPERADOR  >> SI HAY TIEMPO
  getline(*iss, in_string);
  aux_greyscale = stoi(in_string);
  img_arg.set_greyscale(aux_greyscale); // Se guarda el valor de la escala de grises.

  // Crea la matriz de enteros y los llena con ceros.
  // Como la matriz va a ser cuadrada, se pide dos veces de dimension "max".

  aux_matrix = new int*[aux_size[1]]; 
  for (int i = 0; i < aux_size[1]; i++){  
      aux_matrix[i] = new int[aux_size[0]]; 
  }

  for (int i = 0; i < aux_size[1]; i++){
    for (int j = 0; j < aux_size[0]; j++){
    	*iss >> aux_int;
    	if (!(iss->eof())){  // Se evalúa si los elementos que esta leyendo corresponde a la cantidad de la dimensión
    		if (aux_int <= aux_greyscale && aux_int >= 0)
    		{
    			aux_matrix[i][j] = aux_int;
    		}else{
    			cerr<<"Error. Elemento de fuera de rango."<<endl; // En caso que haya menos elementos,
    			for (int i = 0; i<aux_size[1]; i++)        // se destruye matriz auxiliar
        		delete[] aux_matrix[i];
  				delete[] aux_matrix;
    			return false;
    		}
    		

    	}else{
    		cerr<<"Error. Cantidad insuficiente de elementos."<<endl; // En caso que haya menos elementos,
    		for (int i = 0; i<aux_size[1]; i++)        // se destruye matriz auxiliar
        	delete[] aux_matrix[i];
  			delete[] aux_matrix;
    		return false;
    	}   
    }
  }

  *iss >> aux_int; 

  if (!iss->eof()){ // Se evalúa si el siguiente elemento es eof.
  	cerr<<"Error. Cantidad excesiva de elementos."<<endl; // En caso que haya más elementos,
  	for (int i = 0; i<aux_size[1]; i++)      // Se destruye matriz auxiliar en caso de error
      delete[] aux_matrix[i];
  	delete[] aux_matrix;
  	return false;
  }


  img_arg.fill_matrix(aux_matrix);  // Se llena la matriz de imagen

  for (int i = 0; i<aux_size[1]; i++)   // Se destruye la matriz auxiliar              
        delete[] aux_matrix[i];
  delete[] aux_matrix;

  return true;
}


void generate_matrix_c(double max, complejo *** matrix){

	// Esta funcion genera una matriz de complejos con valores que van desde el -1-i hasta el 1+i formando un
	// rectangulo de lado 2, con el centro del plano complejo en el centro de la matriz.
  
  (*matrix) = new complejo*[(int)max]; // Pido memoria para la matriz
  for (int i = 0; i < max; i++){  
   	(*matrix)[i] = new complejo[(int)max];
  }

  double paso=2/(max-1);	// Determina el paso que debe haber debido al salto de una posicion para que en los limites se encutren los unos
  double aux_real=-1;
 	double aux_imag=1;

 	// Se recorre la matriz y se la va rellenando punto a punto con el valor de complejo correspondiente
  for (int i = 0; i < max; i++){    	
    for (int j = 0; j < max; j++){  
      (*matrix)[i][j]=complejo(aux_real,aux_imag);
      aux_real=aux_real+paso; // Se ajusta el valor para la proxima posicion
      }
      aux_real=-1;					  // Se reinicia el valor del x ya que recorre por filas
      aux_imag=aux_imag-paso; // Se ajusta el valor para la proxima posicion
    }
}


int * binary_search(const complejo c, complejo *** matrix, int in_lim[2], int fin_lim[2]){

  // Esta funcion realiza la busqueda del complejo c en la matriz matrix recibida por puntero a traves del metodo binario de busqueda de
  // forma recursiva. in_lim y fin_lim son arreglos de dos posiciones, en la primer posicion de cada uno se encuentra el valor inicial y final
  // para las filas y en la segunda los mismos pero para las columnas.
  // El valor que retorna es la posición de la matiz de donde se encuentra el valor c o el mas proximo a este.
	// Se prueba que los limites iniciales sean menores a los finales, de no ser asi se devuleve NULL
  if (in_lim[0]>fin_lim[0] || in_lim[1]>fin_lim[1]){
    return NULL;
  }


  // Caso base:
  // Cuando se llega a una porcion de matriz de 2x2 se fija cual de los cuatro valores es el más proximo a c y ajusta los limites para 
  // retornar el vector correspondiente
  if ((fin_lim[0]-in_lim[0]) == 1 && (fin_lim[1]-in_lim[1]) == 1){

    if (abs(c.get_real() - ((*matrix)[in_lim[1]][in_lim[0]]).get_real()) > abs(c.get_real() - ((*matrix)[fin_lim[1]][fin_lim[0]]).get_real())){
      in_lim[0] = fin_lim[0];
    }
    if (abs(c.get_img() - ((*matrix)[in_lim[1]][in_lim[0]]).get_img()) > abs(c.get_img() - ((*matrix)[fin_lim[1]][fin_lim[0]]).get_img())){
      in_lim[1] = fin_lim[1];
    }
    return in_lim;
  }else if ((fin_lim[0]-in_lim[0]) == 0 && (fin_lim[1]-in_lim[1]) == 0){ 	// Si encontro el valor exacto lo devuelve. Solo llegar si la matri
   																																				//de la imagen original es de 1x1 porque sino va a terminar en el cb anterior.
  	in_lim[1] = fin_lim[1];
  	return in_lim;
  }


  // Se calcula la posicion del medio
  int medio_x = in_lim[0]+(fin_lim[0]-in_lim[0])/2;
  int medio_y = in_lim[1]+(fin_lim[1]-in_lim[1])/2; 

  // Se evalua si la parte real del complejo es mayor a la prate real del medio, y luego lo mismo
  // para la parte imaginaria. Luego se ajustan los limites para el proximo llamado.

  if (c.get_real()>= ((*matrix)[medio_y][medio_x]).get_real()){ // Se fija si se encuentra en el semiplano derecho
    in_lim[0] = medio_x;
    if (c.get_img()>= ((*matrix)[medio_y][medio_x]).get_img()){	// Se fija si se encuentra en el semiplano superior
      fin_lim[1] = medio_y;
      return binary_search(c, matrix, in_lim, fin_lim);
    }else{
      in_lim[1] = medio_y;
      return binary_search(c, matrix, in_lim, fin_lim);
    }

  }else{
    fin_lim[0] = medio_x;
    if (c.get_img()>=((*matrix)[medio_y][medio_x]).get_img()){ // Se fija si se encuentra en el semiplano superior
      fin_lim[1] = medio_y;
      return binary_search(c, matrix, in_lim, fin_lim);
    }else{
      in_lim[1] = medio_y;
      return binary_search(c, matrix, in_lim, fin_lim);
    }
  } 
}


void map_image(image & original, image & destino, complejo(complejo::*function_pointer)(void)){

  int * pos;
  int in_lim[2];
  int fin_lim[2];
  int aux_color;
  int max = original.get_max_dim();
  complejo aux;
  complejo ** complex_matrix;

  // Se genera la matriz de complejos de tamaño max por max
  generate_matrix_c(original.get_max_dim(), &complex_matrix);

  // Se recorre la matriz de complejos para transformar cada uno de los puntos.
  // Los indices de la matriz de complejos coinciden con los de la matriz destino, por lo tanto 
  // alcanza con recorrer solo una de las dos.
  for(int i=0; i < destino.get_max_dim();i++){
    for (int j = 0; j < destino.get_max_dim(); j++)
    {
    	// Se inicializan los limites para la busqueda binaria
      in_lim[0]=0;
      in_lim[1]=0;
      fin_lim[0]=max-1; 
      fin_lim[1]=max-1;

      // Se guarda el valor de la matriz de complejos para luego realizar la transformacion
      aux = complex_matrix[i][j];

      aux = (aux.*function_pointer)();

  		// Se corrobora que el valor c a buscar este dentro de el semiplano que conforman los puntos (-1+i), (-1-i), (1-i) y (1+i)
  		// sino lo esta, no se hace nada, ya que como la matriz de la imagen destino se encuentra rellena de ceros (negro)
  		if(abs(aux.get_real()) <= 1 && abs(aux.get_img()) <= 1){
    		pos = binary_search(aux,&complex_matrix,in_lim,fin_lim);
    	 	if (pos !=NULL){ 		// Si no se detecta un error se se guarda el color en la imagen destino
    	    	aux_color = original.get_matrix_value(pos[1],pos[0]);
        		destino.set_matrix_value(i,j,aux_color);
      	}
      	else {
      		cerr<<"Error en busqueda binaria."<<endl;
      		for (int i = 0; i<max; i++){    	// Borra la memoria pedida por generate_matrix_c
      			if (complex_matrix[i]){          
        			delete[] complex_matrix[i];
      			}
    			}
  				delete[] complex_matrix;
      	}
    	}
  	}
  }
  
  for (int i = 0; i<max; i++){    	// Borra la memoria pedida por generate_matrix_c
      if (complex_matrix[i]){          
        delete[] complex_matrix[i];
      }
    }
  delete[] complex_matrix;
} 
