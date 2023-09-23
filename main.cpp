#include <cmath>
#include <iostream>
#define INT(x) ((int) (x))
#define PI 3.141592653589793238462643383279502884197

using namespace std;

int main (int argc, char *argv[]) {
    // Convert date to Julian days
    double JD, U, L0, ET1000, Y, M, D, H, m, s, B, A, Z, T, DELTA;
    Y = 2023;
    M = 9;
    D = 23;
    H = 12;
    m = 1;
    s = 1;

    if(INT(M) <= 2) {
        M += 12;
        Y -= 1;
    }
    A = INT(Y / 100);
    B = 2 + INT(A / 4) - A;
    Z = +2;

    JD = 1720994.5 + INT(365.25 * Y) + INT(30.6001 * (M + 1))
        + B + D + (H * 3600 + m * 60 + s) / 86400.0 - Z / 24.0;
    printf("%0.20lf", JD);

    // Calculate Sun declination
    T = 2 * PI * (JD - 2451545) / 365.25;
    DELTA = 0.37877 + 23.264 * sin(57.297 * T - 79.547) + 0.3812 * 
        sin(2 * 57.297 * T - 82.682) + 0.17132 * sin(3 * 57.297 * T - 59.722);
}
