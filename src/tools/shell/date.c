#include <tools/shell/date.h>

void shell_cmd_date(int argc, char** argv) {
    printf("%s %s %d %02d:%02d:%02d GMT+0 %d%d\n",
        rtc_days[rtc_day_of_week()], rtc_months[rtc_month()], rtc_day(),
        rtc_hour(), rtc_minute(), rtc_second(), rtc_century(), rtc_year());
}