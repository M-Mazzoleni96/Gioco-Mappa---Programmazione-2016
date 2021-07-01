#include <iostream>
#include <string.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include "mappa.hpp"
#include "Funzioni.hpp"
using namespace std;
//una mappa è una lista di stanze

		mappa::mappa(){//crea la prima stanza (0,0)
			Valore = Stanza();	
	    	next=NULL;	
		}
		
		void mappa::Setmp(mappa* MP){
			mp=MP;
		}
		
		mappa::mappa(Stanza l, mappa *n){//costruttore che aggiunge in testa una nuova stanza l
			Valore=l;
			next=n;	//le nuove stanze vengono aggiunte in testa alla lista
		}	

		void mappa::setValore(Stanza *Stz){
			Valore=*Stz;
		}
			
		Stanza mappa::getValore(){
			return Valore;
		}
    	
		
		void mappa::Inserisci(Stanza S){//aggiorna la lista di stanze aggiungendo la stanza S in testa richiamando il costruttore mappa
			mp = new mappa(S, mp);
		}
		
		int mappa::MaxY(){//scorre lista di stanze e trova la y maggiore
			mappa* tmp = mp;
			int max=0;
			Stanza s;
			while (tmp!=NULL){
				s=tmp->getValore();
				if (s.GetY() > max) 
					max =s.GetY();
				tmp=tmp->next;
			}
			return (max);	
		}

		int mappa::MaxX(){//scorre lista di stanze e trova la x maggiore
			mappa* tmp = mp;
			int max=0;
			Stanza s;
			while (tmp!=NULL){
				s=tmp->getValore();
				if (s.GetX() > max) 
					max=s.GetX();
				tmp=tmp->next;
			}
			return (max);	
		}	

		int mappa::MinY(){//scorre lista di stanze e trova la y minore
			mappa* tmp = mp;
			int min=0;
			Stanza s;
			while (tmp!=NULL){
				s=tmp->getValore();
				if (s.GetY() < min) 
					min =s.GetY();
				tmp=tmp->next;
			}
			return (min);	
		}

		int mappa::MinX(){//scorre lista di stanze e trova la x minore
			mappa* tmp = mp;
			int min=0;
			Stanza s;
			while (tmp!=NULL){
				s=tmp->getValore();
				if (s.GetX() < min) 
					min=s.GetX();
				tmp=tmp->next;
			}
			return (min);	
		}
		
		mappa* mappa::Trova(int x,int y){ //cerca se la stanza esiste
			mappa* tmp=mp;
			mappa* tmp1=NULL;
			Stanza s;
			bool trovato = false;
			while(tmp!=NULL && !trovato){//scorre tutta la lista per cercare le coordinate
				s=tmp->getValore();
				if (x==s.GetX()){
					if (y==s.GetY()){
						trovato=true;
						tmp1=tmp;
					}
				}
				tmp=tmp->next;
			}
			return tmp1;
		}
		
		void mappa::stampa_Giocatori(ptr_lista p, int n){
			int i, car=0;
			while (p!=NULL){		
				cout<<p->val;
				if(p->val>9)
					car=car+2;//conto i caratteri per formattare la stampa
				if(p->val<=9)
					car++;
				if(p->next!=NULL){
					car++;
					cout<<",";
				}
				p=p->next;
			}	
			for (i=0; i<=3*n-car-11; i++){ //La riga viene riempita di tanti spazi quanti ne mancano per avere la stessa lunghezza che si avrebbe con tutti i giocatori in una sola stanza
				cout <<" ";
			}
			cout<<"\t";//tabulazione per allineamento ancora migliore
		}

		void mappa::Disegna_Mappa(int npl){
			int Y, X;
			mappa* tmp;
			
			for (Y=MaxY(); Y>=MinY(); Y--){//for annidati per stampa della mappa intera usando le 4 coordinate estreme come riferimenti
				for (X=MinX(); X<=MaxX(); X++){			
			       tmp=Trova(X,Y);//con la funzione trova cerco se con le attuali coordinate X e Y ho qualche risultato. se ce l'ho, la stanza esiste e la devo stmapare
			       if (tmp!=NULL){//se la stanza esiste
		    			stampa_Giocatori((tmp->getValore()).getp(),npl); 	  
						if(X>=0 && Y>=0)
		    				cout<<"[ "<< X << ", "<< Y << "]"<<"\t";//il nome della mappa viene stampato in modo che tutte le parentesi siano larghe in egual misura
				   		else if(X<0 && Y<0)
		           			cout<<"[" << X << "," << Y << "]"<<"\t";
				   		else if(X<0 && Y>=0)
		           			cout<<"[" << X << ", " << Y << "]"<<"\t";
				   		else if(X>=0 && Y<0)
		           			cout<<"[ " << X << "," << Y << "]"<<"\t";
					}	        		
		        	else {//se la stanza non esiste
						stampa_Giocatori(NULL,npl); 
				 		cout << "\t";
					}
				}
				cout<<endl<<endl;//do 2 invii così le righe non vengono stampate troppo vicine
			}
	    }	

