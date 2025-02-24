#include "../lib/chacha20.h"

int main() {
  // Example input values
  uint32_t input[16] = {
      0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, 0x03020100, 0x07060504,
      0x0b0a0908, 0x0f0e0d0c, 0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
      0x00000001, 0x09000000, 0x4a000000, 0x00000000,
  };

  uint32_t keystream[16];
  uint32_t ciphertext[16];
  uint32_t decrypted[16];

  cout << "Estado inicial:";
  printState_20(input);

  // Generate keystream for encryption
  chacha_block_20(keystream, input);

  // Encrypt
  xor_buffers(ciphertext, input, keystream, 16);

  cout << "\n\nEstado de salida del generador (cifrado):";
  printState_20(ciphertext);

  // Generate keystream for decryption (same as encryption)
  chacha_block_20(keystream, input);

  // Decrypt
  xor_buffers(decrypted, ciphertext, keystream, 16);

  cout << "\n\nEstado de salida del generador (descifrado):";
  printState_20(decrypted);

  return 0;
}
