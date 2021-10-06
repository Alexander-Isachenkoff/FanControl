#ifndef EditableDisplay_h
#define EditableDisplay_h

#include <LCD_1602_RUS.h>

class EditableDisplay
{
private:

protected:
    int mode;
    int modesCount;
    LCD_1602_RUS &lcd;

public:
    void display();
    void editFirst();
    void editNext();
    void editPrev();
    void save();
    void toggleEditing();
    bool isEditing();
    int getMode();
    EditableDisplay(LCD_1602_RUS&, int);
    ~EditableDisplay();
};

#endif
