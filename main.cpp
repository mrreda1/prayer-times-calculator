#include <iostream>
#include "prayer.hpp"

int main (void) {
    // Variables
    const int Shafii = 1, Hanafi = 2;
    prayers* prayer;
    int timezone;
    double elevation_above_sea_level_in_meter,
    latitude, longitude, fajr_angle, isha_angle;

    // Parameters (custom)
    timezone = +2;
    elevation_above_sea_level_in_meter = 23;
    latitude = 29.8403;
    longitude = 31.2982;
    fajr_angle = 19.5;
    isha_angle = 17.5;

    PrayerApp app(timezone, elevation_above_sea_level_in_meter,
		  Shafii, latitude, longitude, fajr_angle, isha_angle);

    // BlackBox
    app.TimeSync();
    app.ConvertDataToJulianDays();
    app.SunDeclination();
    app.TimeEquation();
    app.TransitTime();
    app.SunAltitude();
    app.HourAngle();
    app.PrayerTimes();
    app.PrayersData();
    prayer = app.iterator();
  
    // Print prayers' data
    for(int i = 0; i < 6; i++)
	printf("%s: %0.2d:%0.2d\n", prayer[i].name.c_str(), prayer[i].time/60, prayer[i].time%60);
}
