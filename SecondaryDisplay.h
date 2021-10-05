#include <LiquidCrystal_I2C.h>
#include "EditableDisplay.h"

class SecondaryDisplay : EditableDisplay
{
private:
    int timeOn;
    int timeOff;
    int editTempMode;
    LiquidCrystal_I2C lcd;

public:
    void displayTemperatures(int, int);
    void toggleEditing();
    SecondaryDisplay(LiquidCrystal_I2C &);
    ~SecondaryDisplay();
};
