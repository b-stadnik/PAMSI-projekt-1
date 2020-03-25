#include "algorytmy_sortujace.hh"
#include "pch.h"
#include <iostream>
#include <algorithm>

//////////////////////////////////////////////////////////
//sortowanie przez scalenie//
//////////////////////////////////////////////////////////
void scalenie(int tab[], int lewy, int srodek, int prawy)
{
	int i, j, k;
	//stworzenie tymczasowych tablic 
	int n1 = srodek - lewy + 1;
	int n2 = prawy - srodek;
	int* Lewy = new int[n1];
	int* Prawy = new int[n2];

	for (i = 0; i < n1; i++)
		Lewy[i] = tab[lewy + i];
	for (j = 0; j < n2; j++)
		Prawy[j] = tab[srodek + 1 + j];

	i = j = 0;
	k = lewy;

	while (i < n1 && j < n2)
	{
		if (Lewy[i] <= Prawy[j])
		{
			tab[k] = Lewy[i];
			i++;
		}
		else
		{
			tab[k] = Prawy[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		tab[k] = Lewy[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		tab[k] = Prawy[j];
		j++;
		k++;
	}
	delete[] Lewy, Prawy;
}
void mergesort(int *tab, int lewy, int prawy)
{
	if (lewy >= prawy) return;

	int srodek = (lewy + prawy) / 2;

	mergesort(tab, lewy, srodek);
	mergesort(tab, srodek + 1, prawy);

	scalenie(tab, lewy, srodek, prawy);
}

//////////////////////////////////////////////////////////
//sortowanie quicksort//
//////////////////////////////////////////////////////////

int partition(int *tab, int lewy, int prawy)
{
	int i = lewy, j = prawy;
	int pivot = tab[(lewy + prawy) / 2]; //punkt odniesienia jest zawsze œrodkiem

	while (1)
	{
		while (tab[j] > pivot) j--;

		while (tab[i] < pivot) i++;

		if (i < j) std::swap(tab[i++], tab[j--]);
		else return j;
	}

}


void quicksort(int *tab, int lewy, int prawy)
{
	if (lewy < prawy)
	{
		int q = partition(tab, lewy, prawy);
		quicksort(tab, lewy, q);
		quicksort(tab, q + 1, prawy);
	}
}



//////////////////////////////////////////////////////////
//sortowanie heapsort//
//////////////////////////////////////////////////////////

void heapsort(int *lewy, int *prawy)
{
	std::make_heap(lewy, prawy);
	std::sort_heap(lewy, prawy);
}

//////////////////////////////////////////////////////////
//sortowanie insertsort//
//////////////////////////////////////////////////////////


void insertion(int *tab, int lewy, int prawy)
{
	int i, j, save;
	for (i = lewy + 1; i <= prawy; i++)
	{
		save = tab[i];
		for (j = i; j >= 1 && tab[j - 1] > save; j--)
			tab[j] = tab[j - 1];
		tab[j] = save;
	}
}
//////////////////////////////////////////////////////////
//sortowanie introsort//
//////////////////////////////////////////////////////////

void introsort_(int *tab, int *lewy, int *prawy, int maxdepth)
{
	if ((prawy - lewy) < 16) insertion(tab, lewy - tab, prawy - tab);
	else if (maxdepth == 0) heapsort(lewy, prawy + 1);
	else
	{
		int pivot = partition(tab, lewy - tab, prawy - tab);
		introsort_(tab, lewy, tab + pivot, maxdepth - 1);
		introsort_(tab, tab + pivot + 1, prawy, maxdepth - 1);
	}
}


//funkcje do wywolania sortowania w main//
void make_introsort(int *tab, int lewy, int prawy, int glebia)
{
	introsort_(tab, tab, tab + prawy, glebia);
}

void make_mergesort(int *tab, int lewy, int prawy, int glebia)
{
	mergesort(tab, lewy, prawy);
}

void make_quicksort(int *tab, int lewy, int prawy, int glebia)
{
	quicksort(tab, lewy, prawy);
}
