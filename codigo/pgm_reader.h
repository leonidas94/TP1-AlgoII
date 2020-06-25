#ifndef PGM_READER__H
#define PGM_READER__H

#include <iostream>
#include <string>
#include <sstream>
#include "image.h"

bool read_pgm(istream *, image &);

bool read_identifier(istream *);
bool read_size(istream *, image &);
void read_greyscale(istream *, image &);
bool read_matrix (istream *, image &);

bool delete_matrix(int ** &, int);

#endif