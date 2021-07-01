#include <iostream>
#include <string.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include "Giocatore.hpp"
#include "stanza.hpp"
#include "Funzioni.hpp"
#include "mappa.hpp"
using namespace std;

		Giocatore::Giocatore(mappa* SC, int id, mappa m, int pu){// costruttore
		    La_Mappa=m;
			ID_Giocatore = id;
			Stanza_Corrente = SC;
			Punteggio = pu;
		}

   		mappa Giocatore::getmappa(){
   			return La_Mappa;
   		}
   		
   		int Giocatore::getPunti(){
   			return Punteggio;
		}
		
	    int Giocatore::IncrementaPunti(){
			return Punteggio++;
		}
   		
   		int Giocatore::getGId(){
   			return ID_Giocatore;
   		}
   		
		mappa* Giocatore::getStanza_Corrente(){
			return Stanza_Corrente;
		}
   
   		void Giocatore::setStanza_Corrente(mappa* st){
   			Stanza_Corrente=st;
   		}
   
   		void Giocatore::setMappa(mappa cm){
   			La_Mappa=cm;
   		}
   
    	void Giocatore::Vai_A_Nord(){
			ptr_lista pu; //lista dei giocatori presenti nella stanza
			Stanza* N_Stz; //puntatore a nuova stanza
			Stanza* nd; //puntatore ad una stanza
			Stanza* Stz_PT; //puntatore ad una stanza che viene creata al momento
			Stanza Stz; //stanza a nord - stanza attuale (a seconda se vado nell'if o nell'else)
			Stanza Stz_Att;	//stanza attuale (prima di muovere)
			mappa* MPA;//puntatore a mappa
			
			Stanza* Confine1=new Stanza();//creo 3 puntatori a 3 stanze vicine
			Stanza* Confine2=new Stanza();
			Stanza* Confine3=new Stanza();
			Stanza Stz_Limit;
			
	     	nd=Stanza_Corrente->getValore().getNord();  //puntatore a nord della stanza
	     	
			if(nd!=NULL){//se la stanza esisteva già
				Stz_Att=Stanza_Corrente->getValore(); //assegno stz_att il valore della stanza corrente
				Stz_Att.Rimuovi_Giocatore(ID_Giocatore);  //cancello il giocatore dalla lista di giocatori nella stanza
				Stanza_Corrente->setValore(&Stz_Att); //sostituisco la stanza con una identica ma con un giocatore in meno
			    MPA=La_Mappa.Trova(nd->GetX(), nd->GetY());//cerca la stanza x,y e restituisce un puntatore a una mappa che ha in testa la stanza in cui il giocatore si sposta
				Stz=MPA->getValore(); //stz è la stanza a nord rispetto al giocatore
				Stz.Inserisci_Giocatore(ID_Giocatore); //aggiunge il giocatore nella nuova stanza
				MPA->setValore(&Stz);//aggiorna la lista di giocatori della stanza in cui è entrato il giocatore
				Stanza_Corrente=MPA;//la stanza attuale adesso è quella a nord rispetto alla precedente
			}
		
			else{ //se la stanza a nord non esiste
				Stz=Stanza_Corrente->getValore();  //imposto ad Stz la stanza corrente
			    Stz.Rimuovi_Giocatore(ID_Giocatore); //elimino il giocatore dalla stanza corrente 
				Stz_PT= new Stanza();//creo la stanza (scollegata dalla mappa)
				*Stz_PT=Stz; //stz_PT punta alla stanza corrente 
			    N_Stz= new Stanza(Stz.GetX(),Stz.GetY()+1, NULL ,Stz_PT , NULL , NULL , NULL);	//costruisco una nuova stanza che ha come coordinate X la x della stanza corrente e come Y la y aumentata di 1. la stanza è collegata solo a quella preecedente(a sud non viceversa) e non al resto della mappa		     
			    N_Stz->Inserisci_Giocatore(ID_Giocatore); //aggiungo il giocatore alla nuova stanza

			    MPA = La_Mappa.Trova(N_Stz->GetX()+1,N_Stz->GetY());//cerco se esiste una stanza ad est
			    if (MPA!=NULL){   //se c'è la stanza ad est
			    	(*Confine1)=MPA->getValore();//punto alla stanza nuova
					Stz_Limit=MPA->getValore();// "Stz_Limit" è la stanza ad est
			    	Stz_Limit.setOvest(N_Stz);	//collego la stanza est ad ovest
			    	MPA->setValore(&Stz_Limit);//aggiorno la mappa
					N_Stz->setEst(Confine1);  //nella nuova stanza metto un collegamento ad est
				}
			    MPA=La_Mappa.Trova(N_Stz->GetX(), N_Stz->GetY()+1);//stesso procedimento per le altre possibili stanze limitrofe
			    if (MPA!=NULL){
			    	(*Confine2)=MPA->getValore(); 
			    	Stz_Limit=MPA->getValore();
			    	Stz_Limit.setSud(N_Stz);	
			    	MPA->setValore(&Stz_Limit);
			    	N_Stz->setNord(Confine2);
				
				}
				MPA=La_Mappa.Trova(N_Stz->GetX()-1, N_Stz->GetY());			
			    if (MPA!=NULL){
			    	(*Confine3)=MPA->getValore(); 
			    	Stz_Limit=MPA->getValore();
			    	Stz_Limit.setEst(N_Stz);	
			    	MPA->setValore(&Stz_Limit);
			    	N_Stz->setOvest(Confine3);				  
				}
			    
				Stz.setNord(N_Stz);//collego la stanza precedente a quella attuale
			    Stanza_Corrente->setValore(&Stz);//aggiorna la lista di stanze (con il giocatore in meno)
			    //Stz.setNord(N_Stz);
				La_Mappa.Inserisci(*N_Stz); //inserisce la nuova stanza nella lista di tutte le stanze esistenti
			    Stanza_Corrente=La_Mappa.Trova(N_Stz->GetX() , N_Stz->GetY()); //aggiorno la stanza corrente del giocatore a quella in cui si è spostato
    		}	
    	}

  		void Giocatore::Vai_A_Sud(){//stesso procedimento vedi sopra
			ptr_lista pu;
			Stanza* N_Stz;
			Stanza* sd;
			Stanza* Stz_PT;
			Stanza Stz;
			Stanza Stz_Att;	
			mappa* MPA;
			Stanza* Confine1=new Stanza();
			Stanza* Confine2=new Stanza();
			Stanza* Confine3=new Stanza();
			
			Stanza Stz_Limit;
	     	sd=Stanza_Corrente->getValore().getSud();  
			if(sd!=NULL){
				Stz_Att=Stanza_Corrente->getValore();
				Stz_Att.Rimuovi_Giocatore(ID_Giocatore);  
				Stanza_Corrente->setValore(&Stz_Att); 
			    MPA=La_Mappa.Trova(sd->GetX(), sd->GetY());
				Stz=MPA->getValore();
				Stz.Inserisci_Giocatore(ID_Giocatore); 
				MPA->setValore(&Stz);
				Stanza_Corrente=MPA;
			}
		
			else{
			    Stz=Stanza_Corrente->getValore(); 
			    Stz.Rimuovi_Giocatore(ID_Giocatore); 	
				Stz_PT= new Stanza();
				*Stz_PT=Stz;
			    N_Stz= new Stanza(Stz.GetX(),Stz.GetY()-1, Stz_PT ,NULL , NULL , NULL , NULL);
			    N_Stz->Inserisci_Giocatore(ID_Giocatore); 

			    MPA = La_Mappa.Trova(N_Stz->GetX()+1,N_Stz->GetY()); 
			    if (MPA!=NULL){   
					(*Confine1)=MPA->getValore();
					Stz_Limit=MPA->getValore();
			    	Stz_Limit.setOvest(N_Stz);	
			    	MPA->setValore(&Stz_Limit);
					N_Stz->setEst(Confine1);  
				}
			    MPA=La_Mappa.Trova(N_Stz->GetX(), N_Stz->GetY()-1);
			    if (MPA!=NULL){
			    	(*Confine2)=MPA->getValore(); 
			    	Stz_Limit=MPA->getValore();
			    	Stz_Limit.setNord(N_Stz);	
			    	MPA->setValore(&Stz_Limit);
			    	N_Stz->setSud(Confine2);
				}
				
				MPA=La_Mappa.Trova(N_Stz->GetX()-1, N_Stz->GetY());
						
			    if (MPA!=NULL) {
			    	(*Confine3)=MPA->getValore(); 
			    	Stz_Limit=MPA->getValore();
			    	Stz_Limit.setEst(N_Stz);	
			    	MPA->setValore(&Stz_Limit);
			    	N_Stz->setOvest(Confine3);
				}			    
			    
				Stz.setSud(N_Stz);
			    Stanza_Corrente->setValore(&Stz);
			    Stz.setSud(N_Stz);
				La_Mappa.Inserisci(*N_Stz); 
			    Stanza_Corrente=La_Mappa.Trova(N_Stz->GetX() , N_Stz->GetY());
	      	}
		}
			
		void Giocatore::Vai_A_Ovest(){
			ptr_lista pu;
			Stanza* N_Stz;
			Stanza* ot;
			Stanza* Stz_PT;
			Stanza Stz;
			Stanza Stz_Att;	
			mappa* MPA;
			Stanza* Confine1=new Stanza();
			Stanza* Confine2=new Stanza();
			Stanza* Confine3=new Stanza();

			Stanza Stz_Limit;
			
	    	ot=Stanza_Corrente->getValore().getOvest();  
			if(ot!=NULL){   
				Stz_Att=Stanza_Corrente->getValore();
				Stz_Att.Rimuovi_Giocatore(ID_Giocatore);  
				Stanza_Corrente->setValore(&Stz_Att); 
			    MPA=La_Mappa.Trova(ot->GetX(), ot->GetY());
				Stz=MPA->getValore();
				Stz.Inserisci_Giocatore(ID_Giocatore); 
				MPA->setValore(&Stz);
				Stanza_Corrente=MPA;
			}
			else{		  
				Stz=Stanza_Corrente->getValore();  
			    Stz.Rimuovi_Giocatore(ID_Giocatore); 	
				Stz_PT= new Stanza();
				*Stz_PT=Stz;
			    N_Stz= new Stanza(Stz.GetX()-1,Stz.GetY(), NULL ,NULL , NULL , Stz_PT , NULL);			     
			    N_Stz->Inserisci_Giocatore(ID_Giocatore); 			    

			    MPA = La_Mappa.Trova(N_Stz->GetX(),N_Stz->GetY()-1);
			    if (MPA!=NULL){
					(*Confine1)=MPA->getValore();
					Stz_Limit=MPA->getValore();
			    	Stz_Limit.setNord(N_Stz);	
			    	MPA->setValore(&Stz_Limit);
					N_Stz->setSud(Confine1);
				}
				
				MPA=La_Mappa.Trova(N_Stz->GetX(), N_Stz->GetY()+1);
			     
			    if (MPA!=NULL){
			    	(*Confine2)=MPA->getValore(); 
			    	Stz_Limit=MPA->getValore();
			    	Stz_Limit.setSud(N_Stz);	
			    	MPA->setValore(&Stz_Limit);
			    	N_Stz->setNord(Confine2);
				}
				
				MPA=La_Mappa.Trova(N_Stz->GetX()-1, N_Stz->GetY());
				
			    if (MPA!=NULL) {
			    	(*Confine3)=MPA->getValore(); 
			    	Stz_Limit=MPA->getValore();
			    	Stz_Limit.setEst(N_Stz);
			    	MPA->setValore(&Stz_Limit);
			    	N_Stz->setOvest(Confine3);
					   
				}
			    
				Stz.setOvest(N_Stz);
			    Stanza_Corrente->setValore(&Stz);
			    La_Mappa.Inserisci(*N_Stz);
			    Stanza_Corrente=La_Mappa.Trova(N_Stz->GetX(), N_Stz->GetY());
        	}
    	}
    	
    	void Giocatore::Vai_A_Est(){
			ptr_lista pu;
			Stanza* N_Stz;
			Stanza* et;
			Stanza* Stz_PT;
			Stanza* Confine1=new Stanza();
			Stanza* Confine2=new Stanza();
			Stanza* Confine3=new Stanza();
			Stanza Stz;
			Stanza Stz_Att;	
			mappa* MPA;

			Stanza Stz_Limit;
			
	    	et=Stanza_Corrente->getValore().getEst();  
			if(et!=NULL){
				Stz_Att=Stanza_Corrente->getValore();
				Stz_Att.Rimuovi_Giocatore(ID_Giocatore);  
				Stanza_Corrente->setValore(&Stz_Att); 
			    MPA=La_Mappa.Trova(et->GetX(), et->GetY());
				Stz=MPA->getValore();
				Stz.Inserisci_Giocatore(ID_Giocatore); 
				MPA->setValore(&Stz);
				Stanza_Corrente=MPA;			
			}
		
			else{  			  
				Stz=Stanza_Corrente->getValore();  
			    Stz.Rimuovi_Giocatore(ID_Giocatore); 	
				Stz_PT= new Stanza();
				*Stz_PT=Stz;
			    N_Stz= new Stanza(Stz.GetX()+1,Stz.GetY(), NULL ,NULL, Stz_PT , NULL , NULL);			     
			    N_Stz->Inserisci_Giocatore(ID_Giocatore); 
			    Confine1= new Stanza();
			    Confine2= new Stanza();
			    Confine3= new Stanza();
			    MPA = La_Mappa.Trova(N_Stz->GetX()+1,N_Stz->GetY());
			    if (MPA!=NULL){
					(*Confine1)=MPA->getValore();
					Stz_Limit=MPA->getValore();
			    	Stz_Limit.setOvest(N_Stz);	
			    	MPA->setValore(&Stz_Limit);
					N_Stz->setEst(Confine1);
				}
			    MPA=La_Mappa.Trova(N_Stz->GetX(), N_Stz->GetY()-1); 
			    if (MPA!=NULL){
			    	(*Confine2)=MPA->getValore(); 
			    	Stz_Limit=MPA->getValore();
			    	Stz_Limit.setNord(N_Stz);	
			    	MPA->setValore(&Stz_Limit);
			    	N_Stz->setSud(Confine2);
				}
				
				MPA=La_Mappa.Trova(N_Stz->GetX(), N_Stz->GetY()+1);
								
			    if (MPA!=NULL) {
			    	(*Confine3)=MPA->getValore(); 
			    	Stz_Limit=MPA->getValore();
			    	Stz_Limit.setSud(N_Stz);	
			    	MPA->setValore(&Stz_Limit);
			    	N_Stz->setNord(Confine3);
				}
			    
				Stz.setEst(N_Stz);
			    Stanza_Corrente->setValore(&Stz);
			    Stz.setEst(N_Stz);
			    La_Mappa.Inserisci(*N_Stz); 
			    Stanza_Corrente=La_Mappa.Trova(N_Stz->GetX() , N_Stz->GetY()); 
        	}
    	}		
