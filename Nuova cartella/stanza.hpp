#ifndef STANZA_HPP
#define STANZA_HPP
#include <iostream>
#include <string.h>
#include <math.h>
#include <ctime>
#include <cstdlib>

struct lista {
	int val;
	lista *next;
};
typedef lista* ptr_lista;
class Stanza {
	protected:
		typedef lista* ptr_lista;
		ptr_lista p; // puntatore lista dei giocatori presenti nella Stanza
		int x,y; // coordinate Stanza
		Stanza* nord; // puntatore a nord
		Stanza* sud; // puntatore a sud
		Stanza* ovest; // puntatore a ovest
		Stanza* est; // puntatore a est
		
		public:
			
			Stanza();
			
			Stanza(int ics, int ipsilon, Stanza* n,Stanza* s, Stanza* o, Stanza* e, ptr_lista pu);
			
			void setp(ptr_lista pu);
			
			void setx(int n);
			
			void sety(int n);
		
			ptr_lista getp();
			
			int GetX();
			
			int GetY();
			
			Stanza* getNord();
			
			Stanza* getSud();
		
			Stanza* getOvest();
		
			Stanza* getEst();
			
			void setNord(Stanza* n);
		
			void setSud(Stanza* s);
		
			void setEst(Stanza* e);
	
	    	void setOvest(Stanza* o);
		
			void Inserisci_Giocatore(int n);
		
			void Rimuovi_Giocatore(int n);

};
#endif
