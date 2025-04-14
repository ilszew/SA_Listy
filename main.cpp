#include <iostream>
#include "singlyLinkedList.h"
#include "arrayList.h"
#include "doublyLinkedList.h"

int main() {

    ArrayList<int> arrayList;
    SinglyLinkedList<int> singlyList;
    DoublyLinkedList<int> lista;


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

    singlyList.addLast(10);
    singlyList.addLast(20);
    singlyList.addFirst(5);
    singlyList.addAt(2, 15);
    std::cout << "SinglyLinkedList: rozmiar = " << singlyList.getSize() << std::endl;


    singlyList.removeFirst();
    singlyList.removeLast();
    std::cout << "Po usunieciu: rozmiar = " << singlyList.getSize() << std::endl;

    std::cout << "Czy 10 jest na liscie? " << std::endl;
    if (singlyList.search(10)) {
        std::cout <<"Tak";
    }else {
        std::cout <<"Nie";
    }

    std::cout << "\nElementy na koniec listy:" << std::endl;
    lista.pushBack(10);
    lista.pushBack(20);
    lista.pushBack(30);

    lista.print();
    std::cout << "Rozmiar listy: " << lista.getSize() << std::endl;

    std::cout << "Elementy na początek listy:" << std::endl;
    lista.pushFront(5);
    lista.pushFront(1);

    lista.print();
    std::cout << "Rozmiar listy: " << lista.getSize() << std::endl;

    std::cout << "\nUsuwamy element z początku listy:" << std::endl;
    lista.popFront();
    lista.print();

    std::cout << "\nUsuwamy element z końca listy:" << std::endl;
    lista.popBack();
    lista.print();

    std::cout << "\nCzyszczenie listy" << std::endl;
    lista.clear();
    return 0;
}