#ifndef LISTA_H
#define LISTA_H
#include "ember.h"

/**
 * \file lista.hpp
 *
 * A Lista osztály deklarációja és megvalósítása
 */

template <typename T>
class Lista {

    T* data; ///< A dinamikusan foglalt tömb, amely tárolja az elemeket
    size_t len; ///< Az elemek száma a listában

public:
    /// @return Az elemek száma a listában
    size_t size() const { return len; }

    Lista() : data(NULL), len(0) {}

    /// Az [] operátor, amely visszaadja az adott indexű elemet
    /// @param i Az index, amelyhez tartozó elemet visszaadja
    /// @return Az i. indexen található elem
    /// @throws const char* kivételt, ha túl nagy indexet próbálunk elérni
    T& operator[](size_t i) {
        if (i >= len) throw "tul nagy index!";
        return data[i];
    }

    /// A konstans [] operátor, amely visszaadja az adott indexű elemet
    /// @param i Az index, amelyhez tartozó elemet visszaadja
    /// @return Az i. indexen található elem
    /// @throws const char* kivételt, ha túl nagy indexet próbálunk elérni
    const T& operator[](size_t i) const {
        if (i >= len) throw "tul nagy index!";
        return data[i];
    }

    /// Az értékadás operátor, amely másolja a listát egy másik listába
    /// @param l A másik lista, amelybe másolunk
    /// @return Az újra másolt lista
    /// @throws const char* kivételt, ha nem sikerül a memóriafoglalás
    Lista<T>& operator=(Lista<T>& l) {
        if (this != &l) {
            delete[] data;
            len = l.len;
            try {
                data = new T[len];
                for (size_t i = 0; i < len; i++) {
                    data[i] = l.data[i];
                }
            } catch (std::bad_alloc) {
                throw "Nem sikerult a foglalas!";
            }
        }
        return *this;
    }

    /// Az egyenlőség operátor, amely összehasonlítja két listát
    /// @param l A másik lista, amellyel összehasonlítjuk
    /// @return Igaz, ha a két lista egyenlő, hamis, ha nem
    bool operator==(Lista<T>& l) {
        if (len != l.len) return false;
        for (size_t i = 0; i < len; i++) {
            if (data[i] != l.data[i]) return false;
        }
        return true;
    }

    /// Az elem hozzáadása a listához
    /// @param e Az elem, amelyet hozzáadunk
    /// @throws const char* kivételt, ha nem sikerül a memóriafoglalás
    void addElem(T e) {
        try {
            T* uj = new T[len + 1];
            for (size_t i = 0; i < len; i++) {
                uj[i] = data[i];
            }
            uj[len++] = e;
            delete[] data;
            data = uj;
        } catch (std::bad_alloc) {
            throw "Nem sikerult a foglalas!";
        }
    }

    /// Elem eltávolítása a listából adott index alapján
    /// @param idx Az index, amelyen található elemet eltávolítjuk
    /// @throws const char* kivételt, ha üres listából próbálunk törölni, nem létező indexűt próbálunk törölni, vagy sikertelen a törlés
    void removeElem(size_t idx) {
        if (len <= 0) throw "lista ures!";
        if (len <= idx) throw "nincs ilyen index!";
        Lista<T> uj;
        if (len != 1) {
            for (size_t i = 0; i < len; i++) {
                if (i != idx) try {
                    uj.addElem(data[i]);
                } catch (const char* err) {
                    throw err;
                }
            }
            if (len == uj.len) throw "torles nem sikerult!";
        }
        *this = uj;
    }

    /// Az elem eltávolítása a listából az adott elem alapján
    /// @param e Az elem, amelyet eltávolítunk
    /// @throws const char* kivételt, ha üres listából próbálunk törölni, vagy ha nincs a listában ilyen elem
    void removeElem(T& e) {
        if (len <= 0) throw "lista ures!";
        Lista<T> uj;
        if (len != 1) {
            for (size_t i = 0; i < len; i++) {
                if (data[i] != e) try {
                    uj.addElem(data[i]);
                } catch (const char* err) {
                    throw err;
                }
            }
            if (len == uj.len) throw "nincs ilyen elem";
        } else {
            if (data[0] != e) throw "nincs ilyen elem";
        }
        *this = uj;
    }

    ~Lista() { delete[] data; }
};

#endif // LISTA_H
