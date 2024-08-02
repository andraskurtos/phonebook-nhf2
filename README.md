Telefonkönyv - Programozás Alapjai 2 Nagyházi

this program was created as an assignment in my second semester of university.
it is a simple phonebook application, created in C++.
included are tests using a light GTest framework provided to us by the university for the assignment.

**disclaimer**
no build file included in this repo, for documentation purpuses only.

below is the original user documentation written in hungarian:




LEÍRÁS
================================================================
A program egy **telefonkönyv** applikációt valósít meg. Képes dinamikusan tárolni adatsorokat, amelyek **neveket** és a hozzájuk tartozó **címet**, **munkahelyi** és **privát telefonszámot** tartalmazzák. Ezen adatokat képes egy külső txt fájlba kiírni, vagy onnan visszaolvasni. A programban felvehetünk új adatokat, törölhetjük őket, kilistázhatjuk őket, valamint kereshetünk név és telefonszám alapján.
________________________________________________________________


MENÜPROGRAM
================================================
A menüprogrammal kezelhetjük a programot. Megnyitás után egy menüfelület fogad minket, ahol a standard bemenetre írt számokkal navigálhatunk.
- *1-es menüpont*
  Az *1-es menüponttal* **kiirathatjuk** a jelenleg betöltött telefonkönyv minden adatát a standard kimenetre
- *2-es menüpont*
  A *2-es menüponttal* **új adatot vehetünk fel a telefonkönyvbe.** Kiválasztás után *tabulátorokkal elválasztva* adhatjuk meg az adatokat (Vezetéknév, Keresztnév, Privát telefonszám, Munkahelyi telefonszám, Irányítószám, Város, Utca, Házszám). Az adatfelvételhez szükséges, hogy **minden adatot helyes formátumban adjunk meg**, ha ezt nem teljesítjük, hibát kapunk. Az adatok helyes formátuma:
    + A *vezetéknév, keresztnév* első karaktere mindenképpen betű kell legyen. A többi karakter lehet további betű, vagy '.', '-', vagy space. Csak 1 betűt kötünk meg, mert így tárolhatunk vezetéknevet rövidítetten is (pl: K. Gábor). A '.' karakterre a prefixumok miatt is szükség van (pl: Dr. Kovács Gábor). A '-' karakterre az összetett vezetéknevek miatt van szükség (pl: Kovács-Kurtos Gábor), a szőközre pedig azért, ha valakinek több keresztneve van. A kötőjel, pont és szóköz bárhol lehet a névben, az első karakteren kívűl.
    + A *telefonszám* minden esetben 12 karakterből áll, '+36'-al kezdődik, majd '20'-al, '30'-al, vagy '70'-el folytatódik. Ezután további 7 számjegy következik,
    + Az *irányítószám* 4 számjegyből áll, és csak számokból állhat
    + A *város* csakis betűből állhat, szóköz sem lehet benne (magyar helyesírás szerint így helyes, egyetlen magyar városban sincs szóköz)
    + Az *utcában* lehet betű, szám, '.', '-' és szóköz. (szám mert pl: 413. utca, '.' ugyanezért, '-' pl Bajcsy-Zsilinszky utca)
    + A *házszám* első karaktere mindenképpen szám, ezután következhet '.', '/' vagy betű
- *3-as menüpont*
  A *3-as menüpontban* kereshetünk a telefonkönyvben név vagy telefonszám szerint. A menüpontot választva újból választanunk kell, hogy telefonszám, vagy név alapján óhajtunk-e keresni. A kiválasztott menüpont számát beírva választhatunk. Ezután tabulátorokkal elválasztva adhatjuk meg a szükséges adatokat (vezetéknév, keresztnév // munkahelyi, privát szám). Ha rossz formátumban adjuk meg ezeket, hibát fogunk kapni. Egyébként, ha csak egy ilyen elem van a listában, megtalálja és kiírja azt. Ha több ilyen van, vagy nincs ilyen elem, hibát kapunk. Ha megtalálta az elemet, kitörölhetjük azt. A 'y' (mint 'yes') karakter beírásával elfogadjuk a törlést, az 'n'-el elutasítjuk.
- *4-es menüpont*
  A *4-es menüpontban* index szerint törölhetünk egy elemet. Fontos megjegyezni, hogy az első elem indexe 1, azaz nem 0-tól keződik az indexelés.
- *5-ös menüpont*
  Az *5-ös menüponttal* menthetünk a mentés fájlba
- *6-os menüpont*
  A *6-os menüponttal* törölhetjük a lista minden adatát. A menüpont választása után megerősítésképpen a már fentebb leírt y/n rendszerrel meg kell erősítenünk, hogy tényleg törölni szeretnénk a listát, így kisebb eséllyel töröljük véletlenül az egészet.
- *7-es menüpont*
  A *7-es menüponttal* visszatölthetjük a mentésfájl adatait a telefonkönyvbe. A menüpont választása után megerősítésképpen a már fentebb leírt y/n rendszerrel meg kell erősítenünk, hogy tényleg be szeretnénk tölteni az adatokat, mert így a nem mentett adatok elvesznek.
- *8-as menüpont*
  A *8-as menüponttal* kiléphetünk a programból. A menüpont választásakor még lehetőségünk van menteni, erről a fentebb leírt y/n rendszerrel dönthetünk. Kilépés után fut le a tesztprogram.

________________________________________________________________

TESZTPROGRAM
================================================
A tesztprogram 11 tesztesetből áll, és átfogóan vizsgálja a program különböző működéseit.
- *1-es teszteset*:
  Az 1-es tesztesetben a lista **paraméter nélküli konstruktorját** vizsgáljuk, megnézzük, üres listát hoz-e létre.
- *2-es teszteset*:
  A 2-es tesztesetben a lista **addElem** függvényét teszteljük. Megnézzük, elem hozzáadásánál megnő-e a lista mérete, és hozzáadódik-e az elem.
- *3-as teszteset*:
  A 3-as tesztesetben a lista **értékadó operátorát** teszteljük, megnézzük, helyesen másolja-e át az adatokat egy listából a másikba.
- *4-es teszteset*:
  A 4-es tesztesetben a lista **== operátorát** vizsgáljuk, megnézzük, jó logikai értékkel tér-e vissza.
- *5-ös teszteset:*:
  Az 5-ös tesztesetben a lista **[] operátorát** vizsgáljuk, megnézzük, jó elemmel tér-e vissza, és hogy dob-e kivételt túl nagy index esetén.
- *6-os teszteset*:
  A 6-os tesztesetben a lista **removeElem** függvényét vizsgáljuk. Megnézzük, kivételt dob-e túl nagy indexre. Mind az index alapú, mind az elem alapú törlésre megnézzük, csökken-e a lista mérete, jó elem kerül-e a törölt elem helyére, és hogy dob-e kivételt, ha üres listából törölnénk.
- *7-es teszteset*:
  A 7-es tesztesetben a stringvizsgáló függvények helyes működését teszteljük. Ezek ellenőrzik, hogy helyes formátumúak-e az adatok.
- *8-as teszteset*:
  A 8-as tesztesetben a telefonkönyv **fájlból beolvasását** teszteljük. Beolvassuk a tesztadatsort, majd megnézzük, sikerült-e.
- *9-es teszteset*:
  A 9-es tesztesetben a telefonkönyv **keres** függvényét vizsgáljuk. Megnézzük a név és a telefonszám alapú keresésre is, hogy megtalálják-e a keresett adatot, illetve dobják-e a megfelelő kivételeket (ha nem létezőre keresünk, ha rossz formátumúval keresünk, ha több elem van a keresett adatával)
- *10-es teszteset*:
  A 10-es tesztesetben a telefonkönyv **clear** függvényét vizsgáljuk. Megnézzük, tényleg kitörli-e a telefonkönyv összes adatát. Megnézzük azt is, kivételt dob-e, ha üres listát próbálunk törölni.
- *11-es teszteset*:
  A 11-es tesztesetben a telefonkönyv **kiir** függvényét vizsgáljuk. Kiírjuk egy fájlba, majd a fájlt megvizsgálva ellenőrizzük, hogy jól írta-e ki magát.
  
  
