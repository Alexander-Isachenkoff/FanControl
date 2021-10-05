#include <LiquidCrystal_I2C.h>
#include "EditableDisplay.h"
#include "MainDisplay.h"

const char *months[12] = {
    "янв",
    "февр",
    "марта",
    "апр",
    "мая",
    "июня",
    "июля",
    "авг",
    "сент",
    "окт",
    "ноя",
    "дек",
};

class MainDisplay : EditableDisplay
{
private:
    int timeOn = 600;
    int timeOff = 400;
    LiquidCrystal_I2C lcd;
    int mode = BASE_MODE;

    void printTime(int hours, int minutes)
    {
        lcd.setCursor(0, 0);
        int hourLength = hours < 10 ? 1 : 2;
        if (mode == HOURS_MODE && millis() % (timeOn + timeOff) > timeOn)
        {
            for (int i = 0; i < hourLength; i++)
            {
                lcd.print(' ');
            }
        }
        else
        {
            lcd.print(hours);
        }

        lcd.print(':');

        if (mode == MINUTES_MODE && millis() % (timeOn + timeOff) > timeOn)
        {
            lcd.print("  ");
        }
        else
        {
            if (minutes < 10)
            {
                lcd.print('0');
            }
            lcd.print(minutes);
        }

        if (hours < 10)
        {
            lcd.print(' ');
        }
    }

    void printDate(int day, int month, int year)
    {
        lcd.setCursor(0, 1);
        int dayLength = day < 10 ? 1 : 2;
        if (mode == DAY_MODE && millis() % (timeOn + timeOff) > timeOn)
        {
            for (int i = 0; i < dayLength; i++)
            {
                lcd.print(' ');
            }
        }
        else
        {
            lcd.print(day);
        }

        lcd.print(' ');

        int monthLength = strlen(months[month - 1]) / 2;
        if (mode == MONTH_MODE && millis() % (timeOn + timeOff) > timeOn)
        {
            for (int i = 0; i < monthLength; i++)
            {
                lcd.print(' ');
            }
        }
        else
        {
            lcd.print(months[month - 1]);
        }
        lcd.print(' ');

        if (mode == YEAR_MODE && millis() % (timeOn + timeOff) > timeOn)
        {
            lcd.print("    ");
        }
        else
        {
            lcd.print(year);
        }
        lcd.print(" г.");

        for (int i = 0; i < 7 - (dayLength + monthLength); i++)
        {
            lcd.print(' ');
        }
    }

    void printTemp(float temp)
    {
        lcd.setCursor(10, 0);
        lcd.print(round(temp * 10) / 10.0);
        lcd.setCursor(14, 0);
        lcd.print("°C");
    }

public:
    void display(int hours, int minutes, int day, int month, int year, float temp)
    {
        printTime(hours, minutes);
        printDate(day, month, year);
        printTemp(temp);
    }

    MainDisplay(LiquidCrystal_I2C &lcd)
    {
        this->lcd = lcd;
    }

    ~MainDisplay();
};
