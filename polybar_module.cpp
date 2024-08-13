#include <iostream>
#include "prayer.hpp"

int main (void) {
    // Variables
    const int Shafii = 1, Hanafi = 2;
    std::string prayer_name, command;
    prayers* prayer;
    int time_in_minutes, remaining, timezone, i;
    double elevation_above_sea_level_in_meter,
    latitude, longitude, fajr_angle, isha_angle;

    // Parameters (custom)
    timezone = +3;
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
    time_in_minutes = app.GetCurrentTime();

    // Find next prayer
    for(i = 0; i < 6; i++) {
	if(prayer[i].time >= time_in_minutes) {
	    remaining = prayer[i].time - time_in_minutes;
	    prayer_name = prayer[i].name;
	    break;
	}
    }

    // If after Isha time
    if(i == 6) {
	remaining = prayer[0].time + 24 * 60 - time_in_minutes;
	prayer_name = prayer[0].name;
    }

    // Send notification if it's prayer time
    command = "notify-send \"It's " + prayer_name + " time.\" -i ~/.config/polybar/mosque.png";
    if(remaining == 1)
	std::system(command.c_str());

    // Print remaining time for next prayer
    printf("%0.2d:%0.2d", remaining/60, remaining%60);
}
