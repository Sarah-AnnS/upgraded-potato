#include <iostream>
#include <limits>

using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char player = 'X'; // 'X' is the first player

void drawBoard() {
    cout << "-------------" << endl;
    int index = 0;
    int index2;
    while(index < 3){
        cout << "| ";
        index2 = 0;
        while(index2 < 3){
            cout << board[index][index2] << " | ";
            index2++;
        }
        cout << endl << "-------------" << endl;
        index++;
    }
    return;
}

bool isBoardFull() {
    int index = 0;
    int index2;
    while(index < 3){
        index2 = 0;
        while(index2 < 3){
            if (board[index][index2] != 'X'){
                if(board[index][index2] != 'O'){
                    return false;
                }
            }
            index2++;
        }
        index++;
    }
    return true;
}

bool checkWin(char mark) {
    // Check rows, columns, and diagonals for a win
    int index = 0;
    while(index < 3){
        if (board[index][0] == mark){
            if(board[index][1] == mark){
                if(board[index][2] == mark){
                    return true;
                }
            }
        }
        if (board[0][index] == mark){
            if(board[1][index] == mark){
                if(board[2][index] == mark){
                    return true;
                }
            }
        }
        index++;
    }
    if (board[0][0] == mark){
        if(board[1][1] == mark){
            if(board[2][2] == mark){
                return true;
            }
        }
    }
    if (board[0][2] == mark){
        if(board[1][1] == mark){
            if(board[2][0] == mark){
                return true;
            }
        }
    }

    return false;
}

int minimax(bool isMaximizing) {
    // Base cases
    if (checkWin('O')) return 10;
    if (checkWin('X')) return -10;
    if (isBoardFull()) return 0;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        int index = 0;
        int index2;
        while(index < 3){
            index2 = 0;
            while(index2 < 3){
                if (board[index][index2] != 'X') {
                        if(board[index][index2] != 'O'){
                        char temp = board[index][index2];
                        board[index][index2] = 'O';
                        int score = minimax(false);
                        board[index][index2] = temp;
                        bestScore = max(score, bestScore);
                    }
                }
                index2++;
            }
            index++;
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        int index = 0;
        int index2;
        while(index < 3){
            index2 = 0;
            while(index2 < 3){
                if (board[index][index2] != 'X') {
                    if(board[index][index2] != 'O'){
                        char temp = board[index][index2];
                        board[index][index2] = 'X';
                        int score = minimax(true);
                        board[index][index2] = temp;
                        bestScore = min(score, bestScore);
                    }
                }
                index2++;
            }
            index++;
        }
        return bestScore;
    }
}

void computerMove() {
    int bestScore = numeric_limits<int>::min();
    int moveX = -1;
    int moveY = -1;

    int index = 0;
    int col;
    while(index < 3){
        col = 0;
        while(col < 3){
            if (board[index][col] != 'X') {
                if(board[index][col] != 'O'){
                    char temp = board[index][col];
                    board[index][col] = 'O';
                    int score = minimax(false);
                    board[index][col] = temp;

                    if (score > bestScore) {
                        bestScore = score;
                        moveX = index;
                        moveY = col;
                    }
                }
            }
            col++;
        }
        index++;
    }

    board[moveX][moveY] = 'O';
}

void playerMove() {
    int choice;
    cout << "Enter your move (1-9): ";
    cin >> choice;

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] != 'X' ) {
        if(board[row][col] != 'O'){
            board[row][col] = 'X';
        }
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
