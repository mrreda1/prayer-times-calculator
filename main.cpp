#include <cmath>
#include <iostream>

#define INT(x) ((int) (x))
#define PI 3.141592653589793238462643383279502884197
#define SIN(x) sin((x) * PI/180)
#define COS(x) cos((x) * PI/180)
#define TAN(x) tan((x) * PI/180)
#define ACOT(x) acot((x) * PI/180)

int main (int argc, char *argv[]) {
    double Y, M, D, H, m, s, B, A, Z, T, JD, U, L0, h, TT,
    ET1000, ET, DELTA, SF, LONG, LAT, FAJR_ANGLE, ISHA_ANGLE;
    Y = 2023;
    M = 9;
    D = 24;
    H = 12;
    m = 0;
    s = 0;
    Z = +3;
    h = 8;
    SF = 1;
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

    // Convert date to Julian days
    JD = 1720994.5 + INT(365.25 * Y) + INT(30.6001 * (M + 1))
        + B + D + (H * 3600 + m * 60 + s) / 86400.0 - Z / 24.0;

    // Calculate Sun declination
    T = 2 * PI * (JD - 2451545) / 365.25;
    DELTA = 0.37877 + 23.264 * SIN(57.297 * T - 79.547) + 0.3812 * 
        SIN(2 * 57.297 * T - 82.682) + 0.17132 * SIN(3 * 57.297 * T - 59.722);

    // Calculate equation of time
    U = (JD - 2451545) / 36525;
    L0 = 280.46607 + 36000.7698 * U;
    ET1000 = -(1789 + 237*U) * SIN(L0) -
	(7146 - 62*U) * COS(L0) + 
	(9934 - 14*U) * SIN(2*L0) - 
	(29 + 5*U) * COS(2*L0) +
	(74 + 10*U) * SIN(3*L0) +
	(320 - 4*U) * COS(3*L0) -
	212 * SIN(4*L0);
    ET = ET1000 / 1000;
    
    // Calculate transit time
    TT = 12 + Z - (LONG / 15) - (ET / 60);
}
