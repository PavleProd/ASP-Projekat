//
// Created by pavle on 07-Dec-21.
//

#ifndef PROGRAMI_CVOR_H
#define PROGRAMI_CVOR_H

#include <iostream>
#include <vector>

using namespace std;


class Cvor {
private:
    static int ukupanID;

    struct Podaci {
        string tekst;
        int id;
        int nivo;

        Podaci(string tekst_, int nivo_) : tekst(move(tekst_)), nivo(nivo_) {
            id = ++ukupanID;
        }
    };

    Podaci *podaci;

public:
    vector<pair<int, Cvor *>> potomci;
    Cvor(const string &tekst, int nivo) {
        podaci = new Podaci(tekst, nivo);
    }
    Cvor(const Cvor &cvor) = delete;
    Cvor& operator =(const Cvor &cvor) = delete;

    int getID() const { return podaci->id; }
    string tekst() const { return podaci->tekst; }

    void dodajPotomka(const string &tekst);

    void sortirajStablo();
    void obrisiStablo();
    Cvor* nadjiPotomka(int id);
    Cvor* nadjiOcaPotomka(int id);


    friend ostream& operator <<(ostream& os, Cvor &cvor);
};




#endif //PROGRAMI_CVOR_H
