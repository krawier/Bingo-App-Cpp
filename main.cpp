#include <iostream>
#include "raylib.h"
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include "CBingoCell.h"

bool CheckBingo(BingoCell board[5][5]) {
    const int size = 5;

    for (int i = 0; i < size; i++) {
        bool rowWin = true;
        bool colWin = true;
        for (int j = 0; j < size; j++) {
            if (!board[i][j].GetIsChecked()) rowWin = false;
            if (!board[j][i].GetIsChecked()) colWin = false;
        }
        if (rowWin || colWin) return true;
    }

    bool diag1Win = true;
    bool diag2Win = true;
    for (int i = 0; i < size; i++) {
        if (!board[i][i].GetIsChecked()) diag1Win = false;
        if (!board[i][size - 1 - i].GetIsChecked()) diag2Win = false;
    }
    if (diag1Win || diag2Win) return true;

    return false;
}


int main() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    const int screenWidth = 800;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Bingo-App");
    SetTargetFPS(60);

    const int gridSize = 5;

    BingoCell bingoBoard[5][5];

    // std::vector<std::string> wordList = {
    //     "TRIVIAL CALCULATION", "YOU CAN DO IT AT HOME", "DO WE NEED A BREAK?", "DEATH STARE", "FALLS OVER", "DIES",
    //     "LET ME STRESS OUT", "INTERVALS FROM HELL", "GOOFY AHH GRAPHIC", "ANY QUESTIONS?",
    //     "ALL IS CLEAR?", "IMPOSSIBLE", "ATTENDANCE LIST", "MATRIX OF DEATH", "CHOKES", "TOTALLY UNCLEAR GRAPH",
    //     "IS OLD", "AS YOU MAY REMEMBER", "JUST A MOMENT AGO", "GOOD MORNING", "THANK YOU FOR YOUR ATTENTION", "67",
    //     "GETS SCARED", "PROJECTOR FAILURE"
    // };


    std::vector<std::string> wordList;

    for (int i = 1; i <= 128; i++) {
        wordList.push_back(std::to_string(i));
    }

    std::mt19937 g(time(0));
    std::shuffle(wordList.begin(), wordList.end(), g);

    int wordIndex = 0;
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {

            if (row == 2 && col == 2) {
                bingoBoard[row][col].Init("FREE", true);
            } else {

                bingoBoard[row][col].Init(wordList[wordIndex], false);
                wordIndex++;
            }

        }
    }


    bool isGameOver = false;

    while (!WindowShouldClose()) {

        int screenW = GetScreenWidth();
        int screenH = GetScreenHeight();
        int boardSize = std::min(screenW, screenH) - 40;
        int cellSize = boardSize / gridSize;
        int offsetX = (screenW - (cellSize * gridSize)) / 2;
        int offsetY = (screenH - (cellSize * gridSize)) / 2;

        if (!isGameOver) {

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                int mouseX = GetMouseX();
                int mouseY = GetMouseY();

                if (mouseX >= offsetX && mouseX <= offsetX + (cellSize * gridSize) &&
                    mouseY >= offsetY && mouseY <= offsetY + (cellSize * gridSize)) {

                    int clickedCol = (mouseX - offsetX) / cellSize;
                    int clickedRow = (mouseY - offsetY) / cellSize;

                    bingoBoard[clickedRow][clickedCol].Toggle();
                    isGameOver = CheckBingo(bingoBoard);
                    }
            }
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                int x = offsetX + (col * cellSize);
                int y = offsetY + (row * cellSize);

                bingoBoard[row][col].Draw(x, y, cellSize);
            }
        }

        if (isGameOver) {

            DrawRectangle(0,0,screenW,screenH, Fade(BLACK, 0.6f));




            if ((int)(GetTime() * 3) % 2 == 0) {
                const char* winText = "BINGO!!!";
                int winFontSize = screenW / 8;
                int textWidth = MeasureText(winText, winFontSize);

                DrawText(winText, (screenW - textWidth) / 2, (screenH - winFontSize) / 2, winFontSize, GOLD);
            }

            const char* resetText = "press space to start over";
            int winFontSize = screenW / 16;
            DrawText(resetText, (screenW - MeasureText(resetText, 20)) / 2, (screenH / 2) + winFontSize, 20, GOLD);



            if (IsKeyPressed(KEY_SPACE)) {
                isGameOver = false;

                std::mt19937 g(time(0));
                std::shuffle(wordList.begin(), wordList.end(), g);

                int wordIndex = 0;
                for (int r = 0; r < gridSize; r++) {
                    for (int c = 0; c < gridSize; c++) {

                        if (r == 2 && c == 2) {
                            bingoBoard[r][c].Init("FREE", true);
                        } else {
                            bingoBoard[r][c].Init(wordList[wordIndex], false);
                            wordIndex++;
                        }

                    }
                }
            }


        }



        EndDrawing();
    }

    CloseWindow();
    return 0;

}