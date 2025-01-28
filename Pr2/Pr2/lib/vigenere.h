#ifndef VIGENERE_H
#define VIGENERE_H

#include <string>

std::string preprocessText(const std::string& text);
std::string extendKey(const std::string& key, int textLength);
std::string encryptVigenere(const std::string& plaintext, const std::string& key);
std::string decryptVigenere(const std::string& ciphertext, const std::string& key);

#endif // VIGENERE_H
