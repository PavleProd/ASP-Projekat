//
// Created by pavle on 07-Dec-21.
//

#include "Cvor.h"
#include <stack>
#include <algorithm>

int Cvor::ukupanID = 0;

ostream &operator<<(ostream &os, Cvor &cvor) {
    cout << string(cvor.podaci->nivo*2, ' '); // formatiranje prema nivou
    os << cvor.podaci->tekst << " ID:" << cvor.podaci->id;

    return os;
}

void Cvor::dodajPotomka(const string &tekst) {
    if(potomci.size() == 10) {
        cout << "Dodat je maksimalan broj potomaka!\n";
        return;
    }

    potomci.emplace_back(0, new Cvor(tekst, podaci->nivo+1));

}

void Cvor::sortirajStablo() {
    stack<Cvor*> s;

    s.push(this);

    while(!s.empty()) {
        Cvor *cvor = s.top();
        s.pop();

        for(int i = (int)cvor->potomci.size() - 1; i >= 0; i--){
            s.push(cvor->potomci[i].second);
        }

        sort(cvor->potomci.begin(), cvor->potomci.end(), greater<>());
    }


}

void Cvor::obrisiStablo() {
    stack<Cvor *> s;
    s.push(this);

    while(!s.empty()) {
        Cvor *cvor = s.top();
        s.pop();

        for(int i = (int)cvor->potomci.size() - 1; i >= 0; i--) {
            s.push(cvor->potomci[i].second);
        }
        cvor->potomci.clear();

        delete cvor;
    }
}

Cvor *Cvor::nadjiPotomka(int id) {

    stack<Cvor*> s;
    s.push(this);
    while(!s.empty()) {
        Cvor *cvor = s.top();
        s.pop();

        if(cvor->podaci->id == id) {
            return cvor;
        }

        for(int i = (int)cvor->potomci.size() - 1; i >= 0; i--) {
            s.push(cvor->potomci[i].second);
        }
    }

    return nullptr;
}

Cvor *Cvor::nadjiOcaPotomka(int id) {
    stack<Cvor*> s;
    s.push(this);
    while(!s.empty()) {
        Cvor *cvor = s.top();
        s.pop();

        for(int i = (int)cvor->potomci.size() - 1; i >= 0; i--) {
            if(cvor->potomci[i].second->getID() == id) {
                return cvor;
            }
            s.push(cvor->potomci[i].second);
        }
    }

    return nullptr;
}





