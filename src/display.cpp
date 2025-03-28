#include "display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "time_manager.h"
#include "buttons.h"
#include "sensor.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3c

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void init_display()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    display.display();
    delay(100);
}

void clear_display()
{
    display.clearDisplay();
}

void display_screen()
{
    display.display();
}

void print_line(String text, int column, int row, int text_size)
{
    display.setTextSize(text_size);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(column, row);
    display.println(text);
    display.display();
}

void write_to_display(String text, int cursorX, int cursorY, int size, bool highlight)
{
    // Text size 1 = 10 pixels
    display.setTextSize(size);
    if (highlight)
    {
        display.setTextColor(BLACK);
        display.fillRect(cursorX, cursorY - 2, 128, 11 * size, WHITE);
    }
    else
    {
        display.setTextColor(WHITE);
    }
    display.setCursor(cursorX, cursorY);
    display.println(text);
}

void print_time_now(void)
{
    clear_display();
    print_line(String(days), 0, 0, 2);
    print_line(":", 20, 0, 2);
    print_line(String(hours), 30, 0, 2);
    print_line(":", 50, 0, 2);
    print_line(String(minutes), 60, 0, 2);
    print_line(":", 80, 0, 2);
    print_line(String(seconds), 90, 0, 2);
    delay(200);
}

void home_screen()
{

    // Display the time on top
    char time_str[9];

    strftime(time_str, sizeof(time_str), "%H:%M:%S", &timeinfo);
    write_to_display(time_str, 1, 0, 2);
    display.display();
    delay(200);
    // Display the temperature and humidity
    check_temp();
    display_screen();
}

//   void menu() {
//     int offset_next_state = next_state - 1;

//     // Display the menu options
//     write_to_display("1. Set Time", 1, 1, 1, offset_next_state == 1);
//     write_to_display("2. Set Alarm", 1, 11, 1, offset_next_state == 2);
//     write_to_display("3. View/Delete Alarm", 1, 21, 1, offset_next_state == 3);
//     write_to_display("4. Exit Menu", 1, 31, 1, offset_next_state == 0);

//     // Navigate the menu with buttons, and select menu option with OK
//     if (up_btn.state == 1) {
//       offset_next_state = (offset_next_state + 1) % 4;
//     } else if (down_btn.state == 1) {
//       offset_next_state -= - 1;
//       if (offset_next_state >= 0) {
//         offset_next_state = offset_next_state % 4;
//       } else {
//         offset_next_state = 3;
//       }
//     } else if (ok_btn.state == 1) {
//       current_mode = offset_next_state + 1;
//       next_state = 0;
//     }
//   }