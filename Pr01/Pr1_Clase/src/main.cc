#include <iostream>

#include "vernam.h"

int main() {
  std::string originalMessage;

  std::cout << "Introduce el mensaje original: ";
  std::getline(std::cin, originalMessage);

  std::string binaryMessage = textToBinary(originalMessage);
  std::cout << "Mensaje original en binario: " << binaryMessage << std::endl;
  std::cout << "Longitud del mensaje binario: " << binaryMessage.size()
            << " bits" << std::endl;

  std::string randomKey;
  
  std::cout << "Quiere introducir usted la clave (s/n)\n";

  char aux;
  std::cin >> aux;

  if (aux == 's') {
    std::cout << "Introduce la clave aleatoria (" << binaryMessage.size()
            << " bits): ";
    std::cin >> randomKey;

    if (randomKey.size() != binaryMessage.size()) {
      std::cerr << "Error: La clave aleatoria debe tener el mismo tamaño que el "
                  "mensaje."
                << std::endl;
      return 1;
    }
  } else if (aux == 'n') {
    randomKey = generateRandomKey(binaryMessage.size());
    std::cout << "Su clave es: ";
    std::cout << randomKey;
  } else {
    std::cerr << "Opcion no válida\n";
    return 1;
  }

  int option;
  std::cout << "\n¿Que desea hacer?:\n1. Encriptar mensaje\n2. Desencriptar "
               "mensaje\n";
  std::cin >> option;

  std::string resultBinary;
  switch (option) {
    case 1:
      resultBinary = xorOperation(binaryMessage, randomKey);
      break;
    case 2:
      resultBinary = xorOperation(binaryMessage, randomKey);
      break;
    default:
      std::cerr << "Opción inválida." << std::endl;
      return 1;
  }

  std::string resultText = binaryToText(resultBinary);
  std::cout << "Resultado en binario: " << resultBinary << std::endl;
  std::cout << "Resultado en texto: " << resultText << std::endl;

  return 0;
}
