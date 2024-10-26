using namespace std;

#include <limits>
#include <iostream>

char human = 'X', computer = 'O';
const int SIZE = 3;
char board[SIZE][SIZE] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };

// Function to check if the move is valid
bool isValidMove(int row, int col) {
    return  board[row][col] == ' ' && row < SIZE && col < SIZE && row >= 0 && col >= 0;
}

// Function to check for a win
char checkWinner() {    
    // Check diagonals
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
    }
    
    return ' '; // No winner yet
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

// Minimax algorithm for optimal computer move
int minimax(bool isMaximizing) {
    if (isBoardFull()) return 0;
    char winner = checkWinner();
    if (winner == computer) return 10;
    if (winner == human) return -10;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    int score = minimax(false);
                    board[i][j] = computer;
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
                    int score = minimax(true);
                    board[i][j] = human;
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
    pair<int, int> bestMove = {-1, -1};
    int bestScore = numeric_limits<int>::min();

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                int score = minimax(false);
                if (score > bestScore) {
                    bestMove = {i, j};
                    bestScore = score;
                }
                board[i][j] = computer;
                board[i][j] = ' ';
            }
        }
    }
    return bestMove;
}

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
        if (isBoardFull()) {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }
        if (checkWinner() == human) {
            displayBoard();
            cout << "You win!\n";
            break;
        }

        // Computer's turn
        pair<int, int> bestMove = findBestMove();
        board[bestMove.first][bestMove.second] = computer;
        cout << "Computer plays at (" << bestMove.first + 1 << ", " << bestMove.second + 1 << ")\n";
        
        if (isBoardFull()) {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }
        if (checkWinner() == computer) {
            displayBoard();
            cout << "Computer wins!\n";
            break;
        }
    }
}

int main() {
    cout << "Welcome to Tic-Tac-Toe! You are 'X' and the computer is 'O'.\n";
    playGame();
    return 0;
}
