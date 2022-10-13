#include<iostream>
#include<fstream>
#include <filesystem>

using namespace std;


int** matrice;
int** ponderi;
int** rezultat;

//int matriceStatic[10][10];
//int matriceStatica[1000][1000];
//int matriceStatica[10][10000];
//int matriceStatica[10000][10];
int matriceStatica[10000][500];

void dealoca(int n, int N, int M) {
	for (int i = 0; i < n; i++) {
		delete[] ponderi[i];
	}
	delete[] ponderi;
	for (int i = 0; i < N; i++) {
		delete[] matrice[i];
		delete[] rezultat[i];
	}
	delete[] rezultat;
	delete[] matrice;
}

void citeste(int n,int N, int M, string numeFisier, string numeFisierPonderi) {
	ifstream fisier(numeFisier);
	ifstream fisierPonderi(numeFisierPonderi);
	ponderi = new int* [n];
	for (int i = 0; i < n; i++) {
		ponderi[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fisierPonderi >> ponderi[i][j];
		}
	}
	matrice = new int* [N];
	rezultat = new int* [N];
	for (int i = 0; i < N; i++) {
		matrice[i] = new int[M];
		rezultat[i] = new int[M];
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) {
			fisier >> matrice[i][j];
		}
	}
}

void citesteStatic(int n, int N, int M, string numeFisier, string numeFisierPonderi) {
	ifstream fisier(numeFisier);
	ifstream fisierPonderi(numeFisierPonderi);
	ponderi = new int* [n];
	for (int i = 0; i < n; i++) {
		ponderi[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fisierPonderi >> ponderi[i][j];
		}
	}
	rezultat = new int* [N];
	for (int i = 0; i < N; i++) {
		rezultat[i] = new int[M];
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) {
			fisier >> matriceStatica[i][j];
		}
	}
}

void scrie(int N, int M) {
	ofstream out("rezultatSecvential.txt");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			out << rezultat[i][j] << " ";
		}
		out << endl;
	}

}

void filtreaza(int n, int N, int M) {

	int linii = n / 2;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int trans = 0;
			for (int p1 = -linii; p1 <= linii; p1++) {
				for (int p2 = -linii; p2 <= linii; p2++) {
					int poz1 = i + p1;
					int poz2 = j + p2;
					if (poz1 < 0) poz1 = 0;
					if (poz1 >= N) poz1 = N - 1;
					if (poz2 < 0) poz2 = 0;
					if (poz2 >= M)poz2 = M - 1;
					trans += matrice[poz1][poz2] * ponderi[p1 + linii][p2 + linii];
				}
			}
			rezultat[i][j] = trans;
		}
	}
	
}

void run(int n, int N, int M, string numeFisier, string numeFisierPonderi) {
	citeste(n, N, M, numeFisier, numeFisierPonderi);
	filtreaza(n, N, M);
	scrie(N,M);
}

int main(void) {
	run(3, 10, 10, "date.txt", "ponderi3.txt");
	//run(5,1000,1000, "date1.txt","ponderi5.txt");
	//run(5,10000,10, "date2.txt","ponderi5.txt");
	//run(5,10,10000, "date3.txt","ponderi5.txt");
	//run(5, 10000, 500, "date4.txt", "ponderi5.txt");
	return 0;
}