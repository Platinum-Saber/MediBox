#ifndef ALARM_H
#define ALARM_H

#define BUZZER 5
#define LED_1 15

extern bool alarm_enabled;

void ring_alarm(int alarm_index);
void update_time_with_check_alarm();
void set_alarm(int alarm);
void delete_alarm();
void view_alarms();
void ring_warning();

#endif
