#include <IRremote.h>
#include <microDS18B20.h>
#include <microDS3231.h>
#include <LCD_1602_RUS.h>

#include "MainDisplay.h"
#include "SecondaryDisplay.h"
#include "IR_CODES.h"

#define DS18B20_PORT 2
#define IR_REC_PORT 6
#define TIME_UPDATE_TIMEOUT 1000

MicroDS3231 rtc;
MicroDS18B20<DS18B20_PORT> sensor1;
LCD_1602_RUS lcd(0x27, 16, 2);

DateTime timeNow;
unsigned long lastTempGetTime;
float tempFloat;
int tempRound;

int displayMode = 0;
bool displayModeChanged = false;

int onTemp = 45;
int offTemp = 35;

MainDisplay mainDisplay(lcd);
SecondaryDisplay secondaryDisplay(lcd);
IRrecv irrecv(IR_REC_PORT);
decode_results results;

void setup()
{
    pinMode(2, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);

    Serial.begin(9600);

    lcd.init();
    lcd.backlight();
    IrReceiver.begin(IR_REC_PORT, ENABLE_LED_FEEDBACK);
}

void loop()
{
    timeNow = rtc.getTime();
    if (millis() - lastTempGetTime > TIME_UPDATE_TIMEOUT)
    {
        monitor();
    }
    display();

    if (IrReceiver.decode())
    {
        Serial.println(IrReceiver.decodedIRData.command, HEX);

        switch (IrReceiver.decodedIRData.command)
        {
        case OK:
            if (displayMode == 0)
            {
                mainDisplay.toggleEditing();
            }
            if (displayMode == 1)
            {
                secondaryDisplay.toggleEditing();
            }
            break;

        case UP:
            if (displayMode == 0)
            {
                evalTime(1);
            }
            if (displayMode == 1)
            {
                evalTemp(1);
            }
            break;

        case DOWN:
            if (displayMode == 0)
            {
                evalTime(-1);
            }
            if (displayMode == 1)
            {
                evalTemp(-1);
            }
            break;

        case LEFT:
            if (displayMode == 0)
            {
                if (mainDisplay.isEditing())
                {
                    mainDisplay.editPrev();
                }
            }
            if (displayMode == 1)
            {
                displayMode = 0;
                displayModeChanged = true;
            }
            break;

        case RIGHT:
            if (displayMode == 0)
            {
                if (mainDisplay.isEditing())
                {
                    mainDisplay.editNext();
                }
                else
                {
                    displayMode = 1;
                    displayModeChanged = true;
                }
                break;
            }

            if (displayMode == 1)
            {
                editTempMode++;
                editTempMode %= 2;
                break;
            }
        }
        irrecv.resume();
    }
}

void display()
{
    if (displayModeChanged)
    {
        lcd.clear();
        displayModeChanged = false;
    }
    if (displayMode == 0)
    {
        mainDisplay.display(rtc.getHours(), rtc.getMinutes(), rtc.getDate(), rtc.getMonth(), rtc.getYear(), tempFloat);
    }
    if (displayMode == 1)
    {
        secondaryDisplay.displayTemperatures(onTemp, offTemp);
    }
}

void evalTime(int inc)
{
    switch (mainDisplay.getMode())
    {
    case BASE_MODE:
        return;
    case HOURS_MODE:
        timeNow.hour = (timeNow.hour + inc) % 24;
        break;
    case MINUTES_MODE:
        timeNow.minute = (timeNow.minute + inc) % 60;
        break;
    case DAY_MODE:
        timeNow.date = (timeNow.date + inc) % 31;
        break;
    case MONTH_MODE:
        timeNow.month = (timeNow.month + inc) % 12;
        break;
    case YEAR_MODE:
        timeNow.year = timeNow.year + inc;
        break;
    }
    rtc.setTime(timeNow);
}

void evalTemp(int inc)
{
    switch (editTempMode)
    {
    case 1:
        onTemp += inc;
        break;
    case 2:
        offTemp += inc;
        break;
    }
}

void monitor()
{
    lastTempGetTime = millis();
    sensor1.requestTemp();
    tempFloat = sensor1.getTemp();
    tempRound = round(tempFloat);

    // Serial.println(rtc.getTemperatureFloat());
    // Serial.println(timeNow.second);
    // Serial.println(digitalRead(5));

    Serial.print("editTimeMode: ");
    Serial.println(mainDisplay.editTimeMode);
}
