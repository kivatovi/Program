#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;
//#include "polje.h"
#include "pokazivac.h"

klient *polje;
int gener(que *Q){
	int n;
	cout << "Koliko cetvorki zelite generirati? ";
	cin >> n;
	polje = new klient [n];
	for(int i=0; i<n; i++){
		polje[i].ai = 10 + rand()%491;
		polje[i].bi = 80 + rand()%721;
		polje[i].ci = 1 + rand()%5;
		polje[i].di = 1 + rand()%5;
	}
	cout << "Uspjesno je generirano " <<endl<<endl;
	for(int i=0; i<n; i++)
		cout << i+1 << ". cetvorka: " << polje[i].ai << ", " << polje[i].bi << ", " << polje[i].ci << ", " << polje[i].di << endl;
		cout<<endl;
        return n;
}
        void ispis_cetvorki(int a, int b, int c, int d){
        	cout << "Dolazak u red nakon prethodnog: " << a << " s\n";
        	cout << "Trajanje posluzivanja: " << b << " s\n";
        	cout << "Priroritet klijenta (1-5) ";
        	switch(c){
        		case 1: cout << "-1- VIP klijent"<<endl; break;
        		case 2: cout << "-2- Osoba sa invaliditetom"<<endl; break;
        		case 3: cout << "-3- Trudnica"<<endl; break;
        		case 4: cout << "-4- Umirovljenik"<<endl; break;
        		case 5: cout << "-5- Ostali"<<endl; break;
        	}
        	cout << "Vrsta usluge (1-5) ";
        	switch(d){
        		case 1: cout << "-1- Predaja/preuzimanje posiljke"<<endl; break;
        		case 2: cout << "-2- Placanje racuna"<<endl; break;
        		case 3: cout << "-3- Uplata lutrije"<<endl; break;
        		case 4: cout << "-4- Western Union"<<endl; break;
        		case 5: cout << "-5- Evotv"<<endl; break;
        	}
        }
        void sortiraj (que *Q){
        	que *PQ = InitQ(PQ);
        	que *PQ2 = InitQ(PQ2);
        	klient x;
        	while(!IsEmptyQ(Q)){
        		x = FrontQ(Q);
        		DeQueueQ(Q);
        		EnQueueQ(x, PQ);
        	}
        	for(int i=1; i<=5; i++){
        		while(!IsEmptyQ(PQ)){
        			x = FrontQ(PQ);
        			DeQueueQ(PQ);
        			if(x.ci == i) EnQueueQ(x, Q);
        			else EnQueueQ(x, PQ2);
        		}
        		while(!IsEmptyQ(PQ2)){
        			x = FrontQ(PQ2);
        			DeQueueQ(PQ2);
        			EnQueueQ(x, PQ);
        		}
        	}
        }
        void unos(que *Q, int brN){
        	bool trud, opet;
        	cout << "Unos po 5 klijenata za svaku generiranu kombinaciju"<<endl;
        	for(int i=0; i<brN; i++){
        		cout << i+1 << ". kombinacija"<<endl;
        		ispis_cetvorki(polje[i].ai, polje[i].bi, polje[i].ci, polje[i].di);
        		trud = false;
        		for(int j=0; j<5; j++){
        			cout << j+1 << ". klijent"<<endl;
        			klient x;
        			if(polje[i].ci==3){
        				trud = true;
         				cout << "Klijent je trudnica, spol zenski... Automatski upisano!"<<endl;
         				x.spol='Z';
         			}
        			cout << "Ime: ";
        			cin.ignore();
        			getline(cin, x.ime);
        			cout << "Prezime: ";
        			getline(cin, x.prezime);
        			do{
        				cout << "Dan: ";
        				cin >> x.dan;
        				if(x.dan<1 || x.dan>31) cout << "nije u rasponu od 1 do 31"<<endl;
        			}while(x.dan<1 || x.dan>31);
        			do{
        				cout << "Mjesec: ";
        				cin >> x.mj;
        				if(x.mj<1 || x.mj>12) cout << "nije u rasponu od 1 do 12"<<endl;
        			}while(x.mj<1 || x.mj>12);
        			do{
        				opet = false;
        				cout << "Godina: ";
        				cin >> x.god;
        				if(x.god<1900 || x.god>2014){
        					cout << "nije u rasponu od 1900 do 2014"<<endl;
        					opet = true;
        				}
        				if(polje[i].ci==4 && ((2014 - x.god)<40)){
        					cout << "nije stariji od 40 godina!"<<endl;
        					opet = true;
        				}
        			}while(opet);
        			if(!trud){
        				do{
        					cout << "Spol (M/Z): ";
        					cin >> x.spol;
        					if(toupper(x.spol)!='M' && toupper(x.spol)!='Z') cout << "Pogresan unos!"<<endl;
        				}while(toupper(x.spol)!='M' && toupper(x.spol)!='Z');
        			}
        			x.ai = polje[i].ai;
        			x.bi = polje[i].bi;
        			x.ci = polje[i].ci;
        			x.di = polje[i].di;
        			ispis_cetvorki(x.ai, x.bi, x.ci, x.di);
        			EnQueueQ(x, Q);
        			if(x.ci<5) sortiraj(Q);
        			cout << "Dodana!"<<endl;
        		}
        	}
        }
    bool horoskop(klient x){
    	if(((x.dan>=22) && x.mj==12) || ((x.dan<=20) && x.mj==1)) return true; 
    	else return false;
    }  //korisnici horoskopskog znaka Jarac... provjera
        void ispis_klijenta(klient x){
        	cout << "Ime: " << x.ime << endl;
        	cout << "Prezime: " << x.prezime << endl;
        	cout << "Datum rodenja: " << x.dan << "." << x.mj << "." << x.god << endl;
        	cout << "Spol: " << x.spol << endl;
        	ispis_cetvorki(x.ai, x.bi, x.ci, x.di);
        }
        void ispis_jarac(que *Q){
        	cout << "Klijenti koji su po horoskopskom znaku Jarac uz to su mladi od 40 godina te cekaju na uplatu lutrije"<<endl;
        	que *PQ = InitQ(Q);
        	klient x;
        	bool jarac;
        	while(!IsEmptyQ(Q)){
        		x = FrontQ(Q);
        		DeQueueQ(Q);
        		EnQueueQ(x, PQ);
        		jarac = horoskop(x);
        		if(x.di==3 && jarac && ((2014 - x.god)<40))
        			ispis_klijenta(x);
        	}
        	while(!IsEmptyQ(PQ)){
        		x = FrontQ(PQ);
        		DeQueueQ(PQ);
        		EnQueueQ(x, Q);
        	} //vracamo se u glavni red...
        }
        void ispis_red(que *Q){
        	if(IsEmptyQ(Q)) return;
        	klient x = FrontQ(Q);
        	ispis_klijenta(x);
        	DeQueueQ(Q);
        	ispis_red(Q);
        	EnQueueQ(x, Q);
        }
        void vrati(que *Q){
        	if(IsEmptyQ(Q)) return;
        	klient x = FrontQ(Q);
        	DeQueueQ(Q);
        	vrati(Q);
        	EnQueueQ(x, Q);
        }
        void izlaz_trudnice(que *Q){
        	if(IsEmptyQ(Q)) return;
        	klient x;
        	bool pop;
        	do{
        		pop = false;
        		x = FrontQ(Q);
        		if(x.ci==3 && x.di==5){
        			pop = true;
        			DeQueueQ(Q);
        		}
        		if(IsEmptyQ(Q)) break;
        	}while(pop);
        	if(!IsEmptyQ(Q)) DeQueueQ(Q);
        	izlaz_trudnice(Q);
        	if(!pop) EnQueueQ(x, Q);
        }
        void rasporedi(que *Q, que *Q1, que *Q2, que *Q3, que *Q4, que *Q5, que *FQ){
        	if(IsEmptyQ(Q)) return;
        	klient x = FrontQ(Q);
        	DeQueueQ(Q);
        	if(x.ci==4) EnQueueQ(x, FQ);
        	else {
        		switch(x.di){
        			case 1: EnQueueQ(x, Q1); break;
        			case 2: EnQueueQ(x, Q2); break;
        			case 3: EnQueueQ(x, Q3); break;
        			case 4: EnQueueQ(x, Q4); break;
        			case 5: EnQueueQ(x, Q5); break;
        		}
        	}
        	rasporedi(Q, Q1, Q2, Q3, Q4, Q5, FQ);
        }
        void brzi(que *FQ, que *Qn){
        	static int br=0;
        	if(IsEmptyQ(Qn) || br==2) return;
        	klient x = FrontQ(Qn);
        	DeQueueQ(Qn);
        	EnQueueQ(x, FQ);
        	br++;
        	brzi(FQ, Qn);
        	br=0;
        }
int main (){
	que *Q = InitQ(Q);
	que *Q1 = InitQ(Q1);
	que *Q2 = InitQ(Q2);
	que *Q3 = InitQ(Q3);
	que *Q4 = InitQ(Q4);
	que *Q5 = InitQ(Q5);
	que *FQ = InitQ(FQ);
	int izbor, brN=0;
	do{
		cout << "-1- Generiranje cetvorki"<<endl << "-2- Dodavanje klijenta"<<endl<< "-3- Odlazak trudnica"<<endl << "-4- Brzi salter"<<endl << "-5- Stanje"<<endl<< "-0- Izlaz"<<endl<<endl;
		cout << "Vas izbor: ";
		cin >> izbor;
		switch(izbor){
            			case 1:
            				system("cls");
            				brN = gener(Q);
            				break;
            			case 2:
            				system("cls");
            				if(!brN){
            					cout << "Prvo morate generirati cetvorke!"<<endl;
            					break;
            				}
            				unos(Q, brN);
            				ispis_jarac(Q);
            				break;
            			case 3:
            				system("cls");
            				izlaz_trudnice(Q);
            				vrati(Q);
            				if(IsEmptyQ(Q)){
            					cout << "Red je prazan!"<<endl;
            					break;
            				}
            				cout << "Stanje u redu"<<endl;
            				ispis_red(Q);
            				vrati(Q);
            				break;
            			case 4:
            				system("cls");
            				rasporedi(Q, Q1, Q2, Q3, Q4, Q5, FQ);
            				sortiraj(Q5);
            				brzi(FQ, Q5);
            				sortiraj(Q4);
            				brzi(FQ, Q4);
            				sortiraj(Q3);
            				brzi(FQ, Q3);
            				sortiraj(Q2);
            				brzi(FQ, Q2);
            				sortiraj(Q1);
            				brzi(FQ, Q1);
            				sortiraj(FQ);
            				cout << "Brzi salter je kreiran!"<<endl << "Stanje u redovima"<<endl;
            				if(!IsEmptyQ(FQ)){
            					cout << "Brzi red "<<endl;
            					ispis_red(FQ);
            				}
            				if(!IsEmptyQ(Q1)){
            					cout << "red 1.- Predaja/Preuzimanje posiljke"<<endl;
            					ispis_red(Q1);
            				}
            				if(!IsEmptyQ(Q2)){
            					cout << "red 2.- Placanje racuna"<<endl;
            					ispis_red(Q2);
            				}
            				if(!IsEmptyQ(Q3)){
            					cout << "red 3.- Uplata lutrije"<<endl;
            					ispis_red(Q3);
            				}
            				if(!IsEmptyQ(Q4)){
            					cout << "red 4.- Western Union"<<endl;
            					ispis_red(Q4);;
            				}
            				if(!IsEmptyQ(Q5)){
            					cout << "red 5.- Evotv"<<endl;
            					ispis_red(Q5);
            				} break;
            			case 5:
            				system("cls");
            				if(IsEmptyQ(Q)){
            					cout << "Red je prazan..."<<endl;
            					break;
            				}
            				cout << "Stanje u redu..."<<endl;
            				ispis_red(Q);
            				vrati(Q);
            				break;
            			case 0: break;
            			default: cout << "Pogresan unos!"<<endl;
		}
	}while(izbor!=0);
	return 0;
}
