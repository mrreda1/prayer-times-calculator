#include <iostream>
#include "prayer.h"

int main (void) {
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
  
    // Print prayers' data
    for(int i = 0; i < 6; i++)
    printf("%s: %0.2d:%0.2d\n", prayer[i].name.c_str(), prayer[i].time/60, prayer[i].time%60);
}
