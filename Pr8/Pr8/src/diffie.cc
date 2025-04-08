#include <iostream>
#include "../lib/diffie.h"

int pow (int base, int exponente, const int mod) {
  int resultado = 1;
  base = base % mod;

  while (exponente > 0) {
    if (exponente % 2 == 1) {
      resultado = (resultado * base) % mod;
      exponente--;
    } else {
      base = (base * base) % mod;
      exponente /= 2;
    }
  }

  return resultado;
}

void diffie_hellman(int mod, int base, int x_a, int x_b)
{
    int y_a, y_b;

    std::cout << "------------------Canal público------------------\n";
    std::cout << "Número primo: " << mod;
    std::cout << "\nAlfa: " << base;
    std::cout << "\n-------------------------------------------------\n";

    std::cout << "------------------A------------------\n";
    std::cout << "Número secreto: " << x_a;
    y_a = pow(base, x_a, mod);
    std::cout << "\n-------------------------------------\n";

    std::cout << "------------------B------------------\n";
    std::cout << "Número secreto: " << x_b;
    y_b = pow(base, x_b, mod);
    std::cout << "\n-------------------------------------\n";

    std::cout << "------------------Canal público------------------\n";
    std::cout << "[A] - Me da " << y_a;
    std::cout << "\n[B] - A mi " << y_b;
    std::cout << "\n-------------------------------------------------\n";

    std::cout << "------------------A------------------\n";
    std::cout << "Entonces K vale " << pow(y_b, x_a, mod);
    std::cout << "\n-------------------------------------\n";

    std::cout << "------------------B------------------\n";
    std::cout << "Entonces K vale " << pow(y_a, x_b, mod);
    std::cout << "\n-------------------------------------\n";
}