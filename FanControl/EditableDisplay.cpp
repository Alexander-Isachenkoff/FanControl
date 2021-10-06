#include <LCD_1602_RUS.h>
#include "EditableDisplay.h"

EditableDisplay::EditableDisplay(LCD_1602_RUS &lcd, int modes) : lcd{lcd}
{
    modesCount = modes;
}

EditableDisplay::~EditableDisplay() {};

void EditableDisplay::editFirst() {
    if (!isEditing()) {
        mode = 1;
    }
}

void EditableDisplay::editNext() {
    if (isEditing() && mode < modesCount) {
        mode++;
    }
}

void EditableDisplay::editPrev() {
    if (mode > 1) {
        mode--;
    }
}

bool EditableDisplay::isEditing() {
    return mode > 0;
}

void EditableDisplay::save() {
    mode = 0;
}

void EditableDisplay::toggleEditing() {
    if (isEditing()) {
        save();
    } else {
        editFirst();
    }
}

int EditableDisplay::getMode() {
    return mode;
}
