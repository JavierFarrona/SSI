#include <iostream>
#include <bitset>
#include <cstdint>
#include <limits> // Incluir el encabezado para std::numeric_limits

#include "../lib/multiply.h"

// Definir los polinomios módulo para SNOW 3G y AES
#define AES_POLY 0x1B  // x^8 + x^4 + x^3 + x + 1
#define SNOW3G_POLY 0xA9 // x^8 + x^7 + x^5 + x^3 + 1

// Función para multiplicación en el campo finito GF(2^8)
uint8_t gf_multiply(uint8_t a, uint8_t b, uint8_t poly, bool isSnow3G) {
    uint8_t result = 0; // Variable para almacenar el resultado de la multiplicación
    
    // Bucle para realizar la multiplicación bit a bit
    for (int i = 0; i < 8; i++) {
        if (b & 1) {   // Si el bit menos significativo de b es 1, sumamos (XOR) a al resultado
            result ^= a;
        }
        b >>= 1; // Desplazamos b un bit a la derecha
        
        // Comprobamos si el bit más significativo de a está activo antes de desplazarlo
        bool msb_set = (a & 0x80);
        a <<= 1; // Desplazamos a un bit a la izquierda
        
        // Si el bit más significativo estaba activo antes del desplazamiento, realizamos la reducción
        if (msb_set) {
            a ^= poly;  // Aplicamos el polinomio irreducible para asegurar que el resultado esté en GF(2^8)
        }
    }
    
    if (isSnow3G) {
        // Sumar uno al primer conjunto de 4 bits y restar uno al último conjunto de 4 bits
        result = ((result & 0xF0) + 0x10) | ((result & 0x0F) - 0x01);
    }
    
    return result; // Devolvemos el resultado final
}