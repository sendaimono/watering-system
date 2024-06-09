#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "lcd.h";

#define LCD_COLS 20
#define LCD_ROWS 4
#define LCD_I2C_ADRESS 0x27

unsigned const int DISPLAY_DURATION = 30 * 1000;

bool g_lcd_active = false;
unsigned int g_display_started_on = 0;

LiquidCrystal_I2C lcd_I2C(LCD_I2C_ADRESS, LCD_COLS, LCD_ROWS);

bool LCD::isLCDPluggedIn()
{
    Wire.beginTransmission(LCD_I2C_ADRESS);
    return Wire.endTransmission() == 0;
}

void LCD::setup()
{
    if (!isLCDPluggedIn())
    {
        Serial.println('LCD is not connected');
        return;
    }
    lcd_I2C.begin(LCD_COLS, LCD_ROWS);
    lcd_I2C.backlight();
    lcd_I2C.clear();
}

void LCD::turn_on()
{
    lcd_I2C.display();
    lcd_I2C.backlight();
}

void LCD::turn_off()
{
    lcd_I2C.noDisplay();
    lcd_I2C.noBacklight();
    g_lcd_active = false;
}

void LCD::wakeUp()
{
    if (!g_lcd_active)
    {
        turn_on();
        g_display_started_on = millis();
        g_lcd_active = true;
    }
}

bool LCD::isActive()
{
    return g_lcd_active;
}

bool LCD::shouldPowerDown(unsigned int current_time)
{
    return current_time - g_display_started_on > DISPLAY_DURATION;
}

void LCD::displaySensors(Sensors sensors)
{
    lcd_I2C.clear();
    lcd_I2C.setCursor(0, 0);
    lcd_I2C.print("S1  S2  S3");
    lcd_I2C.setCursor(0, 1);
    char buffer[LCD_COLS];
    auto moisture_readings = sensors.moisture_readings;
    for (int i = 0; i < moisture_readings.size; i++)
    {
        if (i == 0 || i == moisture_readings.size - 1)
        {
            sprintf(buffer, "%3d", moisture_readings.values[i]);
        }
        else
        {
            sprintf(buffer, " %3d ", moisture_readings.values[i]);
        }
    }
    lcd_I2C.print(buffer);
}
