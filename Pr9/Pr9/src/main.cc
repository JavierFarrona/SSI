#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "../lib/rsa.h"

using namespace std;

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
