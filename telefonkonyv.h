#ifndef TELEFONKONYV_H
#define TELEFONKONYV_H

#include "lista.hpp"  // Lista fejléc fájl inklúziója
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>


class Telefonkonyv : public Lista<Elem> {
public:
    /// Beolvassa az adatokat egy bemeneti adatfolyamból
    /// @param is Az input adatfolyam, alapértelmezett értéke a std::cin
    /// @return true, ha sikeresen beolvasta az adatokat, különben false
    /// @throws const char* kivételt, ha bármelyik adat nem jó formátumú
    bool beolvas(std::istream& is = std::cin);

    /// Beolvassa az adatokat egy fájlból
    /// @param filename A fájlnév, amelybõl beolvassa az adatokat
    /// @throws const char* kivételt, ha nem sikerül megnyitni a fájlt, vagy bármely adat rossz formátumú
    void beolvas(const char* filename);

    /// Kiírja az adatokat egy fájlba
    /// @param filename A fájlnév, amelybe kiírja az adatokat
    /// @throws const char* kivételt, ha nem sikerül megnyitni a fájlt
    void kiir(const char* filename);

    /// Kiírja az adatokat a standard kimenetre
    /// @param os A kimeneti adatfolyam, alapértelmezett értéke a std::cout
    void kiir(std::ostream& os = std::cout);

    /// Keresés egy elem alapján
    /// @tparam U A keresendõ elem típusa
    /// @param a A keresendõ elem
    /// @return Az elsõ találat a keresett elemre, vagy kivételt dob, ha nincs találat
    /// @throws const char* kivételt, ha a keresési feltétel hibás formátumú, ha több olyan elem van, mint a keresett, vagy ha egy sincs
    template <typename U>
    Elem keres(U a) {
        if (!a.correct()) throw "rossz formatumu alapjan probal keresni!";
        int idx = -1;
        for (size_t i = 0; i < size(); i++) {
            if ((*this)[i] == a) {
                if (idx != -1) throw "tobb ilyen van!";
                idx = i;
            }
        }
        if (idx == -1) throw "nincs ilyen!";
        return (*this)[idx];
    }

    /// Törli az összes elemet a telefonkönyvből
    /// @throws const char* kivételt, ha nem sikerül törölni az összes elemet, vagy ha mar alapbol ures a lista
    void clear();

    /// Destruktor
    ~Telefonkonyv() {}
};

#endif // TELEFONKONYV_H
