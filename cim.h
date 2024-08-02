#ifndef CIM_H
#define CIM_H
#include "string.h"
#include <iostream>
#include <fstream>
/**
 * \file cim.h
 *
 * A cím osztály deklarációja és megvalósítása
 */


class Cim {
    String iranyitoszam; ///< Irányítószám
    String varos; ///< Város
    String utca; ///< Utca
    String hazszam; ///< Házszám
public:
    /// Paraméter nélkül is hívható konstruktor
    /// @param isz Irányítószám
    /// @param v Város
    /// @param u Utca
    /// @param hsz Házszám
    Cim(String isz="", String v="", String u="", String hsz="") : iranyitoszam(isz), varos(v), utca(u), hazszam(hsz) {}

    /// Másoló konstruktor
    /// @param rhs A jobb oldali operandus, amiből másolunk
    Cim(const Cim& rhs) : iranyitoszam(rhs.iranyitoszam), varos(rhs.varos), utca(rhs.utca), hazszam(rhs.hazszam) {}

    /// Értekadó operátor overload
    /// @param rhs A jobb oldali operandus, amivel egyenlővé teszünk
    /// @return A módosított string
    Cim& operator=(const Cim& rhs) {
        // minden erteket egyenlove tesz rhs azonos tipusu ertekevel
        iranyitoszam = rhs.iranyitoszam;
        varos = rhs.varos;
        utca = rhs.utca;
        hazszam = rhs.hazszam;
        return *this; // visszater a modositott cimmel
    }

    /// Helyesseget vizsgalja,
    /// @return ha mindegyik adat formatuma helyes, igaz, kulonben hamis
    bool correct() {
        return iranyitoszam.isZip()&&varos.isCity()&&utca.isStreet()&&hazszam.isHouse();
    }

    /// Egyenlőség operátor
    /// @param rhs A jobb oldali operandus, amivel összehasonlítunk
    /// @return igaz, ha egyenlőek, hamis, ha nem (minden adatuk egyenlő kell legyen)
    bool operator==(const Cim& rhs) {
        return (iranyitoszam==rhs.iranyitoszam)&&(varos==rhs.varos)&&(utca==rhs.utca)&&(hazszam==rhs.hazszam);
    }

   /// Irányítószám lekérdezése
   /// @return Irányítószám
    String getIsz() const{ return iranyitoszam;}

    /// Város lekérdezése
    /// @return Város
    String getVaros() const {return varos;}

    /// Utca lekérdezése
    /// @return Utca
    String getUtca() const {return utca;}

    /// Házszám lekérdezése
    /// @return Házszám
    String getHazszam() const {return hazszam;}

    /// Kiíras fajlba, tabulátorral elválasztva
    /// @param of A fájl, amibe írunk
    void kiir(std::ofstream& of) const {of << iranyitoszam << '\t' << varos << '\t' << utca << '\t' << hazszam;}

    /// Destruktor
    ~Cim() {}
};


#endif // CIM_H
