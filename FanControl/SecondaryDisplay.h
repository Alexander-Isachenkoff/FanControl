#ifndef SecondaryDisplay_h
#define SecondaryDisplay_h

#include <LCD_1602_RUS.h>
#include "EditableDisplay.h"

enum
{
    BASE_MODE,
    ON_TEMP_MODE,
    OFF_TEMP_MODE
};

class SecondaryDisplay : public EditableDisplay
{
private:
    int timeOn = 600;
    int timeOff = 400;

public:
    void display(int, int, int, float);
    SecondaryDisplay(LCD_1602_RUS &);
    ~SecondaryDisplay();
};

#endif
