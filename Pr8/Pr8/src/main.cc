#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

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

int main() {
  string mensaje;
  int p, q, d;

  cout << "Introduce el mensaje (en mayúsculas, sin espacios ni Ñ): ";
  cin >> mensaje;

  cout << "Introduce p (primo): ";
  cin >> p;
  while (!esPrimo(p)) {
    cout << "p no es primo. Intenta de nuevo: ";
    cin >> p;
  }

  cout << "Introduce q (primo): ";
  cin >> q;
  while (!esPrimo(q)) {
    cout << "q no es primo. Intenta de nuevo: ";
    cin >> q;
  }

  int n = p * q;
  int phi = (p - 1) * (q - 1);
  cout << "n = " << n << ", φ(n) = " << phi << endl;

  cout << "Introduce d (coprimo con φ(n)): ";
  cin >> d;

  int x, y;
  while (mcdExtendido(d, phi, x, y) != 1) {
    cout << "d no es coprimo con φ(n). Intenta de nuevo: ";
    cin >> d;
  }

  // Calcular e (inverso de d módulo φ(n))
  int e;
  mcdExtendido(d, phi, x, y);
  e = x % phi;
  if (e < 0) e += phi;

  cout << "Clave pública (e, n): (" << e << ", " << n << ")" << endl;
  cout << "Clave privada (d, n): (" << d << ", " << n << ")" << endl;

  // Codificar mensaje
  vector<int> bloques = codificarMensaje(mensaje, n);
  cout << "Bloques codificados: ";
  for (int b : bloques) cout << b << " ";
  cout << endl;

  // Cifrar bloques
  vector<int> cifrado;
  for (int b : bloques) cifrado.push_back(modexp(b, e, n));

  cout << "Bloques cifrados: ";
  for (int c : cifrado) cout << c << " ";
  cout << endl;

  return 0;
}
