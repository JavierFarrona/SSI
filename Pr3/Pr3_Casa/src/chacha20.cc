#include "../lib/chacha20.h"

void printState_20(const uint32_t state[16]) {
  for (int i = 0; i < 16; ++i) {
    if (i % 4 == 0) cout << endl;
    cout << hex << setw(8) << setfill('0') << state[i] << " ";
  }
  cout << dec << endl;
}

void chacha_block_20(uint32_t out[16], const uint32_t in[16]) {
  int i;
  uint32_t x[16];
  memcpy(x, in, sizeof(x));

  // 10 loops x 2 rounds/loop = 20 rounds
  for (i = 0; i < ROUNDS; i += 2) {
    // Odd round
    QR(x[0], x[4], x[8], x[12]);   // column 0
    QR(x[1], x[5], x[9], x[13]);   // column 1
    QR(x[2], x[6], x[10], x[14]);  // column 2
    QR(x[3], x[7], x[11], x[15]);  // column 3

    // Even round
    QR(x[0], x[5], x[10], x[15]);  // diagonal 1
    QR(x[1], x[6], x[11], x[12]);  // diagonal 2
    QR(x[2], x[7], x[8], x[13]);   // diagonal 3
    QR(x[3], x[4], x[9], x[14]);   // diagonal 4
  }

  for (i = 0; i < 16; ++i) out[i] = x[i] + in[i];

  // Print the final state after 20 iterations
  cout << "\n\nEstado final tras las 20 iteraciones:";
  printState_20(x);
}

void xor_buffers(uint32_t* out, const uint32_t* in1, const uint32_t* in2, size_t length) {
  for (size_t i = 0; i < length; ++i) {
    out[i] = in1[i] ^ in2[i];
  }
}
