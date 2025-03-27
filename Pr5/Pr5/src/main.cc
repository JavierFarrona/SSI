#include <iostream>
#include <bitset>
#include <cstdint>
#include <limits> // Incluir el encabezado para std::numeric_limits

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

int main() {
    unsigned int byte1, byte2;
    std::string algorithm;
    
    // Entrada de datos
    std::cout << "Ingrese el primer byte en hexadecimal (sin 0x): ";
    std::cin >> std::hex >> byte1;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    
    std::cout << "Ingrese el segundo byte en hexadecimal (sin 0x): ";
    std::cin >> std::hex >> byte2;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    
    std::cout << "Ingrese el algoritmo (AES/SNOW3G): ";
    std::getline(std::cin, algorithm);
    
    uint8_t poly = (algorithm == "AES") ? AES_POLY : SNOW3G_POLY;
    bool isSnow3G = (algorithm == "SNOW3G");
    uint8_t result = gf_multiply(static_cast<uint8_t>(byte1), static_cast<uint8_t>(byte2), poly, isSnow3G);
    /*
    // Verificación detallada del cálculo paso a paso
    std::cout << "\nDebugging Multiplication en GF(2^8):" << std::endl;
    uint8_t a = static_cast<uint8_t>(byte1);
    uint8_t b = static_cast<uint8_t>(byte2);
    uint8_t debug_result = 0;
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            debug_result ^= a;
        }
        b >>= 1;
        bool msb_set = (a & 0x80);
        a <<= 1;
        if (msb_set) {
            a ^= poly;
        }
        std::cout << "Paso " << i + 1 << ": " << std::bitset<8>(debug_result) << " (0x" << std::hex << (int)debug_result << ")" << std::endl;
    }
    */
    
    std::cout << "\nPrimer byte: " << std::bitset<8>(byte1) << " (0x" << std::hex << byte1 << ")" << std::endl;
    std::cout << "Segundo byte: " << std::bitset<8>(byte2) << " (0x" << std::hex << byte2 << ")" << std::endl;
    std::cout << "Byte Algoritmo: " << std::bitset<8>(poly) << " (0x" << std::hex << (int)poly << ")" << std::endl;
    std::cout << "Multiplicación: " << std::bitset<8>(result) << " (0x" << std::hex << (int)result << ")" << std::endl;
    
    return 0;
}