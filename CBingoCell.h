#pragma once
#include "raylib.h"
#include <string>

class BingoCell {
private:
    std::string word;
    bool isChecked;
    bool isFreeSpace;


public:

    BingoCell();

    void Init(std::string text, bool freeSpace);

    void Toggle();

    void Reset();

    void Draw(int x, int y, int size);
    bool GetIsChecked() const;
};