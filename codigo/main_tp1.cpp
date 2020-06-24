#include "main_tp1.h"

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

static string entered_function;		// Funcion leida directamente de consola

// **********************************MAIN**********************************//

int main(int argc, char * const argv[]){
	image input_image;
	string * string_array;
	size_t string_array_size= 0;
	stk <string> output_stk;

	cmdline cmdl(options);	       // Objeto con parametro tipo option_t (struct) declarado globalmente
	cmdl.parse(argc, argv);        // Metodo de parseo de la clase cmdline


	// Se lee la imagen de entrada
	if(!read_pgm(input_image)){   
		cerr<<"Error. Fallo en el archivo."<<endl;
		return 1;
	}
	
	// Se declara la imagen de salida a partir de las dimenciones de la imagen de entrada
	image output_image(input_image.get_max_dim(),input_image.get_max_dim(),input_image.get_greyscale());

	// Se parsea la funcion ingresada para aplicarle el algoritmo Shunting-Yard
	string_array = parse_function(entered_function, string_array_size);	
	
	// Se aplica el algoritmo Shunting-Yard al array de strings y se guarda la funcion en RPN en output_stk
	shunting_yard(output_stk, string_array, string_array_size);

  // Se mapea la imagen de salida resolviendo la expresion ingresada
	map_image(input_image, output_image, output_stk);

	// Se imprime la imagen de salida
	output_image.print_image(oss);

	delete[] string_array;

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
		cerr << "No se puede abrir el archivo de salida: "<< arg << "." << endl;
		exit(1);
	}
}

static void opt_function(string const &arg){
	entered_function = arg;
}

static void opt_help(string const &arg){  // La opción -h imprime el formato de ejecución
  cout << "cmdline -f function [-i file] [-o file]" << endl;
  cout << "Funciones: exp(z), ln(z), re(z), im(z), abs(z), phase(z)." << endl;
  cout << "Operadores: +, -, *, /." << endl;
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

// Esta funcion lee del archivo de input y llena la imagen VACIA que se le pasa como argumento 
bool read_pgm(image & img_arg){

  string in_string;		

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
  int aux_int;
  int ** aux_matrix;

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

  return true;
}















void map_image(image & original, image & destino, stk <string> output_stk){

  int pos[2];
  int aux_color;
  double max = original.get_max_dim();
  complejo aux;

  double paso=2/(max-1);	// Determina el paso que debe haber debido al salto de una posicion para que en los limites se encutren los unos
  double aux_real=-1;
  double aux_imag=1;
  
  // Se recorre la matriz de complejos para transformar cada uno de los puntos.
  // Los indices de la matriz de complejos coinciden con los de la matriz destino, por lo tanto 
  // alcanza con recorrer solo una de las dos.
  for(int i=0; i < max;i++){

    for (int j = 0; j < max; j++)
    {

 	    // Se crea un complejo a el cual se le va a realizar la transformacion
    	complejo aux (aux_real,aux_imag);

      // Se iguala el stack en RPN a uno vacio para no perder la funcion cuando se desapile
    	stk <string> stk_to_solve = output_stk;

      // Se transforma el complejo
		  solve_rpn(stk_to_solve, aux);

		  string aux_string;

      if(!stk_to_solve.peek(aux_string)){
       cerr << "Stack is empty" << endl;
       exit(1);
      }

		stringstream s1 (aux_string); 
		s1 >> aux;

  		// Se corrobora que el valor c a buscar este dentro de el semiplano que conforman los puntos (-1+i), (-1-i), (1-i) y (1+i)
  		// sino lo esta, no se hace nada, ya que la matriz de la imagen destino se encuentra rellena de ceros (negro)

  		if(abs(aux.get_real()) <= 1 && abs(aux.get_img()) <= 1){

  			search(pos,aux,max);
        aux_color = original.get_matrix_value(pos[1],pos[0]);
        destino.set_matrix_value(i,j,aux_color); // Se guarda el valor del pixel en la imagen destino

    	}
    	aux_real=aux_real+paso;	// Se ajusta el valor para la proxima posicion
  	}
  	aux_real=-1;	// Se reinicia el valor del x ya que recorre por filas
    aux_imag=aux_imag-paso;	// Se ajusta el valor para la proxima posicion

  }

}


void search(int * pos,const complejo c, const double max){
	double paso=2/(max-1);	// Determina el paso que debe haber debido al salto de una posicion para que en los limites se encutren los unos
	double cte = 1;
	int i=0 , j=0;

	i = round((c.get_real()+cte)/paso);
	
	j = round((cte-c.get_img())/paso);

	if (j>=max)
		j=max-1;
	if (i>=max)
		i=max-1;

	
	pos[0]=i;
	pos[1]=j;

	return;
}

// Se destruye la matriz
bool delete_matrix(int ** &matrix, int size){
  for (int i = 0; i<size; i++)              
        delete[] matrix[i];
  delete[] matrix;

  return true;
}