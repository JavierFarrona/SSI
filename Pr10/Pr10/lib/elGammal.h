#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
using namespace std;

// Estructura para representar un punto en la curva
struct Point {
    int x, y;
    bool at_infinity;

    Point() : x(0), y(0), at_infinity(true) {}  // Punto en el infinito
    Point(int x, int y) : x(x), y(y), at_infinity(false) {}

    bool operator==(const Point& other) const {
        return (at_infinity && other.at_infinity) || (x == other.x && y == other.y);
    }

    void print() const {
        if (at_infinity) cout << "Infinity";
        else cout << "(" << x << "," << y << ")";
    }
};

// Función para calcular el inverso modular de k módulo mod
int mod_inv(int k, int mod);

// Suma de dos puntos en la curva elíptica
Point point_add(Point P, Point Q, int a, int p) ;

// Multiplicación escalar de un punto
// (DIFFIE HELLMAN ELIPTICO)
Point scalar_mult(int k, Point P, int a, int p);

// Verifica si un punto pertenece a la curva
bool is_on_curve(int x, int y, int a, int b, int p);

vector<Point> generate_curve_points(int a, int b, int p);