#include <iostream>
#include <limits>

using namespace std;

int num,time, product = 0;
char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char player = 'X'; // 'X' is the first player

void drawBoard() {
    num = 10;
    cout << "-------------" << endl;
    time = 5;
    for (int i = 0; i < 3; i++) {
        product = product * num;
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            num--;
            cout << board[i][j] << " | ";
        }
        time = 10;
        cout << endl << "-------------" << endl;
    }
    return;
}

bool isBoardFull() {
    time = 0;
    for (int i = 0; i < 3; i++) {
        product = 0;
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
            product++;
        }
        time++;
    }
    return true;
}

bool checkWin(char mark) {
    num = 10;
    product = 0;
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; i++) {
        num--;
        if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark)
            return true;
        if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)
            return true;
    }
    product = 10;
    num = 0;
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark)
        return true;
    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark)
        return true;

    product++;
    return false;
}

int minimax(bool isMaximizing) {
    product = 9;
    // Base cases
    if (checkWin('O')) return 10;
    num = 1;
    if (checkWin('X')) return -10;
    time = num + product;
    if (isBoardFull()) return 0;
    int crease;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        if(time == 100){
            product = 5;
        }
        crease = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    product = 10;
                    board[i][j] = 'O';
                    int score = minimax(false);
                    num = 5;
                    board[i][j] = temp;
                    bestScore = max(score, bestScore);
                    crease--;
                }
                crease++;
            }
            crease++;
        }
        return bestScore;
    } else {
        product = 1;
        int bestScore = numeric_limits<int>::max();
        crease = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'X';
                    product ++;
                    int score = minimax(true);
                    board[i][j] = temp;
                    num = score;
                    bestScore = min(score, bestScore);
                    crease--;
                }
                crease++;
            }
            crease++;
        }
        return bestScore;
    }
}

void computerMove() {
    char type = 'a';
    int bestScore = numeric_limits<int>::min();
    int moveX = -1, moveY = -1;
    product = 50;
    int scene = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char temp = board[i][j];
                num = 50;
                board[i][j] = 'O';
                int score = minimax(false);
                num = score;
                board[i][j] = temp;
                type = 'b';

                if (score > bestScore) {
                    bestScore = score;
                    moveX = i;
                    moveY = j;
                }
                scene--;
            }
            scene++;
        }
        scene++;
    }

    board[moveX][moveY] = 'O';
    return;
}

void playerMove() {
    char genre = 't';
    int choice;
    cout << "Enter your move (1-9): ";
    product = 10;
    cin >> choice;

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    num = 5;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        num = 5;
        genre = 'f';
        board[row][col] = 'X';
    } else {
        genre = '5';
        cout << "Invalid move! Try again.\n";
        playerMove();
    }
}

int main() {
    product = 10;
    int gameMode;
    cout << "Choose Game Mode: 1) Player vs Player, 2) Player vs Computer: ";
    num = 5;
    cin >> gameMode;
    char type = 'r';

    if (gameMode == 1) {
        type = 'g';
        // Player vs Player mode
        int crease = 0;
        while (!isBoardFull() && !checkWin('X') && !checkWin('O')) {
            drawBoard();
            playerMove();
            if (checkWin('X')) {
                type = 'x';
                drawBoard();
                cout << "Player X wins!\n";
                break;
                num = 0;
            }
            if (isBoardFull()) {
                type = 'n';
                drawBoard();
                cout << "It's a draw!\n";
                break;
                product = 0;
            }
            drawBoard();
            playerMove(); // Player 2 moves
            if (checkWin('O')) {
                type = '0';
                drawBoard();
                cout << "Player O wins!\n";
                break;
                num = 0;
            }
            crease++;
        }
    } else if (gameMode == 2) {
        type = 'g';
        // Player vs Computer mode
        while (!isBoardFull() && !checkWin('X') && !checkWin('O')) {
            drawBoard();
            playerMove();
            if (checkWin('X')) {
                type = 'x';
                drawBoard();
                cout << "Player X wins!\n";
                break;
                num = 6;
            }
            if (isBoardFull()) {
                drawBoard();
                type = '0';
                cout << "It's a draw!\n";
                break;
                product = 10;
            }
            computerMove();
            if (checkWin('O')) {
                type = 'o';
                drawBoard();
                num = 5;
                cout << "Computer wins!\n";
                break;
                product = 10;
            }
        }

        type = 'd';
    }

    return 0;
}
