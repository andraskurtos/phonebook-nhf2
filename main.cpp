#include <iostream>
#include "telefonkonyv.h"
#include "memtrace.h"
#include <fstream>
#include "gtest_lite.h"


int main()
{
        // ezen fog dolgozni a menüprogram
        Telefonkonyv a;

        // megpróbáljuk betölteni a mentést, kezeljük az esetleges hibát
        try {a.beolvas("save.txt");} catch (const char* err) {std::cout<<err << std::endl;}

        // ezt fogja kiírni a menü
        String alap("TELEFONKONYV - Kurtos Andras BLDI3I\nirja be a valasztott menupont szamat!\n___________________________________\n1. Adatok kilistazasa\n2. Uj adat felvetele\n3. Adat keresese\n4. Valahanyadik adat eltavolitasa\n5. Mentes\n6. Egesz lista torlese\n7. Mentes visszatoltese\n8. kilepes\n___________________________________\n");
        std::cout << alap << std::endl;

        // ezzel választunk a menüben
        char selector=0;

        // ha true, kilép és futtatja a tesztprogramot
        bool vege = false;

        // beolvassuk a selectort, ez a menüprogram innentől
        while(std::cin>>selector) {
            // selector különböző értékei a menüpontok
            switch (selector) {
                // 1-es eset: lista kiírása
                case '1':
                        // kiírjuk a listát, majd egy sortörést
                        a.kiir();
                        std::cout << std::endl;
                        break;

                // 2-es eset: új adat felvétele
                case '2':
                        std::cout<<"Adja meg az uj adatot, az adattagokat tabulatorral elvalasztva!\nVezeteknev\tKeresztnev\tPrivat szam\tMunkahelyi szam\tIranyitoszam\tVaros\tUtca\tHazszam"<<std::endl;
                        // megpróbáljuk beolvasni az adatot, ha nem sikerül, kezeljük a hibát
                        // ignore-olni kell egy karaktert, mert a cin-ben van még egy newline karakter
                        try {
                            if(!a.beolvas(std::cin.ignore(1,'\n'))) {
                                std::cout << "Hibas formatum!" << std::endl;
                                break;
                            }
                        } catch (const char* err) {
                            std::cout << err << std::endl;
                            break;
                            }

                        // visszajelzés
                        std::cout << "\nAdat felveve!\nModositott telefonkonyv:\n" << std::endl;

                        // kiírjuk az új telefonkönyvet
                        a.kiir();
                        std::cout<< std::endl;
                        break;
                // 3-as eset: keresés
                case '3':

                        {

                        std::cout << "Mi alapjan szeretne keresni?\n1: Telefonszam\n2: Nev" << std::endl;
                        // itt választjuk ki, mi alapján keresünk
                        char selector3 = 0;
                        std::cin >> selector3;
                        // ide mentjük majd a megtalált elemet
                        Elem keresett;
                        try {switch (selector3) {
                            case '1':
                                {
                                std::cout<<"Telefonszam alapu kereses\nAdja meg a privat, majd a munkahelyi szamot tabulatorral elvalasztva!\nPrivatSzam\tMunkahelyiSzam" << std::endl;
                                // egy std stringbe beolvassuk a sort
                                std::string line;
                                getline(std::cin.ignore(1,'\n'),line);
                                std::stringstream ss(line);
                                // tabulátornál széttördeljük a sort
                                std::string t1, t2;
                                getline(ss,t1,'\t');
                                getline(ss,t2,'\n');
                                // megpróbáljuk megkeresni az elemet, ha nem megy, kezeljük a hibát
                                try {keresett = a.keres(Telefonszam(String(t1),String(t2)));} catch (const char* err) {throw err;}
                                }
                                break;
                            case '2':
                                {
                                // ugyanúgy, mint telefonszám alapján
                                std::cout<<"Nev alapu kereses\nAdja meg a vezeteknevet, majd a keresztnevet tabulatorral elvalasztva!\nVezeteknev\tKeresztnev" << std::endl;
                                std::string line;
                                getline(std::cin.ignore(1,'\n'),line);
                                std::stringstream ss(line);
                                std::string v, k;
                                getline(ss,v,'\t');
                                getline(ss,k,'\n');
                                try {keresett = a.keres(Nev(String(v),String(k)));} catch (const char* err) {throw err;}
                                }
                                break;
                            default:
                                std::cout<< "nincs ilyen menupont!" << std::endl;
                                break;
                        }} catch (const char* err) { /* itt kezeljuk a hibat */
                            std::cout << err << std::endl;
                            break;

                        }
                        // ha megtalaltuk, kiirjuk az elemet
                        if (keresett != Elem()) {
                        std::cout << "Megvan!\n";
                        keresett.kiir();

                        // törölhetjük ezután az elemet
                        std::cout << "Szeretne torolni a talalt elemet? (y/n): ";
                        // igen / nem
                        char selector32 = 0;
                        std::cin >> selector32;
                        // ha igen, töröljük, bármi másnál nem
                        if(selector32=='y') try{a.removeElem(keresett);} catch (const char* err) {throw err; break;}
                        }
                        }
                        break;
                // 4-es eset: valahanyadik elem törlése
                case '4':
                        {
                            std::cout << "Hanyadik elemet szeretne torolni? (az elso elem az 1-es): ";
                            // ezt az indexediket fogjuk törölni
                            int idx;
                            std::cin >> idx;
                            // megpróbáljuk törölni, kezeljük az esetleges hibát
                            try { a.removeElem(idx-1); } catch (const char* err) {
                                std::cout << err << std::endl;
                                break;
                            }
                            std::cout << idx << ". elem torolve!" << std::endl;
                        }
                        break;
                // 5-ös eset: adatok mentése fájlba
                case '5':
                        {
                            std::cout << "Adatok mentese a fajlba..." << std::endl;
                            // megpróbáljuk kiírni, esetleges hibát kezeljük
                            try {a.kiir("save.txt");} catch (const char* err) {std::cout << err << std::endl; break;}
                        }
                        break;
                // 6-os eset: egész lista törlése
                case '6':
                        {

                            std::cout << "Biztos, hogy torli az egesz listat? Ezzel elveszik minden mentetlen modositas!! (y/n) ";
                            char selector6 = 0;
                            std::cin >> selector6;
                            // ha igen, töröljük, bármi másra nem
                            if(selector6=='y') {
                                    std::cout << "Egesz lista torlese..." << std::endl;
                                    // megpróbáljuk törölni, esetleges hibát kezeljük
                                    try {a.clear();} catch (const char* err) {std::cout << err << std::endl; break;}
                            }
                        }
                        break;
                // 6-os eset: mentés betöltése
                case '7':
                        {
                            std::cout << "Biztos visszatolti a mentest? Ezzel elveszik minden mentetlen modositas!! (y/n) ";
                            char selector7 = 0;
                            std::cin >> selector7;
                            // ha igen, betöltjük, bármi másra nem
                            if(selector7=='y') {
                                    std::cout << "Mentes visszatoltese..." << std::endl;
                                    // megpróbáljuk kitörölni a telefonkonyvet, hiba esetén kezeljük
                                    if (a.size()>0) {try {a.clear();} catch (const char* err) {std::cout << "betoltott konyv torlese:" << err << std::endl; break;}}
                                    // megpróbáljuk betölteni a mentést, esetleges hibát kezeljük
                                    try {a.beolvas("save.txt");} catch (const char* err) {std::cout << err << std::endl; break;}
                            }
                        }
                        break;
                // 8-as eset: kilépés
                case '8':
                        {

                            std::cout << "Szeretne menteni kilepes elott? Ha nem ment, elvesznek a modositasok!! (y/n) ";
                            char selector8 = 0;
                            std::cin >> selector8;
                            // ha igen, mentünk, egyébként nem
                            if(selector8=='y') {
                                    // megpróbálunk menteni, esetleges hibát kezeljük
                                    try {a.kiir("save.txt");} catch (const char* err) {std::cout << err << std::endl; break;}
                            }
                            // kilépunk ezzel
                            vege = true;
                        }
                        break;
                default:
                        // rossz bemenetre nem csinál semmit a menü
                        std::cout << "Nincs ilyen menupont!" << std::endl;
                        break;
            }
            // ha vége, kilépünk
            if(vege) break;

            // pause, hogy megnézhessük a kiírásokat
            system("pause");
            // képernyő törlése, hogy szebb legyen
            system("cls");

            // instrukciók
            std::cout << alap << std::endl;
            }

        system("cls");
        std::cout << "TESZTPROGRAM:" << std::endl;

        // 1-es teszteset, lista default konstruktora
        TEST(1, Lista konstruktor) {
            Lista<int> l;
            // lista üres kell legyen alapból
            EXPECT_EQ(size_t(0),l.size()) << "Nem ures a lista" << std::endl;

        } ENDM

        // 2-es teszteset, lista addElem függvénye
        TEST(2, Lista addElem) {
            Lista<int> l;
            // megpróbálunk hozzáadni egy elemet, hiba esetén kiírjuk
            try {l.addElem(1);} catch (const char* err) {std::cout << err << std::endl;}
            // megnőtt a mérete?
            EXPECT_EQ(size_t(1),l.size()) << "Nem nott meg a lista merete hozzaadasnal" << std::endl;
            // jot adott hozza?
            EXPECT_EQ(1,l[0]) << "Nem jot adott hozza" << std::endl;
        } ENDM

        // 3-as teszteset, lista assign operátora
        TEST(3, Lista assign) {
            Lista<int> l;
            // hozzáadunk egy elemet
            try {l.addElem(1);} catch (const char* err) {std::cout << err << std::endl;}
            Lista<int> l2;
            // assign
            l2=l;
            // egyenlő a méretük, adatuk?
            EXPECT_EQ(l.size(),l2.size()) << "Nem ugyanakkora az assignolt lista" << std::endl;
            EXPECT_EQ(l[0],l2[0]) << "Nem ugyanaz az adat a 2-ben" << std::endl;
        } ENDM

        // 4-es teszteset, lista egyenlőség operátora
        TEST(4, Lista comp) {
            Lista<int> l;
            // hozzáadunk két elemet
            try {l.addElem(1);} catch (const char* err) {std::cout << err << std::endl;}
            try {l.addElem(2);} catch (const char* err) {std::cout << err << std::endl;}
            Lista<int> l2;
            // assign, már tudjuk, hogy jól működik
            l2=l;
            // egyenlőek?
            EXPECT_TRUE(l2==l) << "nem jo az osszehasonlitas" <<std::endl;
        } ENDM

        // 5-ös teszteset, lista index operátora
        TEST(5, Lista index) {
            Lista<int> l;
            try {l.addElem(1);} catch (const char* err) {std::cout << err << std::endl;}
            try {l.addElem(2);} catch (const char* err) {std::cout << err << std::endl;}

            // jót ad vissza?
            EXPECT_EQ(1,l[0]) << "nem jo az index" << std::endl;

            // dob kivételt?
            EXPECT_THROW(l[40],const char*) << "nem dob kivetelt tul nagy index eseten" << std::endl;
        } ENDM

        // 6-os teszteset: lista removeElem függvénye
        TEST(6, Lista removeElem) {
            Lista<int> l;
            // hozzáadunk elemeket
            for (int i=1;i<5;i++) { try {l.addElem(i);} catch (const char* err) {std::cout << err << std::endl;}}
            // dob kivételt túl nagy indexre?
            EXPECT_THROW(l.removeElem(40),const char*) << "nem dob kivetelt tul nagy index eseten" << std::endl;


            int teszt = l[2];
            int teszt2=l[3];
            // törlés index alapján
            try {l.removeElem(1);} catch (const char* err) {std::cout << err << std::endl;}

            // csökkent a méret? jó elem került a helyére?
            EXPECT_EQ(size_t(3),l.size()) << "lista merete nem csokkent torles utan" << std::endl;
            EXPECT_EQ(teszt,l[1]) <<"nem jo elem kerult a torolt helyere" << std::endl;

            // törlés elem alapján
            try {l.removeElem(teszt);} catch (const char* err) {std::cout << err << std::endl;}

            // csökkent a méret? jó elem került a helyére?
            EXPECT_EQ(size_t(2),l.size()) <<"lista merete nem csokkent torles utan" << std::endl;
            EXPECT_EQ(teszt2,l[1]) << "nem jo elem kerult a torolt helyere" << std::endl;

            for (int i=0;i<2;i++) {try {l.removeElem(0);} catch (const char* err) {std::cout << err << std::endl;}}
            Lista<int> l2;

            // kiürítette a listát?
            EXPECT_EQ(size_t(0),l.size()) << "lista nem lett ures";
            EXPECT_TRUE(l==l2) << "lista nem lett ures";
            // dob kivételt üres listára?
            EXPECT_THROW(l.removeElem(0),const char*) << "nem dob kivetelt, ha ures listat probalunk torolni" << std::endl;
        } ENDM


        // 7-es teszteset: string formátumvizsgálók tesztje
        TEST(7, string vizsgalok) {
            char a = '/';
            char b = '8';
            char c = 'C';

            // isLetter - csak c-re igaz
            EXPECT_FALSE(isLetter(a)) << "nem jo az isLetter" << std::endl;
            EXPECT_FALSE(isLetter(b)) << "nem jo az isLetter" << std::endl;
            EXPECT_TRUE(isLetter(c)) << "nem jo az isLetter" << std::endl;

            // isNum - csak b-re igaz
            EXPECT_FALSE(isNum(a)) << "nem jo az isNum" << std::endl;
            EXPECT_TRUE(isNum(b)) << "nem jo az isNum" << std::endl;
            EXPECT_FALSE(isNum(c))  << "nem jo az isNum" << std::endl;


            String nevJo("Dr. Sajtos-Bucis Aron"); // lehet benne kotojel, space, pont, betu, es az elso karakter mindig betu
            String nevRossz("||||"); // más karakter nem lehet


            EXPECT_TRUE(nevJo.isName()) << "nem jo az isName" << std::endl;
            EXPECT_FALSE(nevRossz.isName()) << "nem jo az isName" << std::endl;


            String szamJo("+36201324567"); // 12 jegyű, +36-al kezdődik, 20-al, 30-al vagy 70-el folytatódik
            String szamRossz("11111");  // ez rossz

            EXPECT_TRUE(szamJo.isPhone()) << "nem jo az isPhone" << std::endl;
            EXPECT_FALSE(szamRossz.isPhone()) << "nem jo az isPhone" << std::endl;


            String iranyitoJo("2461"); // 4 számjegyű, csak szám
            String iranyitoRossz("aa124as"); // nem jó

            EXPECT_TRUE(iranyitoJo.isZip()) << "nem jo az isZip" << std::endl;
            EXPECT_FALSE(iranyitoRossz.isZip()) << "nem jo az isZip" << std::endl;


            String varosJo("Satoraljaujhely"); // csak betű lehet
            String varosRossz("Buda Pest"); // városban csak betű lehet, semmi más
            EXPECT_TRUE(varosJo.isCity()) << "nem jo az isCity" << std::endl;
            EXPECT_FALSE(varosRossz.isCity()) << "nem jo az isCity" << std::endl;


            String utcaJo("bajcsy-zsilinszky utca"); // lehet benne kötőjel, betű, space, pont
            String utcaJo2("47. utca"); // szám is lehet benne
            String utcaRossz("|||||||"); // de más karakter nem

            EXPECT_TRUE(utcaJo.isStreet()) << "nem jo az isStreet" << std::endl;
            EXPECT_TRUE(utcaJo2.isStreet()) << "nem jo az isStreet" << std::endl;
            EXPECT_FALSE(utcaRossz.isStreet()) << "nem jo az isStreet" << std::endl;


            String hazszamJo("50/a-b"); // lehet benne szám, betű, /-jel, vagy kötőjel, az első karakter mindig szám
            String hazszamRossz("___"); // más karakter viszont nem
            EXPECT_TRUE(hazszamJo.isHouse()) << "nem jo az isHouse" << std::endl;
            EXPECT_FALSE(hazszamRossz.isHouse()) << "nem jo az isHouse" << std::endl;

            }ENDM

        // 8-as teszteset: fájlból beolvasás
        TEST(8, fajlbol beolvasas) {
            Telefonkonyv teszt;
            // beolvas
            try {teszt.beolvas("teszt.txt");} catch (const char* err) {std::cout << err << std::endl;}
            // mindent beolvasott?
            EXPECT_EQ(size_t(19),teszt.size()) << "nem lett beolvasva minden adat";
        } ENDM

        // 9-es teszteset: keresés
        TEST(9 , kereses) {
            // keresés név alapján
            Telefonkonyv teszt;
            try {teszt.beolvas("teszt.txt");} catch (const char* err) {std::cout << err << std::endl;}
            Elem keresett1;
            try {keresett1 = teszt.keres(Nev("Kiss","Bence"));} catch (const char* err) {std::cout<<err<<std::endl;}
            // megtalálta?
            EXPECT_TRUE(Elem("Kiss","Bence","+36301829374","+36708192375","8888","Miskolc","Kossuth utca","110")==keresett1) << "Nev szerinti kereses nem jot talalt meg!" << std::endl;
            // keresés szám alapján
            Elem keresett2 = teszt.keres(Telefonszam("+36301293847","+36704278190"));
            // megtalálta?
            EXPECT_TRUE(Elem("Nagy","Andrea","+36301293847","+36704278190","3333","Budapest","Rozsa utca","40")==keresett2) << "Szam szerinti kereses nem jot talalt meg!" << std::endl;

            // név szerinti keresés:

            // kivetelt dob, ha nem létezőre keresünk?
            EXPECT_THROW(teszt.keres(Nev("a","a")),const char*) << "Nev szerinti kereses nem dob kivetelt, ha nem letezore keresunk" << std::endl;
            // ha rossz formátumúval keresünk?
            EXPECT_THROW(teszt.keres(Nev("a_","a_")),const char*) << "Nev szerinti kereses nem dob kivetelt, ha rossz formatumuval keresunk" << std::endl;
            // kivételt dob, ha több ilyen elem van?
            EXPECT_THROW(teszt.keres(Nev("Kovacs","Erika")),const char*) << "Nev szerinti kereses nem dob kivetelt, ha tobb van a keresett elembol" << std::endl;

            // szám szerinti keresés?

            // kivételt dob, ha rossz formátumúval keresünk?
            EXPECT_THROW(teszt.keres(Telefonszam("a","a")),const char*)<< "Szam szerinti kereses nem dob kivetelt, ha rossz formatumuval keresunk" << std::endl;
            // ha nem létezőre keresünk?
            EXPECT_THROW(teszt.keres(Telefonszam("+36201111111","+36301111111")),const char*)<< "Szam szerinti kereses nem dob kivetelt, ha nem letezore keresunk" << std::endl;
            // kivetelt dob, ha tobb ilyen elem van?
            EXPECT_THROW(teszt.keres(Telefonszam("+36302098765", "+36703091827")),const char*) << "Szam szerinti kereses nem dob kivetelt, ha tobb van a keresett elembol" << std::endl;
        } ENDM

        // 10-es teszteset: telefonkönyv clear függvénye
        TEST (10,clear) {
            Telefonkonyv teszt;
            // feltöltjük a listát
            try {teszt.beolvas("teszt.txt");} catch (const char* err) {std::cout << err << std::endl;}
            try {teszt.clear();} catch (const char* err) {std::cout << err << std::endl;}
            EXPECT_EQ(size_t(0),teszt.size()) << "nem sikerult a clear" << std::endl;
            EXPECT_THROW(teszt.clear(), const char*) << "nem dob kivetelt, ha ures listat probalunk torolni" << std::endl;
        } ENDM

        // 11-es teszteset: telefonkönyv mentése
        TEST (11 ,mentes) {
            Telefonkonyv teszt;
            // feltöltjük a könyvet
            try {teszt.beolvas("teszt.txt");} catch (const char* err) {std::cout << err << std::endl;}
            // kiírjuk egy másik fájlba
            try {teszt.kiir("teszt2.txt");} catch (const char* err) {std::cout << err << std::endl;}

            Telefonkonyv teszt2;
            // beolvassuk a fájlt egy másik könyvbe, tudjuk, hogy a beolvasás jól működik
            try {teszt2.beolvas("teszt2.txt");} catch (const char* err) {std::cout << err << std::endl;}
            // ha egyenlők, jó
            EXPECT_TRUE(teszt==teszt2) << "A mentes nem jol mentett a fajlba" << std::endl;
        } ENDM

    return 0;




}
