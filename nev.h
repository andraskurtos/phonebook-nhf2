#ifndef NEV_H
#define NEV_H
#include <fstream>
#include "string.h"

/**
 * \file nev.h
 *
 * A Nev osztály deklarációja
 */

class Nev {
    String keresztnev; ///< Keresztnév
    String vezeteknev; ///< Vezetéknév
public:
    Nev(String v="", String k="") :keresztnev(k), vezeteknev(v) {} /// konstruktor
    Nev(const Nev& rhs) : keresztnev(rhs.keresztnev), vezeteknev(rhs.vezeteknev) {} /// masolo konstruktor

    /// Helyesség vizsgálata
    /// @return  ha minden adat formatuma jo, igaz, egyebkent hamis
    bool correct() {
        return keresztnev.isName()&&vezeteknev.isName();
    }

    /// Keresztnév lekérdezése
    /// @return Keresztnév
    String getKereszt() const {return keresztnev;}

    /// Vezetéknév lekérdezése
    /// @return Vezetéknév
    String getVezetek() const {return vezeteknev;}

    /// Értekadó operátor overload
    /// @param rhs jobb oldali operandus, amivel egyenlővé teszünk
    /// @return az új, megváltozott név
    Nev& operator=(const Nev& rhs) {
        // adatokat egyenlove tesszuk
        keresztnev = rhs.keresztnev;
        vezeteknev = rhs.vezeteknev;
        return *this; // visszaterunk a megvaltozott nevvel
    }

    /// Egyenlőség operátor
    /// @param rhs a jobb oldali operandus, amivel összehasonlítunk
    /// @return igaz, ha minden adatuk egyenlő, hamis, ha nem
    bool operator==(const Nev& rhs) {
        return (keresztnev==rhs.keresztnev)&&(vezeteknev==rhs.vezeteknev);
    }

    /// Kiíras fájlba, tabulátorral elválasztva
    /// @param of a fájl, amibe kiírunk
    void kiir(std::ofstream&of) const {of << vezeteknev << '\t' << keresztnev;}

    /// Destruktor
    ~Nev() {}
};



#endif // NEV_H
