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
    if (sensors.moisture_readings == NULL)
        return;

    lcd_I2C.clear();
    auto moistureStr = sensors.moisture_readings->toString(false);
    int splitIndex = moistureStr.indexOf(" | rH3");
    String line1 = moistureStr.substring(0, splitIndex);
    String line2 = moistureStr.substring(splitIndex + 3); // Skip " | "

    // Display the first line
    lcd_I2C.setCursor(0, 0);
    lcd_I2C.print(line1);

    // Display the second line
    lcd_I2C.setCursor(0, 1);
    lcd_I2C.print(line2);

    auto dhtStr = sensors.dht_readings->toString();
    splitIndex = dhtStr.indexOf(" Temp");
    String line3 = dhtStr.substring(0, splitIndex);
    String line4 = dhtStr.substring(splitIndex + 1); // Skip " | "
    lcd_I2C.setCursor(0, 2);
    lcd_I2C.print(line3);

    // Display the second line
    lcd_I2C.setCursor(0, 3);
    lcd_I2C.print(line4);
}
