#include "vigenere.h"

#include <cctype>

/**
 * @brief Preprocess the input text by converting all alphabetic characters to uppercase.
 * 
 * @param text The input text to preprocess.
 * @return std::string The preprocessed text with only uppercase alphabetic characters.
 */
std::string preprocessText(const std::string& text) {
  std::string processed;
  for (char c : text) {
    if (std::isalpha(c)) {
      processed += std::toupper(c);  // Convert to uppercase
    }
  }
  return processed;
}

/**
 * @brief Extend the key to match the length of the text.
 * 
 * @param key The original key.
 * @param textLength The length of the text to match.
 * @return std::string The extended key.
 */
std::string extendKey(const std::string& key, int textLength) {
  std::string extendedKey;
  int keyLength = key.length();
  for (int i = 0; i < textLength; ++i) {
    extendedKey += key[i % keyLength];  // Repeat the key as needed
  }
  return extendedKey;
}

/**
 * @brief Encrypt the plaintext using the Vigenère cipher.
 * 
 * @param plaintext The text to encrypt.
 * @param key The key to use for encryption.
 * @return std::string The encrypted ciphertext.
 */
std::string encryptVigenere(const std::string& plaintext, const std::string& key) {
  std::string ciphertext;
  for (size_t i = 0; i < plaintext.length(); ++i) {
    char p = plaintext[i];
    char k = key[i];
    char c = ((p - 'A') + (k - 'A')) % 26 + 'A';  // Encryption mod 26
    ciphertext += c;
  }
  return ciphertext;
}

/**
 * @brief Decrypt the ciphertext using the Vigenère cipher.
 * 
 * @param ciphertext The text to decrypt.
 * @param key The key to use for decryption.
 * @return std::string The decrypted plaintext.
 */
std::string decryptVigenere(const std::string& ciphertext, const std::string& key) {
  std::string decryptedText;
  for (size_t i = 0; i < ciphertext.length(); ++i) {
    char c = ciphertext[i];
    char k = key[i];
    char p = ((c - 'A') - (k - 'A') + 26) % 26 + 'A';  // Decryption mod 26
    decryptedText += p;
  }
  return decryptedText;
}
