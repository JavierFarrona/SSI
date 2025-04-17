#include "../lib/elGammal.h"


// Función para calcular el inverso modular de k módulo mod
int mod_inv(int k, int mod) {
    k = k % mod;
    for (int x = 1; x < mod; ++x)
        if ((k * x) % mod == 1)
            return x;
    return -1; // No existe inverso
}

// Suma de dos puntos en la curva elíptica
Point point_add(Point P, Point Q, int a, int p) {
    if (P.at_infinity) return Q;
    if (Q.at_infinity) return P;
    if (P.x == Q.x && (P.y != Q.y || P.y == 0)) return Point(); // Punto en el infinito

    int lambda;
    if (P == Q) {
        int num = (3 * P.x * P.x + a) % p;
        int den = mod_inv(2 * P.y, p);
        lambda = (num * den) % p;
    } else {
        int num = (Q.y - P.y + p) % p;
        int den = mod_inv((Q.x - P.x + p) % p, p);
        lambda = (num * den) % p;
    }

    int x3 = (lambda * lambda - P.x - Q.x + p) % p;
    int y3 = (lambda * (P.x - x3) - P.y + p) % p;

    return Point((x3 + p) % p, (y3 + p) % p);
}

// Multiplicación escalar de un punto
// (DIFFIE HELLMAN ELIPTICO)
Point scalar_mult(int k, Point P, int a, int p) {
    Point R;
    while (k > 0) {
        if (k % 2 == 1) R = point_add(R, P, a, p);
        P = point_add(P, P, a, p);
        k /= 2;
    }
    return R;
}

// Verifica si un punto pertenece a la curva
bool is_on_curve(int x, int y, int a, int b, int p) {
    return (y * y) % p == (x * x * x + a * x + b) % p;
}

// Genera todos los puntos válidos sobre la curva
vector<Point> generate_curve_points(int a, int b, int p) {
    vector<Point> points;
    for (int x = 0; x < p; ++x) {
        for (int y = 0; y < p; ++y) {
            if (is_on_curve(x, y, a, b, p)) {
                points.emplace_back(x, y);
            }
        }
    }
    return points;
}