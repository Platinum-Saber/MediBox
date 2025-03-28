#include "time_manager.h"
#include <WiFi.h>
#include <time.h>
#include "buttons.h"
#include "display.h"

int days = 0;
int hours = 0;
int minutes = 0;
int seconds = 0;
struct tm timeinfo;

#define NTP_SERVER "pool.ntp.org"
#define UTC_OFFSET 0
#define UTC_OFFSET_DST 0


void init_time()
{
    configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
}

// time update function and fetch current time from NTP Server
void update_time()
{
    if (!getLocalTime(&timeinfo))
    {
        print_line("Failed to get time", 0, 0, 1);
        display_screen();
        Serial.println("Failed to obtain time");
        delay(200);
        return;
    }

    // Extract hours, minutes, seconds, and days
    char timeHour[3];
    strftime(timeHour, 3, "%H", &timeinfo);
    hours = atoi(timeHour);

    char timeMinute[3];
    strftime(timeMinute, 3, "%M", &timeinfo);
    minutes = atoi(timeMinute);

    char timeSecond[3];
    strftime(timeSecond, 3, "%S", &timeinfo);
    seconds = atoi(timeSecond);

    char timeDay[3];
    strftime(timeDay, 3, "%d", &timeinfo);
    days = atoi(timeDay);
}

tm get_time_info(){
    return timeinfo;
}

void set_time()
{
    int temp_hours = hours;

    while (true)
    {
        clear_display();
        print_line("Enter hour: " + String(temp_hours), 0, 0, 2);

        int pressed = wait_for_button_press();

        if (pressed == PB_UP)
        {
            delay(200);
            temp_hours += 1;
            temp_hours = temp_hours % 24;
        }

        if (pressed == PB_DOWN)
        {
            delay(200);
            temp_hours -= 1;
            if (temp_hours < 0)
            {
                temp_hours = 23;
            }
        }

        else if (pressed == PB_OK)
        {
            delay(200);
            hours = temp_hours;
        }

        else if (pressed == PB_CANCEL)
        {
            delay(200);
            break;
        }
    }

    int temp_minutes = minutes;

    while (true)
    {
        clear_display();
        print_line("Enter minutes: " + String(temp_minutes), 0, 0, 2);

        int pressed = wait_for_button_press();

        if (pressed == PB_UP)
        {
            delay(200);
            temp_minutes += 1;
            temp_minutes = temp_minutes % 60;
        }

        if (pressed == PB_DOWN)
        {
            delay(200);
            temp_minutes -= 1;
            if (temp_minutes < 0)
            {
                temp_minutes = 59;
            }
        }

        else if (pressed == PB_OK)
        {
            delay(200);
            minutes = temp_minutes;
        }

        else if (pressed == PB_CANCEL)
        {
            delay(200);
            break;
        }
    }

    clear_display();
    print_line("Time is set", 0, 0, 2);
    delay(2000);
}

// Function to set the time zone offset (supports fractional offsets)
void set_time_zone()
{
    float utc_offset = UTC_OFFSET;
    float temp_offset = utc_offset;

    while (true)
    {
        clear_display();
        print_line("UTC Offset: " + String(temp_offset, 1), 0, 0, 2); // Display with 1 decimal place

        int pressed = wait_for_button_press();

        if (pressed == PB_UP)
        {
            delay(200);
            temp_offset += 0.5;     // Increment by 0.5
            if (temp_offset > 14.0) // Limit to a maximum of +14.0
            {
                temp_offset = -12.0;
            }
        }

        if (pressed == PB_DOWN)
        {
            delay(200);
            temp_offset -= 0.5;      // Decrement by 0.5
            if (temp_offset < -12.0) // Limit to a minimum of -12.0
            {
                temp_offset = 14.0;
            }
        }

        else if (pressed == PB_OK)
        {
            delay(200);
            utc_offset = temp_offset;
            configTime(utc_offset * 3600, UTC_OFFSET_DST, NTP_SERVER); // Convert offset to seconds
            break;
        }

        else if (pressed == PB_CANCEL)
        {
            delay(200);
            break;
        }
    }

    clear_display();
    print_line("Time Zone Set", 0, 0, 2);
    delay(2000);
}
