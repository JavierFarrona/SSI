#pragma once  // Ensures the header file is included only once during
              // compilation

#include <iostream>  // For input/output operations
#include <string>    // For string manipulation (not used in this code yet)
#include <vector>    // For using dynamic arrays (vectors)

// AES class definition
class AES {
  // Private member variables
  std::vector<int> S_Caja;  // Substitution box (S-Box) used in AES encryption
  std::vector<std::vector<int>> Rcon;  // Round constants used in key expansion

  std::vector<std::vector<int>> clave_extendida;  // Expanded key for AES rounds
  std::vector<std::vector<int>> clave_original;   // Original encryption key
  std::vector<std::vector<int>> mensaje;  // Input message to be encrypted

  std::vector<std::vector<int>> resultado;  // Resulting encrypted message

 public:
  // Constructor and destructor
  AES();     // Constructor to initialize the AES object
  ~AES(){};  // Destructor (empty, as no dynamic memory is allocated)

  // Public methods
  void cifrar();  // Method to perform AES encryption

  // Method to input the encryption key and message
  void introducir_datos(std::vector<std::vector<int>> clave,
                        std::vector<std::vector<int>> entrada);

  // Method to output the result
  void write();

 private:
  // Private methods for AES encryption steps
  void expandir_clave();  // Expands the original key into multiple round keys
  void addRoundKey(int iteracion);  // Adds the round key to the state
  void SubBytes();   // Performs the SubBytes transformation (byte substitution
                     // using S-Box)
  void ShiftRow();   // Performs the ShiftRows transformation (row shifting)
  void MixColumn();  // Performs the MixColumns transformation (column mixing)
};