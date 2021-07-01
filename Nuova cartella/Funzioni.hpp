#ifndef FUNZIONI_HPP
#define FUNZIONI_HPP
#include <iostream>
#include <string.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include "Giocatore.hpp"

ptr_lista InserisciElemento(ptr_lista head, int e);

ptr_lista RimuoviElemento(ptr_lista l, int e);

int dado(int num);

void StampaVincitori(int npl, Giocatore** g);
#endif
