#include "../lib/gps.h"

int main() {
    int length;
    std::cout << "Ingrese la longitud de la secuencia: ";
    std::cin >> length;

    std::vector<int> caCode = generateCA(length);

    std::cout << "Secuencia C/A generada: ";
    for (int bit : caCode) {
        std::cout << bit;
    }
    std::cout << std::endl;

    return 0;
}