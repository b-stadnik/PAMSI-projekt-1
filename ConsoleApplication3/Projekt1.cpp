#include "pch.h"
#include "algorytmy_sortujace.hh"
#include <iostream>
#include <algorithm>
#include <time.h>
#include <chrono>

using namespace std;
typedef chrono::high_resolution_clock Zegar;
//m - ilosc tablic, n - rozmiar tablicy
int m = 100, n = 1000000;
int maxdepth = log(n) * 2;
using FunkcjaSort = void (*)(int*, int, int, int);

void wypelnij_losowymi(int tab[])
{
	for (int i = 0; i < n; i++)
		tab[i] = rand() % 100000; //przedzial liczbowy od 1 do 100000
}

void wyswietl(int tab[])
{
	for (int i = 0; i < n - 1; i++)
		cout << tab[i] << ", ";
	cout << tab[n-1] << endl;
}

void sprawdz_posortowanie(int tab[])
{
	for (int i = 0; i < n - 1; i++)
		if (tab[i] > tab[i + 1])
		{
			cout << "Tablica jest nieposortowana"<<endl;
			return;
		}
}

void sortuj_procent(int tab[], double x)
{
	make_quicksort(tab, 0, (n*x)/100 - 1, 0);
}

void sortuj_odwroc(int tab[])
{
	sort(tab, tab+n, greater<int>());
}

//funkcja sortuje odpowiednim algortymem przekazywanym przez wskaznik i zwraca czas sortowania tablicy
double sortuj(FunkcjaSort sort, int *tab)
{
	auto czas_start = Zegar::now();
	sort(tab, 0, n - 1,maxdepth);
	auto czas_stop = Zegar::now();
	return chrono::duration_cast<chrono::milliseconds>(czas_stop - czas_start).count();
}


int main()
{

	srand(time(NULL));
	int j;
	double czas=0;

	//wskazniki na funkcje
	FunkcjaSort mpoint = &make_mergesort, qpoint = &make_quicksort, ipoint = &make_introsort;

	int **tablica;
	tablica = new int *[m];
	for (j = 0; j < m; j++)
	{
		tablica[j] = new int[n];
		wypelnij_losowymi(tablica[j]);
		//sortuj_procent(tablica[j],97.3);
		//sortuj_odwroc(tablica[j]);
		czas = czas + sortuj(ipoint,tablica[j]); //aby zastosowac inny algortym- podmienic 1-szy argument zgodnie z FunkcjaSort
		//wyswietl(tablica[j]);
		sprawdz_posortowanie(tablica[j]);
	}
	cout << "Czas trwania sortowania to " << czas << " ms"<<endl;

	for (j = 0; j < m; j++)
	{
		delete[] tablica[j];
	}
	return 0;
}