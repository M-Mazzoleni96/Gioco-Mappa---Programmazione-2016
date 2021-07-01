#ifndef MAPPA_HPP
#define MAPPA_HPP
#include <iostream>
#include <string.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include "stanza.hpp"

class mappa{//una mappa è una lista di stnaze

	protected:
		
		Stanza Valore;
		mappa* mp; //Puntatore alla lista
		
	public:
		mappa *next;
		
		mappa();	
	
		mappa(Stanza l, mappa *n);
	
		void Setmp(mappa* MP);
	
		void setValore(Stanza *Stz);
			
		Stanza getValore();
		
		void Inserisci(Stanza S);//aggiorna la lista di stanze aggiungendo la stanza S in testa richiamando il costruttore mappa
		
		void stampa_Giocatori(ptr_lista p, int n);
		
		int MaxY();

		int MaxX();
	
		int MinY();

		int MinX();
		
		mappa* Trova(int i,int j);

		void Disegna_Mappa(int npl);
};
#endif
