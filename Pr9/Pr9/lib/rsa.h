#include <cmath>       // Biblioteca para funciones matemáticas como pow y sqrt
#include <cstdlib>     // Biblioteca para funciones generales como rand y abs
#include <ctime>       // Biblioteca para trabajar con tiempo (por ejemplo, srand)
#include <iostream>    // Biblioteca para entrada y salida estándar
#include <string>      // Biblioteca para trabajar con cadenas de texto
#include <vector>      // Biblioteca para trabajar con vectores

using namespace std;   // Evita tener que escribir std:: antes de nombres de la biblioteca estándar

// Función para calcular la exponenciación modular: (base^exp) % mod
long long modexp(long long base, long long exp, long long mod);

// Función para determinar si un número es primo
bool esPrimo(int n);

// Algoritmo de Euclides extendido para calcular el MCD y los coeficientes de Bézout
int mcdExtendido(int a, int b, int &x, int &y);

// Convierte una letra a su representación numérica
int letraANum(char c);

// Convierte un número a su representación como letra
char numALetra(int n);

// Codifica un mensaje en un vector de números utilizando una clave pública (n)
vector<int> codificarMensaje(string mensaje, int n);