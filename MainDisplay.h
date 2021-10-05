#include <LiquidCrystal_I2C.h>
#include "EditableDisplay.h"

enum Modes
{
    BASE_MODE,
    HOURS_MODE,
    MINUTES_MODE,
    DAY_MODE,
    MONTH_MODE,
    YEAR_MODE
};

class MainDisplay : EditableDisplay
{
private:
    int timeOn;
    int timeOff;

public:
    void display(int hours, int minutes, int day, int month, int year, float temp);
    void display();
    void editFirst();
    void editNext();
    void editPrev();
    void save();
    void toggleEditing();
    bool isEditing();
    int getMode();
    MainDisplay(LiquidCrystal_I2C &);
    ~MainDisplay();
};
