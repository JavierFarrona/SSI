#pragma once
#include <iostream>
#include <string>
#include <vector>

class AES
{
    std::vector<int> S_Caja;
    std::vector<std::vector<int>> Rcon;

    std::vector<std::vector<int>> clave_extendida;
    std::vector<std::vector<int>> clave_original;
    std::vector<std::vector<int>> mensaje;

    std::vector<std::vector<int>> resultado;

public:
    AES();
    ~AES(){};

    void cifrar();

    void introducir_datos(std::vector<std::vector<int>> clave, std::vector<std::vector<int>> entrada);
    void write();

private:
    void expandir_clave();
    void addRoundKey(int iteracion);
    void SubBytes();
    void ShiftRow();
    void MixColumn();
};