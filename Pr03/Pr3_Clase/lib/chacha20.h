#include <array>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

#define ROTL(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d)                                                       \
   (a += b, d ^= a, d = ROTL(d, 16), \
   c += d, b ^= c, b = ROTL(b, 12), \
   a += b, d ^= a, d = ROTL(d, 8), \
   c += d, b ^= c, b = ROTL(b, 7))

#define ROUNDS 20

void printState_20(const uint32_t state[16]);

void chacha_block_20(uint32_t out[16], const uint32_t in[16]);

void xor_buffers(uint32_t* out, const uint32_t* in1, const uint32_t* in2, size_t length);
