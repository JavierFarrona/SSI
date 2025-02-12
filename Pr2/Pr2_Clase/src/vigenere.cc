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
 * @brief Cifra el texto plano usando el cifrado Vigenère.
 *
 * @param plaintext El texto a cifrar.
 * @param key La clave a usar para el cifrado.
 * @return std::string El texto cifrado.
 */
std::string encryptVigenere(const std::string& plaintext,
                            const std::string& key) {
  std::string ciphertext;  // Cadena para almacenar el texto cifrado
  for (size_t i = 0; i < plaintext.length();
       ++i) {               // Itera sobre cada carácter en el texto plano
    char p = plaintext[i];  // Carácter del texto plano
    char k = key[i];        // Carácter correspondiente de la clave
    char c = ((p - 'A') - (k - 'A') + 26) % 26 +
             'A';  // Cifra el carácter usando la fórmula del cifrado Vigenère
                   // con resta
    ciphertext += c;  // Añade el carácter cifrado al texto cifrado
  }
  return ciphertext;  // Devuelve el texto cifrado
}

/**
 * @brief Descifra el texto cifrado usando el cifrado Vigenère.
 *
 * @param ciphertext El texto a descifrar.
 * @param key La clave a usar para el descifrado.
 * @return std::string El texto descifrado.
 */
std::string decryptVigenere(const std::string& ciphertext,
                            const std::string& key) {
  std::string decryptedText;  // Cadena para almacenar el texto descifrado
  for (size_t i = 0; i < ciphertext.length();
       ++i) {                // Itera sobre cada carácter en el texto cifrado
    char c = ciphertext[i];  // Carácter del texto cifrado
    char k = key[i];         // Carácter correspondiente de la clave
    char p = ((c - 'A') + (k - 'A')) % 26 +
             'A';        // Descifra el carácter usando la fórmula del cifrado
                         // Vigenère con suma
    decryptedText += p;  // Añade el carácter descifrado al texto descifrado
  }
  return decryptedText;  // Devuelve el texto descifrado
}
