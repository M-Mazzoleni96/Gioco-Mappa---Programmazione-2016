#include <iostream>
#include <string.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include "Funzioni.hpp"
using namespace std;
ptr_lista InserisciElemento(ptr_lista head, int e){//funzione per l'inserimento in coda
	
	ptr_lista p;
	if (head == NULL){
		head = new lista;
		head->val = e;
		head->next = NULL;
	}
	else{
		p = head ;
		while ((p->next)!= NULL) p = p->next;
		p->next = new lista;
		p = p->next;
		p->val = e;
		p->next = NULL;
	}
	
	return (head);
}

ptr_lista RimuoviElemento(ptr_lista l, int e){ //funzione per l'eliminazione di un elemento cercato in una lista

ptr_lista s;
if(l!=NULL) {//se esiste la lista
	
	if(l->val==e) {//se il primo elemento è quello cercato
      l=l->next; //cancello l'elemento escludendolo dalla lista 
    }

    else if(l->next!=NULL) {//se la lista ha più di un elemento
      s=l;//per non perdere il puntatore alla testa della lista mi appoggio su s
      while(s->next!=NULL) {//finchè la lista non è finita
        if(s->next->val == e) {//controllo dal secondo elemento
          s->next=s->next->next; //cancello l'elemento escludendolo dalla lista 
        }
        else
          s=s->next;//vado avanti nella lista
      }
    }
    
  }
  return (l);//ritorno la testa della lista modificata
}
 


int dado(int num){
	int n;	
	srand(time(0));
	n = (rand() % num) +1;
	return (n);
}

void StampaVincitori(int npl, Giocatore** g){
	int max=0,w;
	char win;
	for(w=1; w<=npl; w++){//si trova il giocatore con il punteggio più alto
			cout<<"Punteggio giocatore "<<w<<": "<<g[w]->getPunti()<<endl;
			if(g[w]->getPunti()>max){
				win=w;
				max=g[w]->getPunti();
			}
	}
	for(w=1; w<=npl; w++){//questo ciclo serve nel caso in cui più giocatori abbiano ottenuto lo stesso punteggio
		if(g[w]->getPunti()==g[win]->getPunti())
			cout<<"-> Ha vinto il giocatore "<<g[w]->getGId()<<" ottenendo un punteggio di "<<g[w]->getPunti()<<" punti"<<endl;
	}
}

