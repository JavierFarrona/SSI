#include "../lib/aes.h"
#include <sstream>

int main()
{
    //  Clave y texto por defecto (PDF)
    std::vector<std::vector<int>> clave_;
    std::vector<std::vector<int>> texto_;

    clave_ = {
        {0x00, 0x04, 0x08, 0x0c},
        {0x01, 0x05, 0x09, 0x0d},
        {0x02, 0x06, 0x0a, 0x0e},
        {0x03, 0x07, 0x0b, 0x0f}};

    texto_ = {
        {0x00, 0x44, 0x88, 0xcc},
        {0x11, 0x55, 0x99, 0xdd},
        {0x22, 0x66, 0xaa, 0xee},
        {0x33, 0x77, 0xbb, 0xff}};

    //   ------------------------------------

    //  Clave y texto pedir por teclado.
    std::vector<std::vector<int>> clave;
    std::vector<std::vector<int>> texto;

    for (int i = 0; i < 4; i++)
    {
        clave.resize(4);
        texto.resize(4);
        for (int j = 0; j < 4; j++)
        {
            clave[i].resize(4);
            texto[i].resize(4);
        }
    }

    //   ------------------------------------

    AES cifrado;
    bool salir = false;
    int operacion = 0;
    std::string entrada;
    while (!salir)
    {
        std::cout << "------------------------------------";
        std::cout << "\n¿Qué desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Valores por defecto.\n";
        std::cout << "[2] Introducir valores.\n";
        std::cin >> operacion;
        std::cout << "------------------------------------\n";

        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:

            std::cout << "Clave: ";
            for (int j = 0; j < clave_.size(); j++)
                for (int i = 0; i < clave_[j].size(); i++)
                    std::cout << std::hex << clave_[i][j];

            std::cout << "\nBloque de texto: ";
            for (int j = 0; j < texto_.size(); j++)
                for (int i = 0; i < texto_[j].size(); i++)
                    std::cout << std::hex << texto_[i][j];

            cifrado.introducir_datos(clave_, texto_);
            cifrado.cifrar();
            cifrado.write();
            break;
        case 2:
            std::cout << "------------------------------------";
            std::cout << "\nIntroduzca la clave:\n";
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    std::cin >> entrada;
                    std::istringstream(entrada) >> std::hex >> clave[i][j];
                }
            }
            std::cout << "------------------------------------";
            std::cout << "\nIntroduzca el texto:\n";
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    std::cin >> entrada;
                    std::istringstream(entrada) >> std::hex >> texto[i][j];
                }
            }
            std::cout << "------------------------------------";

            cifrado.introducir_datos(clave, texto);
            cifrado.cifrar();
            cifrado.write();
            break;
        default:
            std::cout << "\nOperación incorrecta.\n";
        }
    }
    return 0;
}
