#ifndef TELEFONSZAM_H
#define TELEFONSZAM_H
#include "string.h"
#include <fstream>

/**

\file telefonszam.h
A Telefonszam osztály deklarációja
*/

class Telefonszam {
String munkahelyi; ///< Munkahelyi telefonszám
String privat; ///< Privát telefonszám
public:
/// konstruktor
Telefonszam(String p="", String m="-") : munkahelyi(m), privat(p) {}

/// másoló konstruktor
Telefonszam(const Telefonszam& rhs): munkahelyi(rhs.munkahelyi), privat(rhs.privat) {}

/// Helyesség vizsgálata
/// @return ha minden adat formátuma jó, igaz, egyébként hamis
bool correct() {
    return munkahelyi.isPhone() && privat.isPhone();
}

/// Értékadó operátor overload
/// @param rhs jobb oldali operandus, amivel egyenlővé tesszük
/// @return az új, megváltozott telefonszám
Telefonszam& operator=(const Telefonszam& rhs) {
    // adatokat egyenlővé tesszük
    munkahelyi = rhs.munkahelyi;
    privat = rhs.privat;
    return *this; // visszatérünk a megváltozott telefonszámmal
}

/// Egyenlőség operátor
/// @param rhs a jobb oldali operandus, amivel összehasonlítunk
/// @return igaz, ha minden adatuk egyenlő, hamis, ha nem
bool operator==(const Telefonszam& rhs) {
    return (munkahelyi == rhs.munkahelyi) && (privat == rhs.privat);
}

/// Munkahelyi telefonszám lekérdezése
/// @return Munkahelyi telefonszám
String getMunkahelyi() const { return munkahelyi; }

/// Privát telefonszám lekérdezése
/// @return Privát telefonszám
String getPrivat() const { return privat; }

/// Kiírás fájlba, tabulátorral elválasztva
/// @param of a fájl, amibe kiírunk
void kiir(std::ofstream& of) const { of << privat << '\t' << munkahelyi; }

/// Destruktor
~Telefonszam() {}
};


#endif // TELEFONSZAM_H
