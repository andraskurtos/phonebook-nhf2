
#include <iostream>

#include <iomanip>
#ifndef STRING_H
#define STRING_H

/**
 * \file string.h
 *
 * A string osztály deklarációja
 */



/// Eldönti, hogy egy karakter szám-e
/**
    @param a a karakter, amit vizsgálunk
    @return igaz, ha szám, hamis különben
*/

bool isNum(char a);
/// Eldönti, hogy egy karakter betû-e
/**
    @param a a karakter, amit vizsgálunk
    @return igaz, ha betû, hamis különben
*/
bool isLetter(char a);

class String {
    char* data; ///< tarolt karaktersor, lezaro 0-val
    size_t len; ///< hossz, a lezaro 0 nelkul
public:
    /// Hossz lekérdezése
    /// @return hossz
    size_t getLen() const {return len;}

    /// Adat lekérdezése
    /// @return adat, cstringént
    const char* getData() const {return data;}

     /// Default konstruktor
    String();

    /// Konstruktor cstringbõl
    String(const char *str);

     /// Másoló konstruktor
    String(const String& s);

    /// Konstruktor std stringből
    String(const std::string& s);

    /// Destruktor
    ~String() {delete[] data;}

    /// Értékado operátor overload másik Stringre
    /// @param rhs jobb oldali operandus, ezzel tesszük egyenlõvé
    /// @return a megváltoztatott string
    String& operator=(const String& rhs);

    /// Értékadó operátor overload std stringre
    /// @param str jobb oldali operandus, amivel egyenlõvé tesszük
    /// @return a megváltozott string
    String& operator=(const std::string str);

    /// Egyenlõség operátor overload
    /// @param rhs a jobb oldali operandus, amivel vizsgáljuk az egyenlõséget
    /// @return igaz, ha egyenlõ, hamis, ha nem
    bool operator==(const String& rhs);

    /// Nem egyenlõ operátor overload
    /// @param rhs a jobb oldali operandus, amivel vizsgáljuk az egyenlõséget
    /// @return igaz, ha nem egyenlõ, hamis, ha nem
    bool operator!=(const String& rhs);

    /// Összeadó operátor másik stringgel
    /// @param rhs a jobb oldali operandus, amivel összeadjuk
    /// @return az új string a kettõ összegébõl
    String operator+(const String& rhs) const;

    /// Eldönti, név formátumú-e? (betű, space, pont, kötõjel lehet benne)
    /// @return igaz, ha név formátumú, hamis, ha nem
    bool isName();

    /// Eldönti, telefonszám formátumú-e? (+36-al kezdõdik, 20-al, 30-al vagy 70-el kezdõdik, és 12 karakterbõl áll)
    /// @return igaz, ha telefonszám formátumú, hamis, ha nem
    bool isPhone();

    /// Eldönti, irányítószám-e? (4 karakterbõl áll, és csak szám)
    /// @return igaz, ha irányítószám formátumú, hamis, ha nem
    bool isZip();

    /// Eldönti, város-e? (csak betû lehet benne, semmi más)
    /// @return igaz, ha város formátumú, hamis, ha nem
    bool isCity();

    /// Eldönti, utca-e? (lehet benne betû, szám, pont, kötõjel, space)
    /// @return igaz, ha utca formátumú, hamis, ha nem
    bool isStreet();

    /// Eldönti, házszám-e? (lehet benne szám, betû, space, /-jel, kötõjelÖ
    /// @return igaz, ha házszám formátumú, hamis, ha nem
    bool isHouse();



};
/// inserter operator overload
std::ostream& operator<<(std::ostream& os, const String& s);



#endif // STRING_H
