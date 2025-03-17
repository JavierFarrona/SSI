#include <sstream>  // Include for string stream operations (used for hex input)

#include "../lib/aes.h"  // Include the AES class header file

// Main function
int main() {
  // Default key and text block (used for option 1)
  std::vector<std::vector<int>> clave_;
  std::vector<std::vector<int>> texto_;

  // Initialize the default key (4x4 matrix)
  clave_ = {{0x00, 0x04, 0x08, 0x0c},
            {0x01, 0x05, 0x09, 0x0d},
            {0x02, 0x06, 0x0a, 0x0e},
            {0x03, 0x07, 0x0b, 0x0f}};

  // Initialize the default text block (4x4 matrix)
  texto_ = {{0x00, 0x44, 0x88, 0xcc},
            {0x11, 0x55, 0x99, 0xdd},
            {0x22, 0x66, 0xaa, 0xee},
            {0x33, 0x77, 0xbb, 0xff}};

  // ------------------------------------

  // Key and text block to be entered by the user (used for option 2)
  std::vector<std::vector<int>> clave;
  std::vector<std::vector<int>> texto;

  // Resize the matrices to 4x4
  for (int i = 0; i < 4; i++) {
    clave.resize(4);
    texto.resize(4);
    for (int j = 0; j < 4; j++) {
      clave[i].resize(4);
      texto[i].resize(4);
    }
  }

  // ------------------------------------

  AES cifrado;          // Create an AES object for encryption
  bool salir = false;   // Flag to exit the program
  int operacion = 0;    // Variable to store the user's choice
  std::string entrada;  // Temporary variable to store user input

  // Main loop for user interaction
  while (!salir) {
    // Display menu options
    std::cout << "------------------------------------";
    std::cout << "\n¿Qué desea hacer?\n";
    std::cout << "[0] Salir.\n";
    std::cout << "[1] Valores por defecto.\n";
    std::cout << "[2] Introducir valores.\n";
    std::cin >> operacion;  // Read the user's choice
    std::cout << "------------------------------------\n";

    // Handle the user's choice
    switch (operacion) {
      case 0:  // Exit the program
        salir = true;
        break;

      case 1:  // Use default key and text block
        std::cout << "Clave: ";
        // Print the default key in hexadecimal format
        for (int j = 0; j < clave_.size(); j++) {
          for (int i = 0; i < clave_[j].size(); i++) {
            std::cout << std::hex << clave_[i][j];
            }
        }
        std::cout << "\nBloque de texto: ";
        // Print the default text block in hexadecimal format
        for (int j = 0; j < texto_.size(); j++) {
          for (int i = 0; i < texto_[j].size(); i++) {
            std::cout << std::hex << texto_[i][j];
            }
        }
        // Perform encryption using the default key and text block
        cifrado.introducir_datos(clave_, texto_);
        cifrado.cifrar();
        cifrado.write();
        break;

      case 2:  // Allow the user to input their own key and text block
        std::cout << "------------------------------------";
        std::cout << "\nIntroduzca la clave:\n";
        // Read the key from the user (4x4 matrix in hexadecimal format)
        for (int j = 0; j < 4; j++) {
          for (int i = 0; i < 4; i++) {
            std::cin >> entrada;  // Read input as a string
            std::istringstream(entrada) >> std::hex >>
                clave[i][j];  // Convert hex string to integer
          }
        }
        std::cout << "------------------------------------";
        std::cout << "\nIntroduzca el texto:\n";
        // Read the text block from the user (4x4 matrix in hexadecimal format)
        for (int j = 0; j < 4; j++) {
          for (int i = 0; i < 4; i++) {
            std::cin >> entrada;  // Read input as a string
            std::istringstream(entrada) >> std::hex >>
                texto[i][j];  // Convert hex string to integer
          }
        }
        std::cout << "------------------------------------";

        // Perform encryption using the user-provided key and text block
        cifrado.introducir_datos(clave, texto);
        cifrado.cifrar();
        cifrado.write();
        break;

      default:  // Handle invalid input
        std::cout << "\nOperación incorrecta.\n";
    }
  }
  return 0;  // Exit the program
}
