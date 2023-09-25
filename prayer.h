#ifndef PRAYER
#define PRAYER
#define INT(x) ((int) (x))
#define SIN(x) sin((x) * PI/180)
#define COS(x) cos((x) * PI/180)
#define TAN(x) tan((x) * PI/180)
#define ACOT(x) (atan(1.0/(x))) * 180/PI
#define ACOS(x) (acos(x)) * 180/PI
#define ABS(x) ((x < 0)?(-(x)):(x))
#define PI 3.141592653589793238462643383279502884197
#define C_HA(x) ACOS((SIN(x) - SIN(LAT) \
	     * SIN(DELTA)) / (COS(LAT) * COS(DELTA)))

#include <iostream>
#include <cmath>
#include <ctime>

typedef double LF;
struct prayers {
    std::string name;
    int time;
};

class PrayerApp {
private:
    // Data
    double H, m, s, Z, h, SF, LAT, LONG, FAJR_ANGLE, ISHA_ANGLE;

    // BSS
    std::string prayer_name, command;
    double Y, M, D, B, A, T, JD, U, L0, TT,
    ET1000, ET, DELTA, SA_FAJR, SA_SUNRISE, SA_ASR,
    SA_MAGHRIB, SA_ISHA, FAJR, SUNRISE, ZUHR, ASR, MAGHRIB,
    ISHA, HA_FAJR, HA_SUNRISE, HA_ASR, HA_MAGHRIB, HA_ISHA;
    int time_in_minutes;
    prayers prayer[6];

public:
    PrayerApp(LF H, LF m, LF s, LF Z,
	      LF h, LF SF, LF LAT, LF LONG,
	      LF FAJR_ANGLE, LF ISHA_ANGLE) {
	this->H = H, this->m = m, this->s = s;
	this->Z = Z, this->h = h, this->SF = SF;
	this->LAT = LAT, this->LONG = LONG;
	this->FAJR_ANGLE = FAJR_ANGLE;
	this->ISHA_ANGLE = ISHA_ANGLE;
    }
    void TimeSync() {
	time_t ttime = time(0);
	tm* current_time = localtime(&ttime);
	Y = 1900 + current_time->tm_year;
	M = 1 + current_time->tm_mon;
	D = current_time->tm_mday;
	if(INT(M) <= 2) {
	    M += 12;
	    Y -= 1;
	}
	A = INT(Y / 100);
	B = 2 + INT(A / 4) - A;
	time_in_minutes = current_time->tm_min + current_time->tm_hour * 60;
    }
    void TimeEquation() {
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
    }
    void SunDeclination() {
	T = 2 * PI * (JD - 2451545) / 365.25;
	DELTA = 0.37877 + 23.264 * SIN(57.297 * T - 79.547) + 0.3812 * 
	    SIN(2 * 57.297 * T - 82.682) + 0.17132 * SIN(3 * 57.297 * T - 59.722);
    }
    void ConvertDataToJulianDays() {
	JD = 1720994.5 + INT(365.25 * Y) + INT(30.6001 * (M + 1))
	    + B + D + (H * 3600 + m * 60 + s) / 86400.0 - Z / 24.0;
    }
    void TransitTime() {
	TT = 12 + Z - (LONG / 15) - (ET / 60);
    }
    void SunAltitude() {
	SA_FAJR = -(FAJR_ANGLE);
	SA_SUNRISE = -0.8333 - (0.0347*std::sqrt(h));
	SA_ASR = ACOT(SF + TAN(ABS(DELTA - LAT)));
	SA_MAGHRIB = SA_SUNRISE;
	SA_ISHA = -(ISHA_ANGLE);
    }
    void HourAngle() {
	HA_FAJR = C_HA(SA_FAJR);
	HA_SUNRISE = HA_MAGHRIB = C_HA(SA_SUNRISE);
	HA_ASR = C_HA(SA_ASR);
	HA_ISHA = C_HA(SA_ISHA);
    }
    void PrayerTimes() {
	FAJR    = (TT - HA_FAJR / 15) * 60;
	SUNRISE = (TT - HA_SUNRISE / 15) * 60;
	ZUHR    = (TT + (1.0 / 60)) * 60;
	ASR     = (TT + HA_ASR / 15) * 60;
	MAGHRIB = (TT + HA_MAGHRIB / 15) * 60;
	ISHA    = (TT + HA_ISHA / 15) * 60;
    }
    void PrayersData() {
	prayer[0] = {"Fajr", (int)FAJR};
	prayer[1] = {"Sunrise", (int)SUNRISE};
	prayer[2] = {"Zuhr", (int)ZUHR};
	prayer[3] = {"Asr", (int)ASR};
	prayer[4] = {"Maghrib", (int)MAGHRIB};
	prayer[5] = {"Isha", (int)ISHA};
    }
    int GetCurrentTime() {
	return time_in_minutes;
    }
    prayers* iterator() {
	return prayer;
    }
};

#endif // !PRAYER
