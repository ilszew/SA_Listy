#include <iostream>
#include "singlyLinkedList.h"
#include "arrayList.h"

int main() {

    SinglyLinkedList<int> singlyList;

    singlyList.addLast(10);
    singlyList.addLast(20);
    singlyList.addFirst(5);
    singlyList.addAt(2, 15);
    std::cout << "SinglyLinkedList: rozmier = " << singlyList.getSize() << std::endl;

    // Usuwanie elementów
    singlyList.removeFirst();
    singlyList.removeLast();
    std::cout << "Po usunieciu: rozmiar = " << singlyList.getSize() << std::endl;

    std::cout << "Czy 10 jest na liscie? " << std::endl;
    if (singlyList.search(10)) {
        std::cout <<"Tak";
    }else {
        std::cout <<"Nie";
    }
    ArrayList<int> arrayList;
    arrayList.DodajK(10);
    arrayList.DodajK(20);
    arrayList.DodajP(5);
    arrayList.DodajLos(2, 15);
    std::cout << "ArrayList: rozmiar = " << arrayList.wielkosc() << std::endl;
    arrayList.wyswietl();
    
    arrayList.UsunP();
    arrayList.UsunK();
    arrayList.UsunLos(1);
    std::cout << "Po usunieciu: rozmiar = " << arrayList.wielkosc() << std::endl;
    arrayList.wyswietl();

    std::cout << "Czy 10 jest na liscie? " << std::endl;
    if (arrayList.Szukaj(10)) {
        std::cout << "Tak";
    }
    else {
        std::cout << "Nie";
    }
    return 0;
}