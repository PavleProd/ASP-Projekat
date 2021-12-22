#include <iostream>
#include <stack>
#include <queue>
#include "Cvor.h"

using namespace std;

void ispisiMeni() {
    cout << "MENI:\n"
            << "0. Napravi praznu strukturu\n"
            << "1. Dodaj novo pitanje\n"
            << "2. Dodaj novi odgovor/komentar\n"
            << "3. Nadji pitanje\n"
            << "4. Nadji odgovor\n"
            << "5. Povecaj ocenu odgovora\n"
            << "6. Uredi odgovore po oceni\n"
            << "7. Ispisi sva pitanja\n"
            << "8. Ispisi jedno pitanje i njegove odgovore i komentare\n"
            << "9. Obrisi odgovor\n"
            << "10. Obrisi pitanje\n"
            << "11. Nadji pitanje ciji odgovor ima najvisu ocenu\n"
            << "12. Izlazak iz programa\n";
}

void dodajPitanje(vector<Cvor *> &pitanja) {
    string tekst;
    cout << "Unesite pitanje:";
    cin.ignore();
    getline(cin, tekst);
    pitanja.push_back(new Cvor(tekst, 0));

}

void dodajOdgovor(vector<Cvor*> &pitanja) {

    string tekst;
    int id;
    cout << "Tekst odgovora/komentara:";
    cin.ignore();
    getline(cin, tekst);
    cout << "ID pitanja/odgovora na koji odgovaramo?";
    cin >> id;

    for(Cvor* pitanje : pitanja) {
        Cvor *otac = pitanje->nadjiPotomka(id);
        if(otac) {
            otac->dodajPotomka(tekst);
            return;
        }
    }

    cout << "Nije pronadjeno pitanje/odgovor sa zadatim ID-em!\n";
}

Cvor* nadjiPitanje(vector<Cvor*> &pitanja) {
    int id;
    cout << "ID pitanja?";
    cin >> id;

    for(Cvor *pitanje : pitanja) {
        if(pitanje->getID() == id) {
            return pitanje;
        }
    }

    return nullptr;
}

Cvor* nadjiOdgovor(vector<Cvor*> &pitanja) {

    int id;
    cout << "ID pitanja ciji odgovor trazimo?";
    cin >> id;
    int idOdg;
    cout << "ID odgovora koji trazimo?";
    cin >> idOdg;

    for(Cvor* pitanje : pitanja) {
        if(pitanje->getID() == id) {
            return pitanje->nadjiPotomka(idOdg);
        }
    }

    cout << "Pitanje ciji odgovor trazimo ne postoji!\n";
    return nullptr;
}

void povecajOcenu(vector<Cvor *> &pitanja) {
    int id;
    cout << "ID odgovora?";
    cin >> id;
    int broj;
    cout << "Za koliko se uvecava ocena?";
    cin >> broj;

    if(broj < 0) {
        cout << "Neispravna vrednost za uvecanje ocene!\n";
        return;
    }


    for(Cvor* &pitanje : pitanja) {

        if(pitanje->getID() == id) {
            cout << "Ne moze se povecati ocena pitanja!\n";
            return;
        }

        Cvor *cvor = pitanje->nadjiOcaPotomka(id);
        if(cvor) {
            for(pair<int,Cvor*> &potomak : cvor->potomci) {
                if(potomak.second->getID() == id) {
                    potomak.first += broj;
                    cout << "Nova ocena odgovora je: " << potomak.first << "\n";
                }
            }
            return;
        }
    }

    cout << "Trazeni odgovor ne postoji!\n";
}

void sortirajPitanja(vector <Cvor*> &pitanja) {
    for(Cvor* &pitanje : pitanja) {
        pitanje->sortirajStablo();
    }
}

void ispisPitanja(vector<Cvor *> &pitanja) {
    for(Cvor * pitanje : pitanja) {
        cout << *pitanje << "\n";
    }
}

bool ispisJednogPitanja(vector<Cvor*> &pitanja) {
    int id;
    cout << "ID Pitanja?";
    cin >> id;

    Cvor *koren = nullptr;
    for(Cvor *pitanje : pitanja) {
        if(pitanje->getID() == id) {
            koren = pitanje;
            break;
        }
    }

    if(!koren) return false;

    stack<Cvor *> s;
    s.push(koren);

    while(!s.empty()) {
        Cvor *cvor = s.top();
        s.pop();

        cout << *cvor << "\n"; // ili bilo koja druga obrada

        for(int i = (int)cvor->potomci.size() - 1; i >= 0; i--) {
            s.push(cvor->potomci[i].second);
        }
    }

    return true;

}

void obrisiOdgovor(vector<Cvor*> &pitanja) {
    int id;
    cout << "ID odgovora?";
    cin >> id;

    for(Cvor* pitanje : pitanja) {
       Cvor* cvor = pitanje->nadjiOcaPotomka(id);
       if(cvor) {
           for(int i = 0; i < pitanje->potomci.size(); i++) {
               if(pitanje->potomci[i].second->getID() == id) {
                   pitanje->potomci[i].second->obrisiStablo();
                   pitanje->potomci.erase(pitanje->potomci.begin() + i);
               }
           }
           return;
       }
    }

    cout << "Trazeni odgovor ne postoji!\n";
}

void obrisiPitanje(vector <Cvor*> &pitanja) {
    int id;
    cout << "ID pitanja?";
    cin >> id;

    for(int i = 0; i < pitanja.size(); i++) {
        if(pitanja[i]->getID() == id) {
            pitanja[i]->obrisiStablo();
            pitanja.erase(pitanja.begin() + i);
            return;
        }
    }

    cout << "Trazeno pitanje ne postoji!\n";
}

void pitanjeSaNajvisomOcenom(vector <Cvor*> &pitanja) {
    int najvisaOcena = -1;
    Cvor *pitanje = nullptr;

    for(Cvor* koren : pitanja) {
        stack<Cvor *> s;
        s.push(koren);

        while(!s.empty()) {
            Cvor* cvor = s.top();
            s.pop();

            for(int i = (int)cvor->potomci.size() - 1; i >= 0; i--) {
                s.push(cvor->potomci[i].second);
                if(cvor->potomci[i].first > najvisaOcena) {
                    najvisaOcena = cvor->potomci[i].first;
                    pitanje = koren;
                }
            }
        }
    }

    if(najvisaOcena == -1 ) {
        cout << "Ne postoji nijedan odgovor!\n";
        return;
    }

    cout << "Pitanje sa odgovorom sa najvisom ocenom " << *pitanje << " Ocena: " << najvisaOcena << "\n";
}


int main() {

    vector<Cvor *> pitanja;

    while(true) {

        ispisiMeni();
        int izbor;
        cin >> izbor;

        switch(izbor) {
            case 0:
                for(Cvor * pitanje : pitanja) {
                    pitanje->obrisiStablo();
                }
                pitanja.clear();
                break;
            case 1:
                dodajPitanje(pitanja);
                break;
            case 2:
                dodajOdgovor(pitanja);
                break;
            case 3:
            {
                Cvor *pitanje = nadjiPitanje(pitanja);
                pitanje ? cout << "Adresa na kojoj se nalazi pitanje je: " << pitanje << "\n"
                : cout << "Pitanje ne postoji!\n";
                break;
            }
            case 4:
            {
                Cvor *odgovor = nadjiOdgovor(pitanja);
                odgovor ? cout << "Adresa na kojoj se nalazi odgovor je: " << odgovor << "\n"
                        : cout << "Odgovor ne postoji!\n";
                break;
            }
            case 5:
                povecajOcenu(pitanja);
                break;
            case 6:
                sortirajPitanja(pitanja);
                break;
            case 7:
                ispisPitanja(pitanja);
                break;
            case 8:
                ispisJednogPitanja(pitanja);
                break;
            case 9:
                obrisiOdgovor(pitanja);
                break;
            case 10:
                obrisiPitanje(pitanja);
                break;
            case 11:
                pitanjeSaNajvisomOcenom(pitanja);
                break;
            case 12: return 0;
            default:
                cout << "Pogresan unos!";
                continue;
        }
    }


}