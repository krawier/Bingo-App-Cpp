#include "CBingoCell.h"

BingoCell::BingoCell() {
    word = "";
    isChecked = false;
    isFreeSpace = false;
    drawProgress = 0.0f;
}

void BingoCell::Init(std::string text, bool freeSpace) {
    word = text;
    isFreeSpace = freeSpace;
    isChecked = freeSpace;
    drawProgress = freeSpace ? 2.0f : 0.0f;
}

void BingoCell::Toggle() {
    if (!isChecked) {
        isChecked = !isChecked;
        if (isChecked) {
            drawProgress = 0.0f;
        }
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

        if (drawProgress < 2.0f) {
            drawProgress += GetFrameTime() * 8.0f;
        }

        if (drawProgress > 0.0f) {

            float p1 = std::min(drawProgress, 1.0f);
            DrawLineEx({(float)x, (float)y}, {(float)(x + size * p1), (float)(y + size * p1)}, 4.0f, RED);

        }

        if (drawProgress > 1.0f) {
            float p2 = std::min(drawProgress - 1.0f, 1.0f);
            DrawLineEx({(float)x, (float)(y + size)}, {(float)(x + size * p2), (float)(y + size - size * p2)}, 4.0f, RED);
        }

    }
}

bool BingoCell::GetIsChecked() const {
    return isChecked;
}