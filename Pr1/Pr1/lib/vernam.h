#ifndef CIPHER_H
#define CIPHER_H

#include <string>

const int ASCII_BITS = 8;

std::string textToBinary(const std::string& text);
std::string binaryToText(const std::string& binary);
std::string generateRandomKey(size_t length);
std::string xorOperation(const std::string& binary1,
                         const std::string& binary2);

#endif  // CIPHER_H