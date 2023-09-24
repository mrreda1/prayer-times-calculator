#include <iostream>
#include <cmath>
#include <ctime>

#define INT(x) ((int) (x))
#define PI 3.141592653589793238462643383279502884197
#define SIN(x) sin((x) * PI/180)
#define COS(x) cos((x) * PI/180)
#define TAN(x) tan((x) * PI/180)
#define ACOT(x) (atan(1.0/(x))) * 180/PI
#define ACOS(x) (acos(x)) * 180/PI
#define ABS(x) ((x < 0)?(-(x)):((x)))

int main (int argc, char *argv[]) {
    double Y, M, D, H, m, s, B, A, Z, T, JD, U, L0, h, TT,
    ET1000, ET, DELTA, SF, LONG, LAT, FAJR_ANGLE, ISHA_ANGLE;

    // Time sync
    time_t ttime = time(0);
    tm* current_time = localtime(&ttime);
    Y = 1900 + current_time->tm_year;
    M = 1 + current_time->tm_mon;
    D = current_time->tm_mday;

    H = 12, m = 0, s = 0;
    Z = +3, h = 23;
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

    
    double SA_FAJR, SA_SUNRISE, SA_ASR, SA_MAGHRIB, SA_ISHA,
	FAJR, SUNRISE, ZUHR, ASR, MAGHRIB, ISHA,
	HA_FAJR, HA_SUNRISE, HA_ASR, HA_MAGHRIB, HA_ISHA;

    // Calculate Sun altitude for each prayer times
    SA_FAJR = -(FAJR_ANGLE);
    SA_SUNRISE = -0.8333 - (0.0347*std::sqrt(h));
    SA_ASR = ACOT(SF + TAN(ABS(DELTA - LAT)));
    SA_MAGHRIB = SA_SUNRISE;
    SA_ISHA = -(ISHA_ANGLE);

    // Calculate hour angle
    HA_FAJR = ACOS((SIN(SA_FAJR) - SIN(LAT) * SIN(DELTA)) / (COS(LAT) * COS(DELTA)));
    HA_SUNRISE = HA_MAGHRIB = ACOS((SIN(SA_SUNRISE) - SIN(LAT) * SIN(DELTA)) / (COS(LAT) * COS(DELTA)));
    HA_ASR = ACOS((SIN(SA_ASR) - SIN(LAT) * SIN(DELTA)) / (COS(LAT) * COS(DELTA)));
    HA_ISHA = ACOS((SIN(SA_ISHA) - SIN(LAT) * SIN(DELTA)) / (COS(LAT) * COS(DELTA)));

    // Calculate prayer times
    FAJR    = TT - HA_FAJR / 15;
    SUNRISE = TT - HA_SUNRISE / 15;
    ZUHR    = TT + (1.0 / 60);
    ASR     = TT + HA_ASR / 15;
    MAGHRIB = TT + HA_MAGHRIB / 15;
    ISHA    = TT + HA_ISHA / 15;


    printf("FAJR: %0.2d:%0.2d\n", INT(FAJR), INT(FAJR * 60) % 60);
    printf("SUNRISE: %0.2d:%0.2d\n", INT(SUNRISE), INT(SUNRISE * 60) % 60);
    printf("ZUHR: %0.2d:%0.2d\n", INT(ZUHR), INT(ZUHR * 60) % 60);
    printf("ASR: %0.2d:%0.2d\n", INT(ASR), INT(ASR * 60) % 60);
    printf("MAGHRIB: %0.2d:%0.2d\n", INT(MAGHRIB), INT(MAGHRIB * 60) % 60);
    printf("ISHA: %0.2d:%0.2d\n", INT(ISHA), INT(ISHA * 60) % 60);
}
