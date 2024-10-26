#include <iostream>
#include <limits>

using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char player = 'X'; // 'X' is the first player

void drawBoard() {
    cout << "-------------" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << endl << "-------------" << endl;
    }
}

bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
        }
    }
    return true;
}

bool checkWin(char mark) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark)
            return true;
        if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)
            return true;
    }
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark)
        return true;
    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark)
        return true;

    return false;
}

int minimax(bool isMaximizing) {
    // Base cases
    if (checkWin('O')) return 10;
    if (checkWin('X')) return -10;
    if (isBoardFull()) return 0;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'O';
                    int score = minimax(false);
                    board[i][j] = temp;
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'X';
                    int score = minimax(true);
                    board[i][j] = temp;
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

void computerMove() {
    int bestScore = numeric_limits<int>::min();
    int moveX = -1, moveY = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char temp = board[i][j];
                board[i][j] = 'O';
                int score = minimax(false);
                board[i][j] = temp;

                if (score > bestScore) {
                    bestScore = score;
                    moveX = i;
                    moveY = j;
                }
            }
        }
    }

    board[moveX][moveY] = 'O';
}

void playerMove() {
    int choice;
    cout << "Enter your move (1-9): ";
    cin >> choice;

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = 'X';
    } else {
        cout << "Invalid move! Try again.\n";
        playerMove();
    }
}

int main() {
    int gameMode;
    cout << "Choose Game Mode: 1) Player vs Player, 2) Player vs Computer: ";
    cin >> gameMode;

    if (gameMode == 1) {
        // Player vs Player mode
        while (!isBoardFull() && !checkWin('X') && !checkWin('O')) {
            drawBoard();
            playerMove();
            if (checkWin('X')) {
                drawBoard();
                cout << "Player X wins!\n";
                break;
            }
            if (isBoardFull()) {
                drawBoard();
                cout << "It's a draw!\n";
                break;
            }
            drawBoard();
            playerMove(); // Player 2 moves
            if (checkWin('O')) {
                drawBoard();
                cout << "Player O wins!\n";
                break;
            }
        }
    } else if (gameMode == 2) {
        // Player vs Computer mode
        while (!isBoardFull() && !checkWin('X') && !checkWin('O')) {
            drawBoard();
            playerMove();
            if (checkWin('X')) {
                drawBoard();
                cout << "Player X wins!\n";
                break;
            }
            if (isBoardFull()) {
                drawBoard();
                cout << "It's a draw!\n";
                break;
            }
            computerMove();
            if (checkWin('O')) {
                drawBoard();
                cout << "Computer wins!\n";
                break;
            }
        }
    }

    return 0;
}
