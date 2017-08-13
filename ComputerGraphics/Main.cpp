/*********************************************************
Materia: Gráficas Computacionales
Fecha: 13 de agosto del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/


#include <iostream>
using namespace std;

int PerimetroRectangulo(int base, int altura) {
	return(base * 2 + altura * 2);
}

float AreaTriangulo(float base, float altura) {
	return (base*altura / 2);
}

int Mayor(int numero1, int numero2, int numero3) {
	int mayor = numero1;
	(numero2 > numero1 ? mayor = numero2 : (numero3 > numero1 ? mayor = numero3 : 0));
	(numero3 > numero2 ? mayor = numero3 : 0);
	return mayor;
}

int Menor(int numero1, int numero2, int numero3) {
	int menor = numero1;
	(numero2 < numero1 ? menor = numero2 : (numero3 < numero1 ? menor = numero3 : 0));
	(numero3 < numero2 ? menor = numero3 : 0);
	return menor;
}

void FilaEstrellas(int n) {
	for (int i = 0; i < n; i++) {
		cout << '*';
	}
	cout << endl;
}

void MatrizEstrellas(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << '*';
		cout << endl;
	}
}

void PiramideEstrellas(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++)
			cout << '*';
		cout << endl;
	}
}

void FlechaEstrellas(int n) {
	PiramideEstrellas(n);
	for (int i = n - 1; i > 0; i--) {
		for (int j = 1; j <= i; j++)
			cout << '*';
		cout << endl;
	}
}

void Fibonacci(int n) {
	int a = 0, b = 1, c;
	cout << b << ' ';
	for (int i = 1; i < n; i++) {
		cout << (c = a + b) << ' ';
		a = b;
		b = c;
	}
	cout << endl;
}

bool EsPrimo(int numero) {
	for (int i = 2; i < sqrt(numero); i++) {
		if (numero%i == 0) return false;
	}
	return true;
}

int main() {
	int p = PerimetroRectangulo(5, 3);
	float a = AreaTriangulo(5.0f, 3.0f);
	int mayor = Mayor(5, 9, 1);
	int menor = Menor(5, 9, 1);

	cout << p << endl;
	cout << a << endl;
	cout << mayor << endl;
	cout << menor << endl;

	FilaEstrellas(5);
	MatrizEstrellas(4);
	PiramideEstrellas(6);
	FlechaEstrellas(6);
	Fibonacci(9);
	bool primo = EsPrimo(79);
	cout << primo << endl;
	primo = EsPrimo(52);
	cout << primo << endl;
	cin.get();
	return 0;
}

//Fuente consultada: Tutorials Point. (2017, julio 23). C++ Tutorial. 
//		Retrieved from https://www.tutorialspoint.com/cplusplus/index.htm
