#ifndef EditableDisplay_h
#define EditableDisplay_h

#include <LCD_1602_RUS.h>

class EditableDisplay
{
private:

protected:
    const int timeOn = 600;
    const int timeOff = 400;
    bool blink;
    byte mode;
    byte modesCount;
    LCD_1602_RUS &lcd;

public:
    void display();
    void editFirst();
    void editNext();
    void editPrev();
    void save();
    void toggleEditing();
    bool isEditing();
    byte getMode();
    EditableDisplay(LCD_1602_RUS&, byte);
    ~EditableDisplay();
};

#endif
