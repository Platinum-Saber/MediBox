#include "sensor.h"
#include "display.h"
#include <DHTesp.h>
#include "alarm.h"

DHTesp dhtSensor;
#define DHTPIN 12

void init_dht()
{
    print_line("Initializing DHT sensor", 0, 45, 1);
    dhtSensor.setup(DHTPIN, DHTesp::DHT22);
    if (dhtSensor.getStatusString() != "OK")
    {
        Serial.println("DHT sensor error!");
        print_line("DHT sensor error!", 0, 45, 1);
        delay(1000);
    }
    else
    {
        Serial.println("DHT sensor initialized successfully.");
        clear_display();
        print_line("sensor check [pass]", 0, 25, 2);
        delay(1000);
    }
}

void check_temp()
{
    bool warning = false;
    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    if (data.temperature > 35)
    {
        write_to_display("TEMP HIGH", 0, 45, 1);
    }

    if (data.temperature < 35)
    {
        write_to_display("TEMP LOW", 0, 45, 1);
    }

    if (data.humidity > 40)
    {
        write_to_display("HUMIDY HIGH", 0, 55, 1);
    }

    if (data.humidity < 20)
    {
        write_to_display("HUMIDITY LOW", 0, 55, 1);
    }

    if (data.temperature > 32 || data.temperature < 24)
    {
        warning = true;
        write_to_display("Temperature Warning", 0, 25, 1);
    }

    if (data.humidity > 85 || data.humidity < 65)
    {
        warning = true;
        write_to_display("Humidity Warning", 0, 35, 1);
    }
    if (warning == true)
    {
        digitalWrite(LED_1, HIGH);
        //ring_warning();
        delay(500);
    }
    else
    {
        digitalWrite(LED_1, LOW);
    }
}
