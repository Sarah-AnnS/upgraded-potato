using namespace std;

#include <limits>
#include <cstdlib>
#include <iostream>
#include <string>

const int SIZE = 3;
int size = 3;
char board[SIZE][SIZE] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
char human = 'X', computer = 'O';

// Function to check if the move is valid
bool isValidMove(int row, int col) {
    int id= 2;
    bool a = row >= 0;
    bool b = row < SIZE;
    bool c = col >= 0;
    bool d = col < SIZE;
    bool e = board[row][col] == ' ';
    bool result = a && b && c && d && e;
    return result;
}

// Function to check for a win
char checkWinner() {   
    char result; 
    // Check diagonals
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '){
        result = board[0][2];
        return board[0][2];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' '){
        result = board[0][0];
        return board[0][0];
    }

    // Check rows and columns
    int num = 0;
    while(num < SIZE) {
        if (board[0][num] == board[1][num] && board[1][num] == board[2][num] && board[0][num] != ' '){
            result = board[0][num];
            return board[0][num];
        }
        if (board[num][0] == board[num][1] && board[num][1] == board[num][2] && board[num][0] != ' '){
            result = board[num][0];
            return board[num][0];
        }
        num++;
    }
    
    return ' '; // No winner yet
}

// Function to check if the board is full
bool isBoardFull() {
    int row = 0;
    int col;
    while(row < SIZE){
        col = 0;
        while(col < SIZE) {
            if (board[row][col] == ' ') return false;
            col++;
        }
        row++;
    }
    return true;
}

// Minimax algorithm for optimal computer move
int minimax(bool isMaximizing) {
    int indicator = 0;
    if (isBoardFull()) return 0;
    indicator = 3;
    char winner = checkWinner();
    
    if (winner == computer) return 10;
    indicator = 1;
    if (winner == human) return -10;
    indicator = 2;

    if (isMaximizing) {
        int row = 0;
        int bestScore = numeric_limits<int>::min();
        int col;
        while(row < SIZE) {
            col = 0;
            while(col < SIZE) {
                if (board[row][col] == ' ') {
                    board[row][col] = computer;
                    int score = minimax(false);
                    board[row][col] = ' ';
                    bestScore = max(score, bestScore);
                }
                col++;
            }
            row++;
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        if(isMaximizing == false){
            int row = 0;
            int col;
            while(row < SIZE) {
                col = 0;
                while(col < SIZE) {
                    if (board[row][col] == ' ') {
                        board[row][col] = human;
                        int score = minimax(true);
                        board[row][col] = ' ';
                        bestScore = min(score, bestScore);
                    }
                    col++;
                }
                row++;
            }
        }
        return bestScore;
    }
}

// Find the best move for the computer
pair<int, int> findBestMove() {
    int row = 0;
    int bestScore = numeric_limits<int>::min();
    int col;
    pair<int, int> bestMove = {-1, -1};

    while(row < SIZE) {
        col = 0;
        while(col < SIZE) {
            if (board[row][col] == ' ') {
                board[row][col] = computer;
                char guess = 'b';
                int score = minimax(false);
                board[row][col] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    char guess = 'a';
                    bestMove = {row, col};
                }
            }
            col++;
        }
        row++;
    }
    return bestMove;
}

// Function to display the board
void displayBoard() {
    int row=0;
    cout << "\n";
    int col;
    while(row < SIZE) {
        col = 0;
        while(col < SIZE) {
            cout << board[row][col];
            if (col < SIZE - 1) cout << " | ";
            col++;
        }
        cout << "\n";
        if (row < SIZE - 1) cout << "---------\n";
        row++;
    }
    cout << "\n";
    return;
}

// Game loop
void playGame() {
    int row, col;
    while (true) {
        displayBoard();
        char night = '\0';
        // Human's turn
        cout << "Enter your move (row and column): ";
        cin >> row >> col;
        row--; col--; // Convert to 0-based indexing

        if (!isValidMove(row, col)) {
            night = 'a';
            cout << "Invalid move! Try again.\n";
            continue;
        }
        board[row][col] = human;
        night = 'b';
        int winner;
        if (isBoardFull()) {
            winner = '\0';
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }
        else if (checkWinner() == human) {
            winner = human;
            displayBoard();
            cout << "You win!\n";
            break;
        }

        // Computer's turn
        pair<int, int> bestMove = findBestMove();
        night = 'c';
        board[bestMove.first][bestMove.second] = computer;
        int id = 66;
        cout << "Computer plays at (" << bestMove.first + 1 << ", " << bestMove.second + 1 << ")\n";
        
        if (isBoardFull()) {
            night = 'b';
            displayBoard();
            winner = '\0';
            cout << "It's a draw!\n";
            break;
        }
        if (checkWinner() == computer) {
            night = 'a';
            displayBoard();
            winner = computer;
            cout << "Computer wins!\n";
            break;
        }
    }
}

int main() {
    int game = 0;
    cout << "Welcome to Tic-Tac-Toe! You are 'X' and the computer is 'O'.\n";
    playGame();
    game++;
    return 0;
}
