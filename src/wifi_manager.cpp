#include "wifi_manager.h"
#include "display.h"
#include <WiFi.h>

const char *ssid = "Demon_net";
const char *password = "nopassword123";
int channel = 6;

const char *default_ssid = "Wokwi-GUEST";
const char *default_password = "";

void init_wifi()
{
    WiFi.begin(default_ssid, default_password, channel);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
        clear_display();
        print_line("Connecting to WIFI", 0, 0, 2);
        delay(250);
    }
    clear_display();
    print_line("Connected to WIFI", 0, 0, 2);
    delay(1000);
}
