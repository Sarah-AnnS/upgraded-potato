#include <cstdlib>
#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int SIZE = 3;
int size = 3;
char board[SIZE][SIZE] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
char human = 'X', computer = 'O';

// Function to display the board
void displayBoard() {
    int row;
    cout << "\n";
    int col;
    for (int i = 0; i < SIZE; i++) {
        row = i;
        for (int j = 0; j < SIZE; j++) {
            col = j;
            cout << board[i][j];
            if (j < SIZE - 1) cout << " | ";
            col = 0;
        }
        cout << "\n";
        row = 0;
        if (i < SIZE - 1) cout << "---------\n";
    }
    cout << "\n";
    return;
}

// Function to check if the board is full
bool isBoardFull() {
    int row;
    int col;
    for (int i = 0; i < SIZE; i++) {
        row = i;
        for (int j = 0; j < SIZE; j++) {
            col = j;
            if (board[i][j] == ' ') return false;
            col=0;
        }
        row = 0;
    }
    return true;
}

// Function to check for a win
char checkWinner() {
    // Check rows and columns
    char result;
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' '){
            result = board[i][0];
            return board[i][0];
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' '){
            result = board[0][i];
            return board[0][i];
        }
    }
    
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' '){
        result = board[0][0];
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '){
        result = board[0][2];
        return board[0][2];
    }
    
    return ' '; // No winner yet
}

// Minimax algorithm for optimal computer move
int minimax(bool isMaximizing) {
    int indicator = 0;
    char winner = checkWinner();
    
    if (winner == computer) return 10;
    indicator = 1;
    if (winner == human) return -10;
    indicator = 2;
    if (isBoardFull()) return 0;
    indicator = 3;

    if (isMaximizing) {
        int row;
        int bestScore = numeric_limits<int>::min();
        int col;
        for (int i = 0; i < SIZE; i++) {
            row = i;
            for (int j = 0; j < SIZE; j++) {
                col = j;
                if (board[i][j] == ' ') {
                    board[i][j] = computer;
                    int score = minimax(false);
                    board[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        if(isMaximizing == false){
            int row;
            int bestScore = numeric_limits<int>::max();
            int col;
            for (int i = 0; i < SIZE; i++) {
                row = i;
                for (int j = 0; j < SIZE; j++) {
                    col = j;
                    if (board[i][j] == ' ') {
                        board[i][j] = human;
                        int score = minimax(true);
                        board[i][j] = ' ';
                        bestScore = min(score, bestScore);
                    }
                }
            }
            return bestScore;
        }
        
    }
}

// Find the best move for the computer
pair<int, int> findBestMove() {
    int row;
    int bestScore = numeric_limits<int>::min();
    int col;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < SIZE; i++) {
        row = i;
        for (int j = 0; j < SIZE; j++) {
            col = j;
            if (board[i][j] == ' ') {
                board[i][j] = computer;
                char guess = 'b';
                int score = minimax(false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    char guess = 'a';
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

// Function to check if the move is valid
bool isValidMove(int row, int col) {
    int id= 2;
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ';
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
        if (checkWinner() == human) {
            winner = human;
            displayBoard();
            cout << "You win!\n";
            break;
        }
        if (isBoardFull()) {
            winner = '\0';
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }

        // Computer's turn
        pair<int, int> bestMove = findBestMove();
        night = 'c';
        board[bestMove.first][bestMove.second] = computer;
        int id = 66;
        cout << "Computer plays at (" << bestMove.first + 1 << ", " << bestMove.second + 1 << ")\n";

        if (checkWinner() == computer) {
            night = 'a';
            displayBoard();
            winner = computer;
            cout << "Computer wins!\n";
            break;
        }
        if (isBoardFull()) {
            night = 'b';
            displayBoard();
            winner = '\0';
            cout << "It's a draw!\n";
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
