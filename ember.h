#ifndef EMBER_H
#define EMBER_H
#include "cim.h"
#include "nev.h"
#include "telefonszam.h"
#include <iomanip>
#include <fstream>
/**

    \file ember.h
    Az Elem osztály deklarációja
*/

class Elem {
Nev sajatNev; ///< Ember neve
Cim sajatCim; ///< Ember címe
Telefonszam sajatSzam; ///< Ember telefonszámai
public:

/// Ember nevének lekérdezése
/// @return Ember neve
Nev getNev() const { return sajatNev; }

/// Ember címének lekérdezése
/// @return Ember címe
Cim getCim() const { return sajatCim; }

/// Ember telefonszámainak lekérdezése
/// @return Ember telefonszámai
Telefonszam getSzam() const { return sajatSzam; }

/// Alapértelmezett konstruktor
Elem() : sajatNev(), sajatCim(), sajatSzam() {}

/// Konstruktor
/// @param n Ember neve
/// @param c Ember címe
/// @param sz Ember telefonszámai
Elem(Nev& n, Cim& c, Telefonszam& sz) : sajatNev(n), sajatCim(c), sajatSzam(sz) {}

/// Konstruktor
/// @param vn Vezetéknév
/// @param kn Keresztnév
/// @param p Privát telefonszám
/// @param m Munkahelyi telefonszám
/// @param isz Irányítószám
/// @param v Város
/// @param u Utca
/// @param hsz Házszám
Elem(String vn, String kn, String p, String m, String isz, String v, String u, String hsz)
    : sajatNev(vn, kn), sajatCim(isz, v, u, hsz), sajatSzam(p, m) {}

/// Másoló konstruktor
Elem(const Elem& rhs) : sajatNev(rhs.sajatNev), sajatCim(rhs.sajatCim), sajatSzam(rhs.sajatSzam) {}

/// Értékadó operátor overload
/// @param rhs Jobb oldali operandus, amivel egyenlővé tesszük
/// @return Az új, megváltozott Elem objektum
Elem& operator=(const Elem& rhs) {
    sajatNev = rhs.sajatNev;
    sajatCim = rhs.sajatCim;
    sajatSzam = rhs.sajatSzam;
    return *this;
}

/// Kiírás fájlba, tabulátorral elválasztva
/// @param of A fájl, amibe kiírunk
void kiir(std::ofstream& of) const {
    sajatNev.kiir(of);
    of << '\t';
    sajatSzam.kiir(of);
    of << '\t';
    sajatCim.kiir(of);
}

/// Egyenlőség operátor egy Nev objektummal való összehasonlításhoz (kereséshez kell)
/// @param n A Nev objektum, amivel összehasonlítunk
/// @return Igaz, ha az Elem neve egyezik a paraméterként kapott Nev objektummal, egyébként hamis
bool operator==(const Nev& n) {
    return sajatNev == n;
}

/// Egyenlőség operátor egy Telefonszam objektummal való összehasonlításhoz (kereséshez kell)
/// @param t A Telefonszam objektum, amivel összehasonlítunk
/// @return Igaz, ha az Elem telefonszámai egyeznek a paraméterként kapott Telefonszam objektummal, egyébként hamis
bool operator==(const Telefonszam& t) {
    return sajatSzam == t;
}

/// Egyenlőség operátor egy Elem objektummal való összehasonlításhoz
/// @param e Az Elem objektum, amivel összehasonlítunk
/// @return Igaz, ha az Elem objektum minden adattagja megegyezik a paraméterként kapott Elem objektummal, egyébként hamis
bool operator==(const Elem& e) {
    return (sajatSzam == e.sajatSzam) && (sajatCim == e.sajatCim) && (sajatNev == e.sajatNev);
}

/// Nem egyenlőség operátor egy Elem objektummal való összehasonlításhoz
/// @param e Az Elem objektum, amivel összehasonlítunk
/// \@eturn Igaz, ha az Elem objektum nem egyezik meg a paraméterként kapott Elem objektummal, egyébként hamis
bool operator!=(const Elem& e) {
    return !(*this == e);
}

/// Kiírás az output stream-re, táblázatos formában
/// @param os Az output stream, ahova kiírunk (alapértelmezett: std::cout)
void kiir(std::ostream& os = std::cout) const {
    os << std::setw(8) << std::left << sajatNev.getVezetek() << "  |  "
        << std::setw(16) << std::left << sajatNev.getKereszt() << "  |  "
        << std::setw(12) << std::left << sajatSzam.getPrivat() << "  |  "
        << std::setw(12) << std::left << sajatSzam.getMunkahelyi() << "  |  "
        << std::setw(4) << std::left << sajatCim.getIsz() << "  |  "
        << std::setw(16) << std::left << sajatCim.getVaros() << "  |  "
        << std::setw(18) << std::left << sajatCim.getUtca() << "  |  "
        << std::setw(4) << std::left << sajatCim.getHazszam() << std::endl;
}

/// Destruktor
~Elem() {}
};



#endif // EMBER_H
