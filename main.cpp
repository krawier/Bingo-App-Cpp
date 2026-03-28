#include <iostream>
#include "raylib.h"
#include <string>
#include <vector>

struct BingoCell {

    std::string word;
    bool isChecked = false;

};

int main() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    const int screenWidth = 800;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Bingo-App");
    SetTargetFPS(60);

    const int gridSize = 5;
    const int cellSize = screenWidth / gridSize/gridSize;

    BingoCell bingoBoard[5][5];

    // middle one is FREE
    int wordCount = 1;
    for (int row =0; row < gridSize; row++) {
        for (int col =0; col < gridSize; col++) {

            if (row == 2 && col == 2) {

                bingoBoard[row][col].word = "FREE";
                bingoBoard[row][col].isChecked = true;

            }else {

                bingoBoard[row][col].word = "" + std::to_string(wordCount);
                wordCount++;

            }

        }
    }

    while (!WindowShouldClose()) {

        int screenW = GetScreenWidth();
        int screenH = GetScreenHeight();

        int boardSize = std::min(screenW, screenH) - 40;
        int cellSize = boardSize / gridSize;

        int offsetX = (screenW - (cellSize * gridSize)) / 2;
        int offsetY = (screenH - (cellSize * gridSize)) / 2;


        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {

                int x = offsetX + (col * cellSize);
                int y = offsetY + (row * cellSize);

                if (bingoBoard[row][col].isChecked) {
                    DrawRectangle(x, y, cellSize, cellSize, LIGHTGRAY);
                }

                DrawRectangleLines(x, y, cellSize, cellSize, BLACK);

                const char* text = bingoBoard[row][col].word.c_str();

                int fontSize = cellSize / 4;
                int textWidth = MeasureText(text, fontSize);
                DrawText(text, x + (cellSize - textWidth) / 2, y + (cellSize - fontSize) / 2, fontSize, DARKBLUE);

                if (bingoBoard[row][col].isChecked) {
                    DrawLineEx({(float)x, (float)y}, {(float)(x + cellSize), (float)(y + cellSize)}, 3.0f, RED);
                    DrawLineEx({(float)x, (float)(y + cellSize)}, {(float)(x + cellSize), (float)y}, 3.0f, RED);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;

}