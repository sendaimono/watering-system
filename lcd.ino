#include <LiquidCrystal_I2C.h>
#include "lcd.h";

#define LCD_COLS 16
#define LCD_ROWS 2

bool lcd_active = false;
unsigned int display_started_on = 0;
unsigned const int display_duration = 30 * 1000;

LiquidCrystal_I2C lcd_I2C(0x27, LCD_COLS, LCD_ROWS);

void LCD::setup()
{
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
    lcd_active = false;
}

void LCD::wakeUp()
{
    if (!lcd_active)
    {
        turn_on();
        display_started_on = millis();
        lcd_active = true;
    }
}

bool LCD::isActive()
{
    return lcd_active;
}

bool LCD::shouldPowerDown(unsigned int current_time)
{
    return current_time - display_started_on > display_duration;
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
