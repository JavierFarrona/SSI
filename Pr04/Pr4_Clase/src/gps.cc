#include "../lib/gps.h"

std::pair<int, int> calcular_taps(int id) {
    int tap1 = (id % 8) + 1;
    int tap2 = ((id + 5) % 10) + 1;
    return {tap1, tap2};
}

// Función para generar la secuencia C/A para un satélite específico
std::vector<int> generateCA(int length) {
    std::vector<int> caSequence;

    // Registro de desplazamiento G1 y G2
    std::vector<int> G1(10, 1);
    std::vector<int> G2(10, 1);

    for (int i = 0; i < length; ++i) {
        // Generar salida del generador G1
        int G1_output = G1[9];

        // Generar salida del generador G2 usando los taps específicos del satélite
        //int G2_output = G2[tap1 - 1] ^ G2[tap2 - 1];

        // Secuencia C/A es la XOR de G1 y G2
        caSequence.push_back(G1_output ^ G2[9]);

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