#include <iostream>
#include <array>
#include <time.h>

using namespace std;

void wyzeruj(int rozmiar, short int** t, int wiersz, int kolumna)
{
	for (int j = kolumna; j < rozmiar; j++)
	{
		for (int i = wiersz; i < rozmiar; i++)
		{
			t[i][j] = 0;
		}
		wiersz = 0;
	}
}

void kasuj_trojki(int rozmiar, short int** t, int kolumna)
{
	for (int i = 0; i < rozmiar; i++)
	{
		if (t[i][kolumna] == 3)
			t[i][kolumna] = 0;
	}
}
//kazde szachowanie dodaje 2, jesli chcemy  usunac szachowanie wywolujemy z typ = -2
void szach(int rozmiar, short int** t, int wiersz, int kolumna, int typ = 2)
{
	int i = wiersz; 
	int k = 0;
	while (kolumna + k < rozmiar - 1)
	{
		k++;
		t[i][kolumna + k] +=typ;
		if (i - k >= 0) t[i - k][kolumna + k] += typ;
		if (i + k <= rozmiar - 1) t[i + k][kolumna + k] += typ;
	}
}

int miejsce(int rozmiar, short int** t, int kolumna)
{
	int i = 0;
	while ((i < rozmiar) && (t[i][kolumna] != 0))
		i++;
	return i; 
	//8 oznacza ¿e nie ma miejsca
}

void wypisz(int rozmiar, short int** t)
{
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			cout << t[i][j];
		}
		cout << endl;
	}
}

void wypisz_wynik(int* wynik, int rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
		cout << wynik[i] << " ";
}

int main()
{
	bool chceWypisac;
	int rozmiar;
	cout << "Podaj liczbe hetmanow" << endl;
	cin >> rozmiar;
	cout << "Wypisac wyniki (1) czy tylko statystyki (0)?" << endl;
	cin >> chceWypisac;
	int* wynik = new int[rozmiar];
	const clock_t begin_time = clock();
	int licznik = 0;
	short int** tab = new short int*[rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		tab[i] = new short int[rozmiar];
	}
	wyzeruj(rozmiar, tab, 0, 0);
	// 0 - dostepne pole, 1 - zajete pole, 2 - szachowane pole, 3 - z³e pole
	int wiersz = 0, kolumna = 0;
	while (tab[rozmiar-1][0] != 3)
	{
		if (kolumna == rozmiar)
		{
			if (chceWypisac)
			{
				wypisz_wynik(wynik, rozmiar);
				cout << endl;
			}
			licznik++;
			kolumna--;
			wiersz = wynik[kolumna];
			tab[wiersz][kolumna] = 3;
		}
		wiersz = miejsce(rozmiar, tab, kolumna);
		if (wiersz == rozmiar)
		{
			kasuj_trojki(rozmiar, tab, kolumna);
			kolumna--;
			wiersz = wynik[kolumna];
			tab[wiersz][kolumna] = 3;
			szach(rozmiar, tab, wiersz, kolumna, -2);
				
		}
		else
		{
			tab[wiersz][kolumna] = 1;
			wynik[kolumna] = wiersz;
			szach(rozmiar, tab, wiersz, kolumna);
			kolumna++;
		}
	}
	cout << "Liczba rozwiazan to: " << licznik << endl;
	std::cout << "Obliczono w czasie: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "s";
	cin.get();
	cin.get();
	delete[] wynik;
	for (int i = 0; i < rozmiar; i++)
	{
		delete[] tab[i];
	}
	delete[] tab;
}