#include "../lib/aes.h"  // Include the AES class header file

// Constructor: Initializes the AES object and sets up the S-Box, Rcon, and
// resizes matrices
AES::AES() {
  // Initialize the Substitution Box (S-Box) used in the SubBytes step
  S_Caja = {
      0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b,
      0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
      0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26,
      0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
      0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2,
      0xeb, 0x27, 0xb2, 0x75, 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
      0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed,
      0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
      0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f,
      0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
      0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c, 0x13, 0xec,
      0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
      0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14,
      0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
      0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d,
      0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
      0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f,
      0x4b, 0xbd, 0x8b, 0x8a, 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
      0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11,
      0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
      0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f,
      0xb0, 0x54, 0xbb, 0x16};

  // Initialize the Round Constants (Rcon) used in the key expansion process
  Rcon = {{0x01, 0x00, 0x00, 0x00}, {0x02, 0x00, 0x00, 0x00},
          {0x04, 0x00, 0x00, 0x00}, {0x08, 0x00, 0x00, 0x00},
          {0x10, 0x00, 0x00, 0x00}, {0x20, 0x00, 0x00, 0x00},
          {0x40, 0x00, 0x00, 0x00}, {0x80, 0x00, 0x00, 0x00},
          {0x1B, 0x00, 0x00, 0x00}, {0x36, 0x00, 0x00, 0x00}};

  // Resize the matrices for the result and expanded key
  resultado.resize(4);
  clave_extendida.resize(4);
  for (int i = 0; i < 4; i++) {
    resultado[i].resize(4);         // 4x4 matrix for the result
    clave_extendida[i].resize(44);  // 4x44 matrix for the expanded key
  }
}

// Method to input the encryption key and message
void AES::introducir_datos(std::vector<std::vector<int>> clave,
                           std::vector<std::vector<int>> entrada) {
  clave_original = clave;  // Store the original key
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      clave_extendida[i][j] =
          clave[i][j];  // Copy the original key into the expanded key matrix

  mensaje = entrada;  // Store the input message
}

// Method to expand the encryption key into multiple round keys
void AES::expandir_clave() {
  std::vector<int> Wi_1(4);  // Stores the previous column
  std::vector<int> Wi_4(4);  // Stores the column 4 steps back
  int swap, const_iter = 0;

  for (int j = 4; j < 44; j++)  // Expand the key to 44 columns
  {
    for (int i = 0; i < 4; i++) {
      Wi_1[i] = clave_extendida[i][j - 1];
      Wi_4[i] = clave_extendida[i][j - 4];
    }

    if (j % 4 == 0)  // Perform key schedule core every 4 columns
    {
      // Rotate the column (RotWord)
      swap = Wi_1[0];
      Wi_1[0] = Wi_1[1];
      Wi_1[1] = Wi_1[2];
      Wi_1[2] = Wi_1[3];
      Wi_1[3] = swap;

      // Apply the S-Box to each byte
      for (int i = 0; i < 4; i++) Wi_1[i] = S_Caja[Wi_1[i]];

      // XOR with the round constant
      for (int i = 0; i < 4; i++)
        clave_extendida[i][j] = Wi_4[i] ^ Wi_1[i] ^ Rcon[const_iter][i];

      const_iter++;  // Move to the next round constant
    } else {
      // XOR the previous column with the column 4 steps back
      for (int i = 0; i < 4; i++) clave_extendida[i][j] = Wi_1[i] ^ Wi_4[i];
    }
  }
}

// Method to add the round key to the state matrix
void AES::addRoundKey(int iteracion) {
  int j_iteracion =
      4 * iteracion;  // Calculate the starting column for the round key

  if (iteracion == 0)  // Initial round key addition
  {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        resultado[i][j] = mensaje[i][j] ^ clave_original[i][j];
  } else  // Subsequent round key additions
  {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        resultado[i][j] = resultado[i][j] ^ clave_extendida[i][j + j_iteracion];
  }

  // Debugging output (trace)
  std::cout << "\nR" << iteracion << " (Subclave: ";
  for (int j = 0; j < 4; j++)
    for (int i = 0; i < 4; i++)
      std::cout << std::hex << clave_extendida[i][j + j_iteracion];
  std::cout << ") = ";
  for (int j = 0; j < 4; j++)
    for (int i = 0; i < 4; i++) std::cout << std::hex << resultado[i][j];
  std::cout << "\n";
}

// Method to perform the SubBytes transformation
void AES::SubBytes() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      resultado[i][j] =
          S_Caja[resultado[i][j]];  // Substitute each byte using the S-Box
}

// Method to perform the ShiftRows transformation
void AES::ShiftRow() {
  int swap = 0, fila = 1;

  // Shift the second row left by 1
  swap = resultado[fila][0];
  resultado[fila][0] = resultado[fila][1];
  resultado[fila][1] = resultado[fila][2];
  resultado[fila][2] = resultado[fila][3];
  resultado[fila][3] = swap;

  // Shift the third row left by 2
  fila++;
  swap = resultado[fila][0];
  resultado[fila][0] = resultado[fila][2];
  resultado[fila][2] = swap;
  swap = resultado[fila][1];
  resultado[fila][1] = resultado[fila][3];
  resultado[fila][3] = swap;

  // Shift the fourth row left by 3
  fila++;
  swap = resultado[fila][0];
  resultado[fila][0] = resultado[fila][3];
  resultado[fila][3] = resultado[fila][2];
  resultado[fila][2] = resultado[fila][1];
  resultado[fila][1] = swap;
}

// Method to perform the MixColumns transformation
void AES::MixColumn() {
  unsigned char a[4], b[4], h;

  for (unsigned char j = 0; j < 4; j++) {
    for (unsigned char c = 0; c < 4; c++) {
      a[c] = resultado[c][j];       // Original column
      h = resultado[c][j] & 0x80;   // Check if the high bit is set
      b[c] = resultado[c][j] << 1;  // Multiply by 2 in GF(2^8)

      if (h == 0x80) b[c] ^= 0x1B;  // XOR with the AES irreducible polynomial
    }
    // Perform the column mixing
    resultado[0][j] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
    resultado[1][j] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
    resultado[2][j] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
    resultado[3][j] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
  }
}

// Method to perform AES encryption
void AES::cifrar() {
  std::cout << "\n";

  expandir_clave();  // Expand the key
  addRoundKey(0);    // Initial round key addition

  // Perform 9 main rounds
  for (int i = 1; i < 10; i++) {
    SubBytes();
    ShiftRow();
    MixColumn();
    addRoundKey(i);
  }

  // Perform the final round (no MixColumns)
  SubBytes();
  ShiftRow();
  addRoundKey(10);
}

// Method to output the encrypted result
void AES::write() {
  std::cout << "\nTexto cifrado: ";
  for (int j = 0; j < resultado.size(); j++)
    for (int i = 0; i < resultado[j].size(); i++)
      std::cout << std::hex
                << resultado[i][j];  // Output the result in hexadecimal
  std::cout << "\n";
}