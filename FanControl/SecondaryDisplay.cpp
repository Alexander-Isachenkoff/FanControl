#include <LCD_1602_RUS.h>
#include "EditableDisplay.h"
#include "SecondaryDisplay.h"
#include "Arduino.h"

void SecondaryDisplay::displayTemperatures(int onTemp, int offTemp) {
    lcd.setCursor(0, 0);
    if (mode == ON_TEMP_MODE && millis() % (timeOn + timeOff) > timeOn) {
        lcd.print("     ");
    } else {
        lcd.print("t° ON");
    }
    lcd.setCursor(12, 0);
    lcd.print(onTemp);
    lcd.print("°C");

    lcd.setCursor(0, 1);
    if (mode == OFF_TEMP_MODE && millis() % (timeOn + timeOff) > timeOn) {
        lcd.print("      ");
    } else {
        lcd.print("t° OFF");
    }
    lcd.setCursor(12, 1);
    lcd.print(offTemp);
    lcd.print("°C");
}

SecondaryDisplay::SecondaryDisplay(LCD_1602_RUS &lcd) : EditableDisplay(lcd, 2) {}
SecondaryDisplay::~SecondaryDisplay() {};
