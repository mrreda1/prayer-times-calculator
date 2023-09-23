#include <iostream>
#define INT(x) ((int) x)

int main (int argc, char *argv[]) {
    //Convert date to Julian days
    int Y, M, D, H, m, s, B, A, JD, Z;
    Y = 2023;
    M = 9;
    D = 23;
    H = 12;
    m = 1;
    s = 1;

    if(M <= 2) {
        M += 12;
        Y -= 1;
    }
    A = INT(Y / 100);
    B = 2 + INT(A / 4) - A;
    Z = +3;

    JD = 1720994.5 + INT(365.25*Y) + INT(30.6001 * (M + 1))
        + B + D + ((H*3600 + m*60 + s) / 86400) - (Z / 24);
}
