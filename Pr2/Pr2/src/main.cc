#include <iostream>

#include "vigenere.h"

int main() {
  std::string key, text;

  // Leer clave y texto
  std::cout << "Introduce la palabra clave (sin espacios, solo letras): ";
  std::cin >> key;

  std::cout << "Introduce el texto original: ";
  std::cin.ignore();  // Limpiar el buffer de entrada
  std::getline(std::cin, text);

  // Preprocesar texto y extender clave
  std::string plaintext = preprocessText(text);
  std::string extendedKey = extendKey(key, plaintext.length());

  int aux;
  std::cout << "Que desea hacer: \n1. Encriptar\n2. Desencriptar\n";
  std::cin >> aux;

  if (aux == 1) {
    // Cifrar el texto
    std::string ciphertext = encryptVigenere(plaintext, extendedKey);
    std::cout << "Texto cifrado: " << ciphertext << std::endl;
  } else if (aux == 2) {
    // Descifrar el texto
    std::string decryptedText = decryptVigenere(plaintext, extendedKey);
    std::cout << "Texto descifrado: " << decryptedText << std::endl;
  } else {
    std::cerr << "opcion invalida";
    return 1;
  } 

  return 0;
}