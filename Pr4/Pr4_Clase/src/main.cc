#include "../lib/gps.h"

int main() {
    int satID, length;
    std::cout << "Ingrese el ID del satélite: ";
    std::cin >> satID;
    std::cout << "Ingrese la longitud de la secuencia: ";
    std::cin >> length;

    std::vector<int> caCode = generateCA(satID, length);

    std::cout << "Secuencia C/A generada: ";
    for (int bit : caCode) {
        std::cout << bit;
    }
    std::cout << std::endl;

    return 0;
}