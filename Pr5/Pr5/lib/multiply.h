#include <iostream>
#include <bitset>
#include <cstdint>
#include <limits> // Incluir el encabezado para std::numeric_limits

// Definir los polinomios módulo para SNOW 3G y AES
#define AES_POLY 0x1B  // x^8 + x^4 + x^3 + x + 1
#define SNOW3G_POLY 0xA9 // x^8 + x^7 + x^5 + x^3 + 1

uint8_t gf_multiply(uint8_t a, uint8_t b, uint8_t poly, bool isSnow3G);