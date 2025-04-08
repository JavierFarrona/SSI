#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "../lib/rsa.h"

using namespace std;

// Función para exponenciación modular rápida
long long modexp(long long base, long long exp, long long mod) {
  long long result = 1;
  base %= mod;
  while (exp > 0) {
    if (exp % 2 == 1) result = (result * base) % mod;
    exp /= 2;
    base = (base * base) % mod;
  }
  return result;
}

// Test de Lehman-Peralta para verificar si un número es primo
bool esPrimo(int n) {
  if (n < 2) return false;
  if (n == 2 || n == 3) return true;
  if (n % 2 == 0) return false;

  srand(time(0));
  for (int i = 0; i < 5; ++i) {
    int a = 2 + rand() % (n - 3);  // 2 <= a <= n-2
    int r = modexp(a, (n - 1) / 2, n);
    if (r != 1 && r != n - 1) return false;
  }
  return true;
}

// Algoritmo extendido de Euclides
int mcdExtendido(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int x1, y1;
  int d = mcdExtendido(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return d;
}

// Convertir letra a número (A = 0, ..., Z = 25)
int letraANum(char c) { return c - 'A'; }

// Convertir número a letra
char numALetra(int n) { return 'A' + n; }

// Codificar texto a bloques numéricos
vector<int> codificarMensaje(string mensaje, int n) {
  vector<int> bloques;
  int base = 26;
  int tam_bloque = 1;

  while (pow(base, tam_bloque) < n) tam_bloque++;
  tam_bloque--;  // Usar el último valor válido

  // Rellenar con 'X' si es necesario
  while (mensaje.length() % tam_bloque != 0) mensaje += 'X';

  // Codificar cada bloque
  for (size_t i = 0; i < mensaje.length(); i += tam_bloque) {
    int bloque = 0;
    for (int j = 0; j < tam_bloque; ++j) {
      bloque = bloque * base + letraANum(mensaje[i + j]);
    }
    bloques.push_back(bloque);
  }

  return bloques;
}