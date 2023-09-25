#include <iostream>
#include "prayer.h"

int main (void) {
    int time_in_minutes, remaining, i;
    std::string prayer_name, command;
    prayers* prayer;
    PrayerApp app(12, 0, 0, +3, 23, 1,
		29.8403, 31.2982, 19.5, 17.5);

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
    if(remaining == 0)
	std::system(command.c_str());

    // Print remaining time for next prayer
    printf("%0.2d:%0.2d", remaining/60, remaining%60);
}
