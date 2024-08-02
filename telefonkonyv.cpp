#include "memtrace.h"
#include <iostream>
#include "telefonkonyv.h"

// beolvas egy sort, fajlbol vagy standard bemenetrol
    bool Telefonkonyv::beolvas(std::istream& is) {
        std::string line;
        getline(is,line); // eloszor beolvas egy sort
        std::stringstream ss(line); // stringstream a sorbol
        std::string datas[8]; // ide menti a tördelt adatokat
        for (int i=0; i<7; i++) {
            getline(ss,datas[i],'\t'); // a sort tabulátoronként széttördeli, stringstreambol beolvasassal
            if (datas[i].empty()) return false; // ha valamelyik adat ures, akkor hamis ertekkel ter vissza
        }
        getline(ss, datas[7],'\r'); // az utolso adatot is beolvassa
        if(datas[7].empty()) return false;
        // megvizsgalja az adatok formatumat
        if( !String(datas[0]).isName()) throw "Helytelen formatum: Vezeteknev";
        if(!String(datas[1]).isName()) throw "Helytelen formatum: Keresztnev";
        if(!String(datas[2]).isPhone()) throw "Helytelen formatum: Privat Szam";
        if(!String(datas[3]).isPhone()) throw "Helytelen formatum: Munkahelyi Szam";
        if(!String(datas[4]).isZip()) throw "Helytelen formatum: Iranyitoszam";
        if(!String(datas[5]).isCity()) throw "Helytelen formatum: Varos";
        if(!String(datas[6]).isStreet()) throw "Helytelen formatum: Utca";
        if(!String(datas[7]).isHouse()) throw "Helytelen formatum: Hazszam";
        // hozzaadja az elemet a konyvhoz, ha hibat dob, tovabbdobja
        try {addElem(Elem(datas[0],datas[1],datas[2],datas[3],datas[4],datas[5],datas[6],datas[7]));} catch (const char* err) {throw err;}
        return true; // ha sikerul az adatot beolvasni, igazzal ter vissza
    }

    // megnyit es beolvassa egy fajlnak minden sorat
    void Telefonkonyv::beolvas(const char* filename) {
        std::ifstream readfile(filename); // megnyitja a fajlt
        if (!readfile.is_open() || !readfile) throw "nem sikerult megnyitni a fajlt"; // kivetel, ha nem sikerult megnyitni a fajlt
        try { while (beolvas(readfile)) ; // while looppal beolvassa a fajlt, pont akkor fog megallni, mikor vege van a fajlnak
        } catch (const char* err) {throw err;} // a hibat dob, tovabbdobjuk

    }


    // kiiras, fajlba
    void Telefonkonyv::kiir(const char* filename) {
        // minden elemet kiir fajlba
        std::ofstream of(filename); // megnyitja a fajlt
        if (!of.is_open() || !of) throw "nem sikerult megnyitni a fajlt!"; // kivetel, ha nem sikerul megnyitni
        for (size_t i=0; i<size();i++) {
            (*this)[i].kiir(of); // minden adatot kiir
            of << std::endl; // ir egy sortorest
        }
    }

    // kiiras szepen, standard kimenetre
    void Telefonkonyv::kiir(std::ostream&os) {
        for (size_t i=0;i<size();i++) {
            (*this)[i].kiir(os); // a szep kiiro fuggvenyt hasznalja a standard kimenetre
        }
 }


    void Telefonkonyv::clear() {
        if (size()==0) throw "mar ures a lista!";
        size_t i = size()-1;
        try {while (size()!= 0) {
            removeElem(i);
            i--;
        }} catch (const char* err) {throw "clear nem sikerult";}
    }
