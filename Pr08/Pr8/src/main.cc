#include <iostream>
#include "../lib/diffie.h"

int main() {
    diffie_hellman(13, 4, 5, 2);
    diffie_hellman(43, 23, 25, 33);
    diffie_hellman(113, 43, 54, 71);

    //diffie_hellman(13, 10, 15, 5);

    return 0;
}