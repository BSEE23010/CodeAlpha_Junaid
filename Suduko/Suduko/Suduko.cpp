#include "raylib.h"
#include <iostream>
#include <vector>

using namespace std;

#define N 9
#define CELL_SIZE 70  // Increased cell size to make the grid wider
#define SCREEN_WIDTH (CELL_SIZE * N)
#define SCREEN_HEIGHT (CELL_SIZE * N + 300) // Increased height for more space

// Function to check if placing num at board[row][col] is valid
bool isValid(vector<vector<int>>& board, int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

// Recursive function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (board[row][col] == 0) {  // Empty cell
                for (int num = 1; num <= 9; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board)) {
                            return true;
                        }
                        board[row][col] = 0;  // Backtrack
                    }
                }
                return false;  // If no valid number is found
            }
        }
    }
    return true;  // Puzzle is solved
}

// Function to reset the Sudoku grid
void resetBoard(vector<vector<int>>& board) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            board[row][col] = 0;
        }
    }
}

// Function to draw the Sudoku grid with bold lines for 3x3 subgrids
void drawGrid(vector<vector<int>>& board, int selectedRow, int selectedCol) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            Rectangle cell = { col * CELL_SIZE, row * CELL_SIZE + 70, CELL_SIZE, CELL_SIZE };
            Color cellColor = (row == selectedRow && col == selectedCol) ? LIGHTGRAY : RAYWHITE;
            DrawRectangleRec(cell, cellColor);

            if (board[row][col] != 0) {
                char buffer[2];
                snprintf(buffer, 2, "%d", board[row][col]);
                DrawText(buffer, col * CELL_SIZE + CELL_SIZE / 3, row * CELL_SIZE + CELL_SIZE / 3 + 70, 40, BLACK);
            }
        }
    }

    // Draw thicker lines for 3x3 subgrids
    for (int i = 0; i <= N; i++) {
        int thickness = (i % 3 == 0) ? 3 : 1;
        DrawLineEx(Vector2{ (float)(i * CELL_SIZE), 70.0f },
            Vector2{ (float)(i * CELL_SIZE), (float)(N * CELL_SIZE + 70) },
            (float)thickness, BLACK);  // Vertical lines
        DrawLineEx(Vector2{ 0.0f, (float)(i * CELL_SIZE + 70) },
            Vector2{ (float)(N * CELL_SIZE), (float)(i * CELL_SIZE + 70) },
            (float)thickness, BLACK);  // Horizontal lines
    }
}

// Function to check if the user clicked a button
bool isButtonClicked(int mouseX, int mouseY, Rectangle button) {
    return CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, button);
}

int main() {
    // Initialize an empty Sudoku board
    vector<vector<int>> board(N, vector<int>(N, 0));

    // Initialize Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sudoku Solver");
    SetTargetFPS(60);

    int selectedRow = 0, selectedCol = 0; // Start at the top-left corner

    // Define the solve and reset button positions and sizes (make them bigger)
    Rectangle solveButton = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 180, 130, 50 };
    Rectangle resetButton = { SCREEN_WIDTH / 2 + 40, SCREEN_HEIGHT - 180, 130, 50 };

    while (!WindowShouldClose()) {
        // Arrow key navigation with wrapping to the other side
        if (IsKeyPressed(KEY_RIGHT)) selectedCol = (selectedCol + 1) % N;   // Move right, wrap to left
        if (IsKeyPressed(KEY_LEFT)) selectedCol = (selectedCol - 1 + N) % N; // Move left, wrap to right
        if (IsKeyPressed(KEY_DOWN)) selectedRow = (selectedRow + 1) % N;     // Move down, wrap to top
        if (IsKeyPressed(KEY_UP)) selectedRow = (selectedRow - 1 + N) % N;   // Move up, wrap to bottom

        // Mouse input: Select a cell
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            int mouseX = (int)mousePos.x;
            int mouseY = (int)mousePos.y;

            if (mouseY > 70 && mouseY < CELL_SIZE * N + 70) { // Ensure clicks are within the grid
                selectedCol = mouseX / CELL_SIZE;
                selectedRow = (mouseY - 70) / CELL_SIZE;
            }
            else if (isButtonClicked(mouseX, mouseY, solveButton)) {
                solveSudoku(board);  // Solve the puzzle when the "Solve" button is clicked
            }
            else if (isButtonClicked(mouseX, mouseY, resetButton)) {
                resetBoard(board);  // Reset the board when the "Reset" button is clicked
            }
        }

        // Keyboard input: If a cell is selected, let the user input numbers
        if (selectedRow >= 0 && selectedCol >= 0 && selectedRow < N && selectedCol < N) {
            for (int key = KEY_ONE; key <= KEY_NINE; key++) {
                if (IsKeyPressed(key)) {
                    board[selectedRow][selectedCol] = key - KEY_ZERO;
                }
            }

            // Allow clearing a cell by pressing 0
            if (IsKeyPressed(KEY_ZERO)) {
                board[selectedRow][selectedCol] = 0;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the title
        DrawText("Sudoku Solver", SCREEN_WIDTH / 2 - MeasureText("Sudoku Solver", 50) / 2, 15, 50, DARKBLUE);

        // Draw the Sudoku grid
        drawGrid(board, selectedRow, selectedCol);

        // Draw the "Solve" button
        DrawRectangleRec(solveButton, DARKBLUE);
        DrawText("Solve", SCREEN_WIDTH / 2 - 130, SCREEN_HEIGHT - 170, 30, RAYWHITE);  // Centered text with a larger font

        // Draw the "Reset" button
        DrawRectangleRec(resetButton, DARKBLUE);
        DrawText("Reset", SCREEN_WIDTH / 2 + 60, SCREEN_HEIGHT - 170, 30, RAYWHITE);   // Centered text with a larger font

        // Draw instructions
        DrawText("Instructions:", 10, SCREEN_HEIGHT - 100, 20, DARKGRAY);
        DrawText("Left-click or use arrow keys to select a cell. Use 1-9", 10, SCREEN_HEIGHT - 80, 20, DARKBLUE);
        DrawText("to input numbers. Press 0 to clear the cell. Click 'Solve'", 10, SCREEN_HEIGHT - 60, 20, DARKBLUE);
        DrawText("to solve the puzzle or 'Reset' to clear the board", 10, SCREEN_HEIGHT - 40, 20, DARKBLUE);
        EndDrawing();
    }

    CloseWindow();  // Close window and OpenGL context

    return 0;
}
