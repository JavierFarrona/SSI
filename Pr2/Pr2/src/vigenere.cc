#include "vigenere.h"
#include <cctype>

std::string preprocessText(const std::string& text) {
    std::string processed;
    for (char c : text) {
        if (std::isalpha(c)) {
            processed += std::toupper(c); // Convertir a mayúsculas
        }
    }
    return processed;
}

std::string extendKey(const std::string& key, int textLength) {
    std::string extendedKey;
    int keyLength = key.length();
    for (int i = 0; i < textLength; ++i) {
        extendedKey += key[i % keyLength];
    }
    return extendedKey;
}

std::string encryptVigenere(const std::string& plaintext, const std::string& key) {
    std::string ciphertext;
    for (size_t i = 0; i < plaintext.length(); ++i) {
        char p = plaintext[i];
        char k = key[i];
        char c = ((p - 'A') + (k - 'A')) % 26 + 'A'; // Cifrado mod 26
        ciphertext += c;
    }
    return ciphertext;
}

std::string decryptVigenere(const std::string& ciphertext, const std::string& key) {
    std::string decryptedText;
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        char c = ciphertext[i];
        char k = key[i];
        char p = ((c - 'A') - (k - 'A') + 26) % 26 + 'A'; // Descifrado mod 26
        decryptedText += p;
    }
    return decryptedText;
}
