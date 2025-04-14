#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template <typename T>

class ArrayList {
private:
	T* dane;
	int maxroz;
	int roz;
	void zmroz() {
		if (roz == 0) {
			maxroz = 1;
		}
		else {
			maxroz *= 2;
		}
		T* nDane = new T[maxroz];
		for (int i = 0; i < roz; i++) {
			nDane[i] = dane[i];
		}
		delete[] dane;
		dane = nDane;
	}

public:
	ArrayList() : dane(nullptr), maxroz(0), roz(0) {}

	~ArrayList() {
		delete[] dane;
	}

	void DodajP(T element) {
		if (roz == maxroz) {
			zmroz();
		}
		for (int i = roz; i > 0; i--) {
			dane[i] = dane[i - 1];
		}
		dane[0] = element;
		roz++;

	}

	void UsunP() {
		if (roz > 0) {
			for (int i = 0; i < roz - 1; i++) {
				dane[i] = dane[i + 1];
			}
			roz--;
		}
		else {
			throw std::out_of_range("Tablica jest pusta");
		}
	}

	void DodajK(T element) {
		if (roz == maxroz) {
			zmroz();
		}
		dane[roz++] = element;
	}

	void UsunK() {
		if (roz > 0) {
			roz--;
		}
		else {
			throw std::out_of_range("Tablica jest pusta");
		}
	}

	void DodajLos(int miejsce, T element) {
		if (roz == maxroz) {
			zmroz();
		}
		if (miejsce < 0 || miejsce > roz) {
			throw std::out_of_range("Indeks poza zakresem");
		}
		for (int i = roz; i > miejsce; i--) {
			dane[i] = dane[i - 1];
		}
		dane[miejsce] = element;
		roz++;

	}

	void UsunLos(int miejsce) {
		if (miejsce < 0 || miejsce >= roz) {
			throw std::out_of_range("Indeks poza zakresem");
		}
		for (int i = miejsce; i < roz - 1; i++) {
			dane[i] = dane[i + 1];
		}
		roz--;
	}

	bool Szukaj(T element) {
		for (int i = 0; i < roz; i++) {
			if (dane[i] == element) {
				return true;
			}
		}
		return false;
	}

	int wielkosc() {
		return roz;
	}

	void wyswietl() {
		for (int i = 0; i < roz; i++) {
			std::cout << dane[i] << " ";
		}
		std::cout << std::endl;
	}
};

#endif //ARRAYLIST_H
