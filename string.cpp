#include "string.h"
#include <iostream>
#include "memtrace.h"
#include <cstring>
/**
 * \file string.cpp
 *
 * A string osztály megvalósítása
 */


// szam-e?
bool isNum(char a) {
    return (a>='0')&&(a<='9');
}

// betu-e?
bool isLetter(char a) {
    return ((a>='a')&&(a<='z'))||((a>='A')&&(a<='Z'));
}

// nev-e?
// visszateresi ertek: igaz, ha jo formatumu, hamis ha nem
bool String::isName() {
    if (!isLetter(data[0])) return false; // az első karakter mindig betű
    for(size_t i=0; i<len; i++) {
            // utana lehet -, space, . , vagy betu (Dr. Kurtos-Kovacs Andras)
        if( (!isLetter(data[i]))&&(data[i] != '-')&&(data[i] !=' ')&&(data[i]!='.') ) return false;
    }
    return true;
}

// telefonszám-e?
// visszatérési érték: igaz, ha jó formátumú, hamis ha nem
bool String::isPhone() {
    // telefonszám 12 karakterbõl áll, ha nem ennyi, rossz formátum
    if (len!=12) return false;
    // telefonszám +-al kezdõdik, utána 36, majd 20,30,vagy 70, ha nem ilyen, rossz
    if ((data[0]!='+') || (data[1]!='3') || (data[2]!='6') || ( ((data[3]!='2')&&(data[3]!='3'))&&(data[3]!='7') ) || (data[4] != '0')) return false;
    // a többi karakter is szám kell legyen
    for (size_t i=5; i<len;i++) {
        if(!isNum(data[i])) return false;
    }
    return true;
}

// irányítószám-e?
// visszatérési érték: igaz, ha jó formátumú, hamis ha nem
bool String::isZip() {
    // irányítószám hossza 4
    if (len!=4) return false;
    // csak szám lehet benne
    for(size_t i=0;i<len;i++) {
        if(!isNum(data[i])) return false;
    }
    return true;
}

// város-e?
// visszatérési érték: igaz, ha jó formátumú, hamis ha nem
bool String::isCity() {
    // város csak betûbõl áll, semmi más
    for (size_t i=0; i<len; i++) {
        if(!isLetter(data[i])) return false;
    }
    return true;
}

// utca-e?
// visszatérési érték: igaz, ha jó formátumú, hamis ha nem
bool String::isStreet() {
    // utcában betûn kívûl lehet space, pont,kötõjel vagy akár szám is (42.utca)
    for(size_t i=0; i<len;i++) {
        if (  !isLetter(data[i])&&!isNum(data[i])&&(data[i]!=' ')&&(data[i]!='.')&&(data[i]!='-') ) return false;
    }
    return true;
}

// házszám-e?
// visszatérési érték: igaz, ha jó formátumú, hamis ha nem
bool String::isHouse() {
    // házszámban lehet betû, /-jel, space, pont és kötõjel
    if( !isNum(data[0])) return false; // első karakter mindig szám
    for (size_t i=0;i<len;i++) {
        if( !isLetter(data[i]) && !isNum(data[i]) && (data[i]!='/') && (data[i] !=' ') && (data[i] != '.') && (data[i] != '-') ) return false;
    }
    return true;
}



// default konstruktor, ami ures stringet hoz letre
String::String() :len(0) {
    // foglalas
    data = new char[1];
    // lezaro 0
    data[0] = '\0';

}

// konstruktor std stringbol
String::String(const std::string& s) :data(new char[s.size()+1]), len(s.size()) {
    // meret egyenlo s meretevel, data-t lefoglaljuk, majd atmasoljuk
    std::strcpy(data,s.c_str()); // atmasolja az adatot
}

// konstruktor cstringbol, hasonloan
String::String(const char* str) {
    len = strlen(str); // hossz masolasa
    data = new char[len+1]; // helyfoglalas
    strcpy(data, str); // adat masolasa
}

// masolo konstruktor, szinten hasonloan
String::String(const String& s) {
    len = s.len;
    data = new char[len+1];
    strcpy(data,s.data);
}

// ertekado operator stringgel
String& String::operator=(const String& rhs) {
    if (this!=&rhs) { // nem szabad masolni, ha ugyanaz a ket string
        delete[] data; // data felszabaditasa
        len = rhs.len; // uj meret
        data = new char[len+1]; // uj  data
        strcpy(data,rhs.data); // adat atmasolasa
    }
    return *this; // visszaterunk a megvaltozott stringgel
}

// ertekado operator std stringgel, hasonloan
String& String::operator=(const std::string str) {
    delete[] data;
    len = str.size();
    data = new char[len+1];
    strcpy(data, str.c_str());
    return *this;
}

// egyenloseg operator masik stringgel
bool String::operator==(const String& rhs) {
    if(len!=rhs.len) return false; // ha hosszuk nem ugyanakkora, rossz
    for(size_t i=0;i<len;i++)
        if(data[i]!=rhs.data[i]) // ha barmelyik karakter nem ugyanaz, rossz
            return false;
    return true; // egyebkent jo
}

// nem egyenlo operator
bool String::operator!=(const String& rhs) {
    return !(*this==rhs); // igaz, ha az egyenloseg hamis
}

// osszeado operator masik stringgel
String String::operator+(const String& rhs) const {
    String res; // uj string az eredmenynek
    res.len = len + rhs.len; // hossza a ket string hosszanak osszege
    delete[] res.data; // ki kell torolni az adatat eloszor
    res.data = new char[len+1]; // lefoglaljuk az ujat
    strcpy(res.data, data); // atmasoljuk az adatokat
    strcat(res.data,rhs.data); // hozzafuzzuk rhs adatat
    return res; // visszaterunk az eredmennyel
}


// inserter operator
std::ostream& operator<<(std::ostream& os, const String& s) {
    os<< s.getData(); // az os-be inserteljuk a stringet cstringkent
    return os; // visszaterunk os-el
}


