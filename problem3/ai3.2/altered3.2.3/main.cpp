using namespace std;
#include <limits>
#include <iostream>

char player = 'X'; // 'X' is the first player
char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

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

bool checkWin(char mark) {
    // Check rows, columns, and diagonals for a win
    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark)
        return true;
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark)
        return true;

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)
            return true;
        if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark)
            return true;
    }
    return false;
}

void computerMove() {
    int moveY = -1, moveX = -1;
    int bestScore = numeric_limits<int>::min();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char temp = board[i][j];
                board[i][j] = 'O';
                int score = minimax(false);
                board[i][j] = temp;

                if (score > bestScore) {
                    moveY = j;
                    moveX = i;
                    bestScore = score;
                }
            }
        }
    }

    board[moveX][moveY] = 'O';
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

bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'O' && board[i][j] != 'X')
                return false;
        }
    }
    return true;
}

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

int main() {
    cout << "Choose Game Mode: 1) Player vs Player, 2) Player vs Computer: ";
    int gameMode;
    cin >> gameMode;

    if (gameMode == 2) {
        // Player vs Computer mode
        while (!checkWin('X') && !checkWin('O') && !isBoardFull()) {
            drawBoard();
            playerMove();
            if (isBoardFull()) {
                drawBoard();
                cout << "It's a draw!\n";
                break;
            }
            if (checkWin('X')) {
                drawBoard();
                cout << "Player X wins!\n";
                break;
            }
            computerMove();
            if (checkWin('O')) {
                drawBoard();
                cout << "Computer wins!\n";
                break;
            }
        }
    } else if (gameMode == 1) {
        // Player vs Player mode
        while ( !checkWin('X') && !checkWin('O')  && !isBoardFull()) {
            drawBoard();
            playerMove();
            if (isBoardFull()) {
                drawBoard();
                cout << "It's a draw!\n";
                break;
            }
            if (checkWin('X')) {
                drawBoard();
                cout << "Player X wins!\n";
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
    }

    return 0;
}
