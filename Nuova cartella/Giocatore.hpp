#ifndef GIOCATORE_HPP
#define GIOCATORE_HPP
#include <iostream>
#include <string.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include "mappa.hpp"

class Giocatore {
    protected:
    	mappa La_Mappa; //lista di tutte le stanze esistenti
		mappa* Stanza_Corrente; //puntatore Stanza corrente
 		int ID_Giocatore; // identificativo numerico giocatore
		int Punteggio; //punteggio accumulato
	public:		
			
		Giocatore(mappa* SC, int id, mappa m, int pu);

   		mappa getmappa();
   		
   		int getPunti();
		
	    int IncrementaPunti();
   		
   		int getGId();
   		
		mappa* getStanza_Corrente();
   
   		void setStanza_Corrente(mappa* Stz);
   
   		void setMappa(mappa cm);
   
    	void Vai_A_Nord();

  		void Vai_A_Sud();
	
		void Vai_A_Est();
		
		void Vai_A_Ovest();
};

#endif
