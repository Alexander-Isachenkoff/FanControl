#include <Arduino.h>
#include <LCD_1602_RUS.h>
#include "EditableDisplay.h"
#include "MainDisplay.h"

#define SPACE ' '

const char* months[12] = {
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

MainDisplay::MainDisplay(LCD_1602_RUS& lcd) : EditableDisplay(lcd, 5) {
    mode = MAIN_BASE_MODE;
}

MainDisplay::~MainDisplay() {};

void MainDisplay::display(int hours, int minutes, int day, int month, int year, float temp) {
    blink = millis() % (timeOn + timeOff) > timeOn;
    MainDisplay::printTime(hours, minutes);
    MainDisplay::printDate(day, month, year);
    MainDisplay::printTemp(temp);
}

void MainDisplay::printTime(int hours, int minutes) {
    lcd.setCursor(0, 0);
    byte hourLength = hours < 10 ? 1 : 2;
    if (getMode() == HOURS_MODE && blink) {
        for (byte i = 0; i < hourLength; i++) {
            lcd.print(SPACE);
        }
    } else {
        lcd.print(hours);
    }

    lcd.print(':');

    if (getMode() == MINUTES_MODE && blink) {
        lcd.print("  ");
    } else {
        if (minutes < 10) {
            lcd.print('0');
        }
        lcd.print(minutes);
    }

    if (hours < 10) {
        lcd.print(SPACE);
    }
}

void MainDisplay::printDate(int day, int month, int year) {
    lcd.setCursor(0, 1);
    byte dayLength = day < 10 ? 1 : 2;
    if (getMode() == DAY_MODE && blink) {
        for (byte i = 0; i < dayLength; i++) {
            lcd.print(SPACE);
        }
    } else {
        lcd.print(day);
    }

    lcd.print(SPACE);

    byte monthLength = strlen(months[month - 1]) / 2;
    if (getMode() == MONTH_MODE && blink) {
        for (byte i = 0; i < monthLength; i++) {
            lcd.print(SPACE);
        }
    } else {
        lcd.print(months[month - 1]);
    }
    lcd.print(SPACE);

    if (getMode() == YEAR_MODE && blink) {
        lcd.print("    ");
    } else {
        lcd.print(year);
    }
    lcd.print(" г");

    for (byte i = 0; i < 7 - (dayLength + monthLength); i++) {
        lcd.print(SPACE);
    }
}

void MainDisplay::printTemp(float temp) {
    lcd.setCursor(10, 0);
    lcd.print(round(temp * 10) / 10.0, 1);
    lcd.print("°C");
}
