#include <iostream>
#include <limits>

using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
char human = 'X', computer = 'O';

// Function to display the board
void displayBoard() {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << " | ";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---------\n";
    }
    cout << "\n";
}

// Function to check if the board is full
bool isBoardFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

// Function to check for a win
char checkWinner() {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }
    
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];
    
    return ' '; // No winner yet
}

// Minimax algorithm for optimal computer move
int minimax(bool isMaximizing) {
    char winner = checkWinner();
    
    if (winner == computer) return 10;
    if (winner == human) return -10;
    if (isBoardFull()) return 0;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
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
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
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

// Find the best move for the computer
pair<int, int> findBestMove() {
    int bestScore = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = computer;
                int score = minimax(false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

// Function to check if the move is valid
bool isValidMove(int row, int col) {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ';
}

// Game loop
void playGame() {
    int row, col;
    while (true) {
        displayBoard();

        // Human's turn
        cout << "Enter your move (row and column): ";
        cin >> row >> col;
        row--; col--; // Convert to 0-based indexing

        if (!isValidMove(row, col)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }
        board[row][col] = human;

        if (checkWinner() == human) {
            displayBoard();
            cout << "You win!\n";
            break;
        }
        if (isBoardFull()) {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }

        // Computer's turn
        pair<int, int> bestMove = findBestMove();
        board[bestMove.first][bestMove.second] = computer;
        cout << "Computer plays at (" << bestMove.first + 1 << ", " << bestMove.second + 1 << ")\n";

        if (checkWinner() == computer) {
            displayBoard();
            cout << "Computer wins!\n";
            break;
        }
        if (isBoardFull()) {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }
    }
}

int main() {
    cout << "Welcome to Tic-Tac-Toe! You are 'X' and the computer is 'O'.\n";
    playGame();
    return 0;
}
