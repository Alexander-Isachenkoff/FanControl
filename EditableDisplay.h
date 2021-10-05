#include <LiquidCrystal_I2C.h>

class EditableDisplay
{
private:
    LiquidCrystal_I2C lcd;
    int mode;

public:    
    void display();
    void editFirst();
    void editNext();
    void editPrev();
    void save();
    void toggleEditing();
    bool isEditing();
    int getMode();
    EditableDisplay(LiquidCrystal_I2C &);
    ~EditableDisplay();
};
