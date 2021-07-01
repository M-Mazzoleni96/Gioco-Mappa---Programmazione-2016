#include <iostream>
#include <string.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "stanza.hpp"
#include "mappa.hpp"
#include "Giocatore.hpp"
#include "Funzioni.hpp"
using namespace std;

typedef lista* ptr_lista;

int main (){
	ptr_lista pu=NULL;
	Stanza *S = new Stanza;
	int npl=0;
	system("color 71");
	do{
		cout<<"Inserisci numero giocatori: ";
		cin>>npl;
		if(npl<=0)
			cout<<"INPUT INVALIDO"<<endl;
	}while(npl<=0);
    cout<<"inizializzazione giocatori"<<endl;//questo è un finto loading. in attesa che finisca lo sleep più in basso
    
    for(int i=1; i<=npl; i++){
    	pu=InserisciElemento(pu,i);//i giocatori vengono inseriti in coda alla lista
	}//pu è il puntatore alla lista dei giocatori
	
    mappa* m=new mappa();//puntatore a mappa che contiene solo la stanza iniziale 0,0
    mappa Cmap;//Cmap è la lista globale di stanze
    
    *S=m->getValore();//puntatore alla stanza 0,0
    S->setp(pu); //aggiorno il puntatore alla lista giocatori della stanza 0,0 
	m->setValore(S); //inserisco la stanza S nella mappa
   	
    Cmap.Setmp(m); //inizializzo con l'unica stanza esistente al momento
    
	int giocatoreCorrente = 0;
    Giocatore** g = new Giocatore*[npl]; //g è un vettore di puntatori a Giocatore di dimensione npl
    
	for(int i = 1; i <= npl;i++){//creo n giocatori
		g[i] = new Giocatore(m,i,Cmap,0); //l'ultimo parametro è il punteggio
	}
	
	cout<<endl;
	
    int mosse=dado(npl*2)+npl; //il numero di mosse è random ma non è mai inferiore al numero di giocatori
    
	cout<<"il dado ha deciso che si eseguiranno "<<mosse<<" mosse"<<endl;//si gioca a mosse invece che a turni
   	
	Sleep(2000);
	system("cls");
	
	for(int i=0; i<mosse; i++){
		char mossa;
		
		for(int w=1; w<=npl; w++){//stampa del punteggio provvisorio di tutti i giocatori. grazie a cls sembra una lista interattiva
			cout<<"Punteggio giocatore "<<w<<": "<<g[w]->getPunti()<<endl;
		}
		
		cout<<"Mossa "<<i+1<<"/"<<mosse<<endl;
		Cmap.Disegna_Mappa(npl);
		giocatoreCorrente=dado(npl);
		cout<<"muove il giocatore "<<giocatoreCorrente<<endl;
		
		do{//inserimento della mossa con controllo dell'input
			cout<<"seleziona Nord (n), Sud (s), Ovest (o), Est (e): ";
				cin>>mossa;
			if(mossa!='n' && mossa!='s' && mossa!='o' && mossa!='e')
				cout<<"INPUT ERRATO"<<endl;
		}while(mossa!='n' && mossa!='s' && mossa!='o' && mossa!='e');
		
		g[giocatoreCorrente]->setMappa(Cmap);//aggiorno la lista di stanze aperte per il giocatore
		
		if(mossa=='n')//input movimento
			g[giocatoreCorrente]->Vai_A_Nord();
		else if(mossa=='s')
			g[giocatoreCorrente]->Vai_A_Sud();
		else if(mossa=='o')
			g[giocatoreCorrente]->Vai_A_Ovest();
		else if(mossa=='e')
			g[giocatoreCorrente]->Vai_A_Est();

		Cmap=g[giocatoreCorrente]->getmappa(); //aggiorno la lista di stanze aperte nella mappa globale
		g[giocatoreCorrente]->IncrementaPunti(); //ogni giocatore guadagna un punto per ogni mossa

		system("cls");
		
	}//finite tutte le mosse
	Cmap.Disegna_Mappa(npl);//stampa della mappa finale
	StampaVincitori(npl,g);//stmapa punteggio finale dei giocatori e stabilisce chi ha vinto
	cout<<"GAME OVER"<<endl;
	system("pause");
	return 0;
}
