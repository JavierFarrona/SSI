#include "vernam.h"

#include <bitset>
#include <iostream>
#include <random>

std::string textToBinary(const std::string& text) {
  std::string binary = "";
  for (char c : text) {
    binary += std::bitset<ASCII_BITS>(c).to_string();
  }
  return binary;
}

std::string binaryToText(const std::string& binary) {
  std::string text = "";
  for (size_t i = 0; i < binary.size(); i += ASCII_BITS) {
    std::bitset<ASCII_BITS> bits(binary.substr(i, ASCII_BITS));
    unsigned long charValue = bits.to_ulong();

    // Verificar explícitamente si es un valor ASCII válido imprimible
    if (charValue >= 33 && charValue <= 126) {
      text += static_cast<char>(charValue);
    } else {
      std::cerr
          << "Advertencia: Valor binario no válido para ASCII imprimible: "
          << bits << std::endl;
      text += '?';
    }
  }
  return text;
}

std::string generateRandomKey(size_t length) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 1);

  std::string key = "";
  for (size_t i = 0; i < length; ++i) {
    key += dist(gen) ? '1' : '0';
  }
  return key;
}

std::string xorOperation(const std::string& binary1,
                         const std::string& binary2) {
  if (binary1.size() != binary2.size()) {
    std::cerr
        << "Error: Las cadenas binarias deben tener el mismo tamaño para XOR."
        << std::endl;
    return "";
  }

  std::string result = "";
  for (size_t i = 0; i < binary1.size(); ++i) {
    result += (binary1[i] == binary2[i]) ? '0' : '1';
  }
  return result;
}