#include <cmath>
#include <iostream>
#define INT(x) ((int) (x))
#define PI 3.141592653589793238462643383279502884197

using namespace std;

int main (int argc, char *argv[]) {
    // Convert date to Julian days
    double Y, M, D, H, m, s, B, A, Z, T, JD, U, L0, 
    ET1000, ET, DELTA, SF, LONG, LAT, FAJR_ANGLE, ISHA_ANGLE;
    Y = 2023;
    M = 9;
    D = 23;
    H = 12;
    m = 1;
    s = 1;
    LAT = 29.8403;
    LONG = 31.2982;
    FAJR_ANGLE = 19.5;
    ISHA_ANGLE = 17.5;

    if(INT(M) <= 2) {
        M += 12;
        Y -= 1;
    }
    A = INT(Y / 100);
    B = 2 + INT(A / 4) - A;
    Z = +2;

    JD = 1720994.5 + INT(365.25 * Y) + INT(30.6001 * (M + 1))
        + B + D + (H * 3600 + m * 60 + s) / 86400.0 - Z / 24.0;

    // Calculate Sun declination
    T = 2 * PI * (JD - 2451545) / 365.25;
    DELTA = 0.37877 + 23.264 * sin(57.297 * T - 79.547) + 0.3812 * 
        sin(2 * 57.297 * T - 82.682) + 0.17132 * sin(3 * 57.297 * T - 59.722);

    // Calculate equation of time
    U = (JD - 2451545) / 36525;
    L0 = 280.46607 + 36000.7698 * U;
    ET1000 = -(1789 + 237*U) * sin(L0) -
	(7146 - 62*U) * cos(L0) + 
	(9934 - 14*U) * sin(2*L0) - 
	(29 + 5*U) * cos(2*L0) +
	(74 + 10*U) * sin(3*L0) +
	(320 - 4*U) * cos(3*L0) -
	212 * sin(4*L0);
    ET = ET1000 / 1000;
}
