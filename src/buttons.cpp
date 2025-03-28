#include "buttons.h"
#include <Arduino.h>
#include "display.h"
#include "time_manager.h"
#include "alarm.h"

#define PB_CANCEL 34
#define PB_OK 32
#define PB_UP 33
#define PB_DOWN 35

int current_mode = 0;
int max_modes = 7;
String modes[] = {"1 - Set Time", "2 - Set Alarm 1", "3 - Set Alarm 2", "4- Disable Alarms", "5- View Alarms", "6- Delete Alarms", "7- Set Time Zone"};

void init_pins()
{
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(PB_CANCEL, INPUT);
  pinMode(PB_OK, INPUT);
  pinMode(PB_UP, INPUT);
  pinMode(PB_DOWN, INPUT);
}

bool is_button_pressed(int button)
{
  return digitalRead(button) == LOW;
}

int wait_for_button_press()
{

  while (true)
  {
    if (digitalRead(PB_UP) == LOW)
    {
      delay(200);
      return PB_UP;
    }

    else if (digitalRead(PB_DOWN) == LOW)
    {
      delay(200);
      return PB_DOWN;
    }

    else if (digitalRead(PB_OK) == LOW)
    {
      delay(200);
      return PB_OK;
    }

    else if (digitalRead(PB_CANCEL) == LOW)
    {
      delay(200);
      return PB_CANCEL;
    }

    update_time();
  }
}

void run_mode(int mode)
{
  if (mode == 0)
  {
    set_time();
  }

  if (mode == 1 || mode == 2)
  {
    set_alarm(mode - 1);
  }

  else if (mode == 3)
  {
    alarm_enabled = false;
  }

  else if (mode == 4)
  {
    view_alarms();
  }

  else if (mode == 5)
  {
    delete_alarm();
  }

  else if (mode == 6)
  {
    set_time_zone();
  }
}

void go_to_menu()
{
  while (digitalRead(PB_CANCEL) == HIGH)
  {
    clear_display();
    print_line(modes[current_mode], 0, 0, 2);

    int pressed = wait_for_button_press();

    if (pressed == PB_UP)
    {
      delay(200);
      current_mode += 1;
      current_mode = current_mode % max_modes;
    }

    if (pressed == PB_DOWN)
    {
      delay(200);
      current_mode -= 1;

      if (current_mode < 0)
      {
        current_mode = max_modes - 1;
      }
    }

    else if (pressed == PB_OK)
    {
      delay(200);
      run_mode(current_mode);
    }

    else if (pressed == PB_CANCEL)
    {
      delay(200);
      break;
    }
  }
}