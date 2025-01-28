#include "vigenere.h"
#include <iostream>

int main() {
    std::string key, text;

    // Leer clave y texto
    std::cout << "Introduce la palabra clave (sin espacios, solo letras): ";
    std::cin >> key;
    
    std::cout << "Introduce el texto original: ";
    std::cin.ignore(); // Limpiar el buffer de entrada
    std::getline(std::cin, text);

    // Preprocesar texto y extender clave
    std::string plaintext = preprocessText(text);
    std::string extendedKey = extendKey(key, plaintext.length());

    // Cifrar el texto
    std::string ciphertext = encryptVigenere(plaintext, extendedKey);
    std::cout << "Texto cifrado: " << ciphertext << std::endl;

    // Descifrar el texto
    std::string decryptedText = decryptVigenere(ciphertext, extendedKey);
    std::cout << "Texto descifrado: " << decryptedText << std::endl;

    return 0;
}
