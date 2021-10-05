#include <LiquidCrystal_I2C.h>

class SecondaryDisplay
{
private:
    int timeOn = 600;
    int timeOff = 400;
    int editTempMode = 0;
    LiquidCrystal_I2C lcd;

public:

    void displayTemperatures(int onTemp, int offTemp)
    {
        lcd.setCursor(0, 0);
        if (editTempMode == 1 && millis() % (timeOn + timeOff) > timeOn)
        {
            lcd.print("       ");
        }
        else
        {
            lcd.print("ON temp");
        }
        lcd.setCursor(12, 0);
        lcd.print(onTemp);
        lcd.print("°C");

        lcd.setCursor(0, 1);
        if (editTempMode == 2 && millis() % (timeOn + timeOff) > timeOn)
        {
            lcd.print("        ");
        }
        else
        {
            lcd.print("OFF temp");
        }
        lcd.setCursor(12, 1);
        lcd.print(offTemp);
        lcd.print("°C");
    }

    SecondaryDisplay(LiquidCrystal_I2C &lcd)
    {
        this->lcd = lcd;
    }
    ~SecondaryDisplay();
};
