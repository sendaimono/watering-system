#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "lcd.h";

#define LCD_COLS 20
#define LCD_ROWS 4
#define LCD_I2C_ADRESS 0x27

unsigned const long DISPLAY_DURATION = 30 * 1000;

LiquidCrystal_I2C lcd_I2C(LCD_I2C_ADRESS, LCD_COLS, LCD_ROWS);

bool LCD::isLCDPluggedIn()
{
    Wire.begin();
    Wire.beginTransmission(LCD_I2C_ADRESS);
    return Wire.endTransmission() == 0;
}

void LCD::setup()
{

    if (!isLCDPluggedIn())
    {
        _enabled = false;
        Serial.println("LCD is not connected");
        return;
    }
    delay(100);
    Serial.println("LCD is connected");
    _enabled = true;
    lcd_I2C.begin(LCD_COLS, LCD_ROWS);
    delay(100);
    turn_off();
}

void LCD::turn_on()
{
    if (!_enabled)
        return;
    Serial.println("turn on LCD");
    lcd_I2C.clear();
    lcd_I2C.display();
    lcd_I2C.backlight();
}

void LCD::turn_off()
{
    if (!_enabled)
        return;

    Serial.println("turn off LCD");
    lcd_I2C.noDisplay();
    lcd_I2C.noBacklight();
    _is_activated = false;
}

bool LCD::wokeUp()
{
    if (_should_activate)
    {
        _is_activated = true;
        _should_activate = false;
        _display_started_on = millis();
        return true;
    }

    return false;
}

void LCD::wakeUp()
{
    if (_is_activated)
        return;
    _should_activate = true;
}

bool LCD::isActive()
{
    return _is_activated;
}

bool LCD::shouldPowerDown(unsigned long current_time)
{
    if (!_is_activated)
        return false;
    auto diff = _display_started_on > current_time ? 0 : current_time - _display_started_on;
    return diff > DISPLAY_DURATION;
}

void LCD::displaySensors(Sensors sensors)
{
    if (!_enabled)
        return;
    if (sensors.moisture_readings != NULL)
    {
        lcd_I2C.clear();
        lcd_I2C.setCursor(0, 0);
        lcd_I2C.print("S1  S2  S3");
        lcd_I2C.setCursor(0, 1);
        String output = "";
        char buffer[LCD_COLS];
        auto moisture_readings = sensors.moisture_readings;
        for (int i = 0; i < moisture_readings->size; i++)
        {
            if (i == 0 || i == moisture_readings->size - 1)
            {
                sprintf(buffer, "%3d", moisture_readings->values[i]);
            }
            else
            {
                sprintf(buffer, " %3d ", moisture_readings->values[i]);
            }
            output += buffer;
        }
        lcd_I2C.print(output);
    }
}
