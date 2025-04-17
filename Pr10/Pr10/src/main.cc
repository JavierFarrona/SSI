#include "../lib/elGammal.h"

int main() {
    // Entradas desde teclado
    int p, a, b, dA, dB, m, Gx, Gy;
    cout << "Introduce el valor de p: "; cin >> p;
    cout << "Introduce el valor de a: "; cin >> a;
    cout << "Introduce el valor de b: "; cin >> b;
    cout << "Introduce las coordenadas del punto G (x y): "; cin >> Gx >> Gy;
    cout << "Introduce la clave privada de A (dA): "; cin >> dA;
    cout << "Introduce la clave privada de B (dB): "; cin >> dB;
    cout << "Introduce el mensaje original (entero): "; cin >> m;

    Point G(Gx, Gy);

    // 1. Generar puntos de la curva
    vector<Point> puntos = generate_curve_points(a, b, p);
    cout << "\nPuntos de la curva elíptica:\n";
    for (const auto& pt : puntos) {
        pt.print(); cout << " ";
    }
    cout << "\n";

    // 2. Claves públicas
    Point dAG = scalar_mult(dA, G, a, p);
    Point dBG = scalar_mult(dB, G, a, p);

    cout << "Clave pública de A (dA*G): ";
    dAG.print(); cout << "\n";

    cout << "Clave pública de B (dB*G): ";
    dBG.print(); cout << "\n";

    // Mostrar más múltiplos de G si se desea
    cout << "4(G): "; scalar_mult(4, G, a, p).print(); cout << "\n";
    cout << "5(G): "; scalar_mult(5, G, a, p).print(); cout << "\n";

    // 3. Clave secreta compartida
    Point S_A = scalar_mult(dA, dBG, a, p);
    Point S_B = scalar_mult(dB, dAG, a, p);

    cout << "Clave secreta compartida por A: ";
    S_A.print(); cout << "\n";

    cout << "Clave secreta compartida por B: ";
    S_B.print(); cout << "\n";

    // 4. Codificación del mensaje como punto en la curva
    int M = 4;
    int h = p / M;
    Point Qm;
    for (int j = 0; j < h; ++j) {
        int x = (m * h + j) % p;
        for (int y = 0; y < p; ++y) {
            if (is_on_curve(x, y, a, b, p)) {
                Qm = Point(x, y);
                goto found;
            }
        }
    }
found:
    cout << "Mensaje codificado como punto Qm: ";
    Qm.print(); cout << "\n";
    cout << "M = " << M << ", h = " << h << "\n";

    // 5. Cifrado ElGamal
    Point parte1 = point_add(Qm, scalar_mult(dA, dBG, a, p), a, p);
    Point parte2 = dAG;

    cout << "Mensaje cifrado enviado (parte1 = Qm + dA*(dBG)): ";
    parte1.print(); cout << "\n";

    cout << "Mensaje cifrado enviado (parte2 = dAG): ";
    parte2.print(); cout << "\n";

    return 0;
}
