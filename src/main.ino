#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHTesp.h>
#include <WiFi.h>
#include <display.h>
#include <time_manager.h>
#include <buttons.h>
#include "alarm.h"
#include "sensor.h"
#include "wifi_manager.h"

void setup()
{
  // initializing the pins
  init_pins();

  // Initialize serial monitor
  Serial.begin(115200);

  // Initialize the OLED display
  init_display();

  // Initialize the DHT sensor
  init_dht();

  // Initialize the wifi connection
  init_wifi();

  // Initialize the time
  init_time();

  print_line("Welcome to Medibox!", 5, 15, 2);
  delay(2000);
  clear_display();
}

void loop()
{
  // put your main code here, to run repeatedly:
  update_time_with_check_alarm();
  clear_display();
  home_screen();

  if (digitalRead(PB_OK) == LOW)
  {
    delay(200); // allow the pushbutton to debounce
    go_to_menu();
  }

  delay(200); // this speeds up the simulation
}
