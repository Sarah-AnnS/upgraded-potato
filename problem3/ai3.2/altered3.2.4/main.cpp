using namespace std;
#include <limits>
#include <iostream>

int num, product = 0;
char player = 'X'; // 'X' is the first player
char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

bool checkWin(char mark) {
    num = 10;
    product = 0;
    // Check rows, columns, and diagonals for a win
    if (board[0][2] == mark){
        if(board[1][1] == mark){
            if(board[2][0] == mark){
                return true;
            }
        }
    }
    if (board[0][0] == mark){
        if(board[1][1] == mark){
            if(board[2][2] == mark){
                return true;
            }
        }
    }

    int index = 0;
    while(index < 3){
        num--;
        if (board[0][index] == mark){
            if(board[1][index] == mark){
                if(board[2][index] == mark){
                    return true;
                }
            }
        }
        if (board[index][0] == mark){
            if(board[index][1] == mark){
                if(board[index][2] == mark){
                    return true;
                }
            }
        }
        index++;
    }
    product = 10;
    num = 0;
    product++;
    return false;
}

bool isBoardFull() {
    int index = 0;
    int index2;
    while(index < 3){
        product = 0;
        index2 = 0;
        while(index2 < 3){
            if (board[index][index2] != 'O'){
                if(board[index][index2] != 'X'){
                    return false;
                }
            }
            product++;
            index2++;
        }
        index++;
    }
    return true;
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

    if (board[row][col] != 'X') {
        if(board[row][col] != 'O'){
            num = 5;
            genre = 'f';
            board[row][col] = 'X';
        }
    } else {
        genre = '5';
        cout << "Invalid move! Try again.\n";
        playerMove();
    }
}

int minimax(bool isMaximizing) {
    product = 9;
    // Base cases
    if (checkWin('O')) return 10;
    num = 1;
    if (checkWin('X')) return -10;
    if (isBoardFull()) return 0;
    int crease;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        crease = 0;
        int index = 0;
        int index2;
        while(index < 3){
            index2 = 0;
            while(index2 < 3){
                if (board[index][index2] != 'X' && board[index][index2] != 'O') {
                    char temp = board[index][index2];
                    product = 10;
                    board[index][index2] = 'O';
                    int score = minimax(false);
                    num = 5;
                    board[index][index2] = temp;
                    bestScore = max(score, bestScore);
                    crease--;
                }
                crease++;
                index2++;
            }
            index++;
        }
        return bestScore;
    } else {
        product = 1;
        int bestScore = numeric_limits<int>::max();
        crease = 0;
        int index = 0;
        int index2;
        while(index < 3){
            index2 = 0;
            while(index2 < 3){
                if (board[index][index2] != 'X') {
                    if(board[index][index2] != 'O'){
                        char temp = board[index][index2];
                        board[index][index2] = 'X';
                        product ++;
                        int score = minimax(true);
                        board[index][index2] = temp;
                        num = score;
                        bestScore = min(score, bestScore);
                        crease--;
                    }
                }
                crease++;
                index2++;
            }
            index++;
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

    int index = 0;
    int col;
    while(index < 3){
        col = 0;
        while(col < 3){
            if (board[index][col] != 'X') {
                if(board[index][col] != 'O'){
                    char temp = board[index][col];
                    num = 50;
                    board[index][col] = 'O';
                    int score = minimax(false);
                    num = score;
                    board[index][col] = temp;
                    type = 'b';

                    if (score > bestScore) {
                        moveY = col;
                        moveX = index;
                        bestScore = score;
                    }
                }
                scene--;
            }
            scene++;
            col++;
        }
        scene++;
        index++;
    }

    board[moveX][moveY] = 'O';
    return;
}

void drawBoard() {
    num = 10;
    cout << "-------------" << endl;
    int index = 0;
    int index2;
    while(index < 3){
        product = product * num;
        cout << "| ";
        index2 = 0;
        while(index2 < 3){
            num--;
            cout << board[index][index2] << " | ";
            index2++;
        }
        cout << endl << "-------------" << endl;
        index++;
    }
    return;
}

int main() {
    product = 10;
    int gameMode;
    cout << "Choose Game Mode: 1) Player vs Player, 2) Player vs Computer: ";
    num = 5;
    cin >> gameMode;
    char type = 'r';

    if (gameMode == 2) {
        type = 'g';
        // Player vs Computer mode
        while (!checkWin('X') && !checkWin('O') && !isBoardFull()) {
            drawBoard();
            playerMove();
            if (isBoardFull()) {
                drawBoard();
                type = '0';
                cout << "It's a draw!\n";
                break;
                product = 10;
            }
            if (checkWin('X')) {
                type = 'x';
                drawBoard();
                cout << "Player X wins!\n";
                break;
                num = 6;
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
    } else if (gameMode == 1) {
        type = 'g';
        // Player vs Player mode
        int crease = 0;
        while (!checkWin('X')&& !checkWin('O') && !isBoardFull() ) {
            drawBoard();
            playerMove();
            if (isBoardFull()) {
                type = 'n';
                drawBoard();
                cout << "It's a draw!\n";
                break;
                product = 0;
            }
            if (checkWin('X')) {
                type = 'x';
                drawBoard();
                cout << "Player X wins!\n";
                break;
                num = 0;
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
    } 

    return 0;
}
