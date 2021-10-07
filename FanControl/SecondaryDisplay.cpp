#include <LCD_1602_RUS.h>
#include "EditableDisplay.h"
#include "SecondaryDisplay.h"
#include "Arduino.h"
#include "WORK_MODES.h"

#define GRAD "°C"

void SecondaryDisplay::display(int onTemp, int offTemp, int workMode) {
    lcd.setCursor(0, 0);
    if (mode == ON_TEMP_MODE && millis() % (timeOn + timeOff) > timeOn) {
        lcd.print("    ");
    } else {
        lcd.print(onTemp);
        lcd.print(GRAD);
    }
    lcd.setCursor(4, 0);
    lcd.print(" - ON");

    lcd.setCursor(0, 1);
    if (mode == OFF_TEMP_MODE && millis() % (timeOn + timeOff) > timeOn) {
        lcd.print("    ");
    } else {
        lcd.print(offTemp);
        lcd.print(GRAD);
    }
    lcd.setCursor(4, 1);
    lcd.print(" - OFF");

    lcd.setCursor(12, 0);
    switch (workMode) {
        case ON:
            lcd.print("  ON");
            break;
        case OFF:
            lcd.print(" OFF");
            break;
        case AUTO:
            lcd.print("AUTO");
            break;
    }
}

SecondaryDisplay::SecondaryDisplay(LCD_1602_RUS& lcd) : EditableDisplay(lcd, 3) {}
SecondaryDisplay::~SecondaryDisplay() {};
