#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long modexp(long long base, long long exp, long long mod);
bool esPrimo(int n);
int mcdExtendido(int a, int b, int &x, int &y);
int letraANum(char c);
char numALetra(int n);
vector<int> codificarMensaje(string mensaje, int n);