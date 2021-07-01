#include <iostream>
#include <string.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include "stanza.hpp"
#include "funzioni.hpp"
using namespace std;

		Stanza::Stanza(){ //viene richiamato una volta sola all'inizio del gioco
				p=NULL;
				x=0;
				y=0;
				nord = NULL;
				sud = NULL;
				ovest = NULL;
				est = NULL;
			}
			
			
			
		Stanza::Stanza(int ics, int ipsilon, Stanza* n,Stanza* s, Stanza* o, Stanza* e, ptr_lista pu){
			p=pu; //punatore alla lista contenente i giocatori che si trovano nella stanza
			nord=n;
			sud=s;
			ovest=o;
			est=e;
			x=ics;
			y=ipsilon;
		}
			
		void Stanza::setp(ptr_lista pu){
				p=pu;
			}
			
		void Stanza::setx(int n){
			x=n;
		}
		void Stanza::sety(int n){
			y=n;
		}
		
		 ptr_lista Stanza::getp(){
			return p;
		} 
		int Stanza::GetX(){
			return x;
		}
		int Stanza::GetY(){
			return y;
		}
		Stanza* Stanza::getNord(){
			return nord;
		}
		Stanza* Stanza::getSud(){
			return sud;
		}
		
		Stanza* Stanza::getOvest(){
			return ovest;
		}
		
		Stanza* Stanza::getEst(){
			return est;
		}
			
		void Stanza::setNord(Stanza* n){
			nord=n;
		}
		
		void Stanza::setSud(Stanza* s){
			sud=s;
		}
		
		void Stanza::setEst(Stanza* e){
			est=e;
		}
	
	   	void Stanza::setOvest(Stanza* o){
	   		ovest=o;
		}	
		
		void Stanza::Inserisci_Giocatore(int n){//aggiorna la lista di giocatori aggiungendo il giocatore n
			p=InserisciElemento(p,n);
		}
		
		void Stanza::Rimuovi_Giocatore(int n){//aggiorna la lista di giocaotori eliminando il giocatore n
			p=RimuoviElemento(p,n);
		}


