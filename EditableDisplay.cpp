#include <LiquidCrystal_I2C.h>

class EditableDisplay
{
private:
    LiquidCrystal_I2C lcd;
    int mode = 0;

public:
    void display()
    {
    }

    void editFirst()
    {
        if (!isEditing())
        {
            mode = 1;
        }
    }

    void editNext()
    {
        if (isEditing && mode < 5)
        {
            mode++;
        }
    }

    void editPrev()
    {
        if (mode > 1)
        {
            mode--;
        }
    }

    bool isEditing()
    {
        return mode > 0;
    }

    void save()
    {
        mode = 0;
    }

    void toggleEditing()
    {
        if (isEditing())
        {
            save();
        }
        else
        {
            editFirst();
        }
    }

    int getMode()
    {
        return mode;
    }

    EditableDisplay(LiquidCrystal_I2C &lcd)
    {
        this->lcd = lcd;
    }

    ~EditableDisplay();
};
