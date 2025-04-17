#include "../lib/chacha20.h"
#include <random>

int main() {
  // Example input values
  uint32_t input[16] = {
      0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
      0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
      0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
      0x00000001, 0x09000000, 0x4a000000, 0x00000000,
  };

  uint32_t input_2[16] = {
      0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
      0x97a3990e, 0x97a3990e, 0xad6b42e2, 0x242d312f,
      0x2b76c2d9, 0xd7f45e53, 0xa975178e, 0xa5683a45,
      0xFFFFFFFF, 0xacde9eb6, 0x5044ee73, 0x8e9afad3,
  };

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> dis(0, 0xFFFFFFFF);
  uint32_t random_hex = dis(gen);

  input_2[12] = random_hex;

  uint32_t keystream[16];
  uint32_t keystream_2[16];
  uint32_t ciphertext[16];
  uint32_t ciphertext_2[16];

  cout << "Estado inicial:";
  printState_20(input);

  // Generate keystream for encryption
  chacha_block_20(keystream, input);

  // Encrypt
  xor_buffers(ciphertext, input, keystream, 16);

  cout << "\n\nEstado de salida del generador (cifrado):";
  printState_20(ciphertext);



  cout << "\n\n\nEstado inicial:";
  printState_20(input_2);

  // Generate keystream for encryption
  chacha_block_20(keystream_2, input_2);

  // Encrypt
  xor_buffers(ciphertext_2, input_2, keystream_2, 16);

  cout << "\n\nEstado de salida del generador (cifrado):";
  printState_20(ciphertext_2);

  return 0;
}
