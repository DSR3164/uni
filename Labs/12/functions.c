#include <stdio.h>
#include <math.h>
#include "time.h"

void AllTime( T start,  T end) {
    const int MINUTES_PER_HOUR = 60;
    const int HOURS_PER_DAY = 24;
    const int DAYS_PER_WEEK = 7;
    printf("Start Time: %d:%d\n", start.Hour, start.Minute);
    printf("End Time: %d:%d\n", end.Hour, end.Minute);
    int dif_time = (end.Hour * MINUTES_PER_HOUR + end.Minute) - (start.Hour * MINUTES_PER_HOUR + start.Minute);
    int timeweek = (MINUTES_PER_HOUR * HOURS_PER_DAY * DAYS_PER_WEEK) + dif_time;
    printf("Time in Week: %d\n", timeweek);
    int weeks = timeweek / MINUTES_PER_HOUR / HOURS_PER_DAY / DAYS_PER_WEEK;
    int days = timeweek / MINUTES_PER_HOUR / HOURS_PER_DAY - (weeks * DAYS_PER_WEEK);
    int hours = timeweek / MINUTES_PER_HOUR - (days * HOURS_PER_DAY) - (weeks * DAYS_PER_WEEK * HOURS_PER_DAY);
    int minutes = timeweek - (hours * MINUTES_PER_HOUR) - (days * HOURS_PER_DAY * MINUTES_PER_HOUR) - (weeks * DAYS_PER_WEEK * HOURS_PER_DAY * MINUTES_PER_HOUR);
    printf("Total work time for the week: %d weeks, %d days, %d hours, %d minutes\n", weeks, days, hours, minutes);
}
