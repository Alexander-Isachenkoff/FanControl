#ifndef MainDisplay_h
#define MainDisplay_h

#include <LCD_1602_RUS.h>
#include "EditableDisplay.h"

enum
{
    MAIN_BASE_MODE,
    HOURS_MODE,
    MINUTES_MODE,
    DAY_MODE,
    MONTH_MODE,
    YEAR_MODE
};

class MainDisplay : public EditableDisplay
{
private:
    int timeOn = 600;
    int timeOff = 400;
    void printTime(int, int);
    void printDate(int, int, int);
    void printTemp(float);
    void printWorkMode(int);

public:
    void display(int hours, int minutes, int day, int month, int year, float temp);
    MainDisplay(LCD_1602_RUS &);
    ~MainDisplay();
};

#endif
