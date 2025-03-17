#include "../lib/gps.h"

#include <iostream>
#include <vector>

std::pair<int, int> calcular_taps(int prn) {
    int tap1 = (prn % 8) + 1;
    int tap2 = ((prn + 5) % 10) + 1;
    return {tap1, tap2};
}

// Función para generar la secuencia C/A para un satélite específico
std::vector<int> generateCA(int satID, int length) {
    std::vector<int> caSequence;

    // Registro de desplazamiento G1 y G2
    std::vector<int> G1(10, 1);
    std::vector<int> G2(10, 1);

    // Tap positions para los satélites (Ejemplo para satélite 1: taps en 2 y 6)
    int tap1, tap2;
    switch (satID) {
        case 1: tap1 = 2; tap2 = 6; break;
        case 2: tap1 = 3; tap2 = 7; break;
        case 3: tap1 = 4; tap2 = 8; break;
        case 4: tap1 = 5; tap2 = 9; break;
        case 5: tap1 = 1; tap2 = 9; break;
        case 6: tap1 = 2; tap2 = 10; break;
        case 7: tap1 = 1; tap2 = 8; break;
        case 8: tap1 = 2; tap2 = 9; break;
        case 9: tap1 = 3; tap2 = 10; break;
        case 10: tap1 = 2; tap2 = 3; break;
        case 11: tap1 = 3; tap2 = 4; break;
        case 12: tap1 = 5; tap2 = 6; break;
        case 13: tap1 = 6; tap2 = 7; break;
        case 14: tap1 = 7; tap2 = 8; break;
        case 15: tap1 = 8; tap2 = 9; break;
        case 16: tap1 = 9; tap2 = 10; break;
        case 17: tap1 = 1; tap2 = 4; break;
        case 18: tap1 = 2; tap2 = 5; break;
        case 19: tap1 = 3; tap2 = 6; break;
        case 20: tap1 = 4; tap2 = 7; break;
        case 21: tap1 = 5; tap2 = 8; break;
        case 22: tap1 = 6; tap2 = 9; break;
        case 23: tap1 = 1; tap2 = 3; break;
        case 24: tap1 = 4; tap2 = 6; break;
        case 25: tap1 = 5; tap2 = 7; break;
        case 26: tap1 = 6; tap2 = 8; break;
        case 27: tap1 = 7; tap2 = 9; break;
        case 28: tap1 = 8; tap2 = 10; break;
        case 29: tap1 = 1; tap2 = 6; break;
        case 30: tap1 = 2; tap2 = 7; break;
        case 31: tap1 = 3; tap2 = 8; break;
        case 32: tap1 = 4; tap2 = 9; break;
        default: break; // Valores por defecto
    }

    for (int i = 0; i < length; ++i) {
        // Generar salida del generador G1
        int G1_output = G1[9];

        // Generar salida del generador G2 usando los taps específicos del satélite
        int G2_output = G2[tap1 - 1] ^ G2[tap2 - 1];

        // Secuencia C/A es la XOR de G1 y G2
        caSequence.push_back(G1_output ^ G2_output);

        // Imprimir estado de los registros y retroalimentaciones
        std::cout << "Iteración " << i + 1 << ": " << std::endl;
        std::cout << "  G1: ";
        for (int bit : G1) std::cout << bit;
        std::cout << " | Retroalimentación: " << (G1[2] ^ G1[9]) << std::endl;

        std::cout << "  G2: ";
        for (int bit : G2) std::cout << bit;
        std::cout << " | Retroalimentación: " << (G2[1] ^ G2[2] ^ G2[5] ^ G2[7] ^ G2[8] ^ G2[9]) << std::endl;

        // Desplazamiento en G1
        int G1_new = G1[2] ^ G1[9];
        for (int j = 9; j > 0; --j) {
            G1[j] = G1[j - 1];
        }
        G1[0] = G1_new;

        // Desplazamiento en G2
        int G2_new = G2[1] ^ G2[2] ^ G2[5] ^ G2[7] ^ G2[8] ^ G2[9];
        for (int j = 9; j > 0; --j) {
            G2[j] = G2[j - 1];
        }
        G2[0] = G2_new;
    }

    return caSequence;
}