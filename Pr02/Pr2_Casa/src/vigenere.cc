#include "vigenere.h"  // Incluye el archivo de cabecera para las funciones de Vigenère

#include <cctype>  // Incluye funciones para manipulación de caracteres

/**
 * @brief Preprocess the input text by converting all alphabetic characters to
 * uppercase.
 *
 * @param text The input text to preprocess.
 * @return std::string The preprocessed text with only uppercase alphabetic
 * characters.
 */
std::string preprocessText(const std::string& text) {
  std::string processed;    // Cadena para almacenar el texto procesado
  for (char c : text) {     // Itera sobre cada carácter en el texto
    if (std::isalpha(c)) {  // Verifica si el carácter es alfabético
      processed += std::toupper(
          c);  // Convierte a mayúscula y añade a la cadena procesada
    }
  }
  return processed;  // Devuelve el texto procesado
}

/**
 * @brief Extend the key to match the length of the text.
 *
 * @param key The original key.
 * @param textLength The length of the text to match.
 * @return std::string The extended key.
 */
std::string extendKey(const std::string& key, int textLength) {
  std::string extendedKey;       // Cadena para almacenar la clave extendida
  int keyLength = key.length();  // Longitud de la clave original
  for (int i = 0; i < textLength;
       ++i) {  // Itera hasta que la longitud de la clave extendida coincida con
               // la del texto
    extendedKey += key[i % keyLength];  // Repite la clave según sea necesario
  }
  return extendedKey;  // Devuelve la clave extendida
}

/**
 * @brief Encrypt the plaintext using the Vigenère cipher.
 *
 * @param plaintext The text to encrypt.
 * @param key The key to use for encryption.
 * @return std::string The encrypted ciphertext.
 */
std::string encryptVigenere(const std::string& plaintext,
                            const std::string& key) {
  std::string ciphertext;  // Cadena para almacenar el texto cifrado
  for (size_t i = 0; i < plaintext.length();
       ++i) {               // Itera sobre cada carácter en el texto plano
    char p = plaintext[i];  // Carácter del texto plano
    char k = key[i];        // Carácter correspondiente de la clave
    char c = ((p - 'A') + (k - 'A')) % 26 +
             'A';  // Cifra el carácter usando la fórmula del cifrado Vigenère
    ciphertext += c;  // Añade el carácter cifrado al texto cifrado
  }
  return ciphertext;  // Devuelve el texto cifrado
}

/**
 * @brief Decrypt the ciphertext using the Vigenère cipher.
 *
 * @param ciphertext The text to decrypt.
 * @param key The key to use for decryption.
 * @return std::string The decrypted plaintext.
 */
std::string decryptVigenere(const std::string& ciphertext,
                            const std::string& key) {
  std::string decryptedText;  // Cadena para almacenar el texto descifrado
  for (size_t i = 0; i < ciphertext.length();
       ++i) {                // Itera sobre cada carácter en el texto cifrado
    char c = ciphertext[i];  // Carácter del texto cifrado
    char k = key[i];         // Carácter correspondiente de la clave
    char p =
        ((c - 'A') - (k - 'A') + 26) % 26 +
        'A';  // Descifra el carácter usando la fórmula del cifrado Vigenère
    decryptedText += p;  // Añade el carácter descifrado al texto descifrado
  }
  return decryptedText;  // Devuelve el texto descifrado
}
