#include <apps/shell/date.h>

void shell_cmd_date(int argc, char** argv) {
    (void)(argc);
    (void)(argv);

    printf("%s %s %d %02d:%02d:%02d UTC %d%d\n",
        rtc_days[rtc_day_of_week()], rtc_months[rtc_month() - 1], (i32)rtc_day(),
        (i32)rtc_hour(), (i32)rtc_minute(), (i32)rtc_second(), (i32)rtc_century(), (i32)rtc_year());
}