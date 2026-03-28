#include "CBingoCell.h"

BingoCell::BingoCell() {
    word = "";
    isChecked = false;
    isFreeSpace = false;
}

void BingoCell::Init(std::string text, bool freeSpace) {
    word = text;
    isFreeSpace = freeSpace;
    isChecked = freeSpace;
}

void BingoCell::Toggle() {
    if (!isChecked) {
        isChecked = !isChecked;
    }
}
void BingoCell::Reset() {
    if (!isFreeSpace) {
        isChecked = false;
    }
}

void BingoCell::Draw(int x, int y, int size) {
    if (isChecked) {
        DrawRectangle(x, y, size, size, LIGHTGRAY);
    }

    DrawRectangleLines(x, y, size, size, BLACK);

    const char* text = word.c_str();
    int fontSize = size / 4;
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, x + (size - textWidth) / 2, y + (size - fontSize) / 2, fontSize, DARKBLUE);

    if (isChecked) {
        DrawLineEx({(float)x, (float)y}, {(float)(x + size), (float)(y + size)}, 3.0f, RED);
        DrawLineEx({(float)x, (float)(y + size)}, {(float)(x + size), (float)y}, 3.0f, RED);
    }
}

bool BingoCell::GetIsChecked() const {
    return isChecked;
}