#include <iostream>
#include <limits>

using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
char human = 'X', computer = 'O';

// Function to display the board
void displayBoard() {
    cout << "\n";
    int row = 0;
    int col;
    while(row < SIZE){
        col = 0;
        while(col < SIZE){
            cout << board[row][col];
            if (col < SIZE - 1) cout << " | ";
            col++;
        }            
        cout << "\n";
        if (row < SIZE - 1) cout << "---------\n";
        row++;
    }
    cout << "\n";
}

// Function to check if the board is full
bool isBoardFull() {
    int row = 0;
    int col;
    while(row < SIZE){
        col = 0;
        while(col < SIZE){
            if (board[row][col] == ' '){return false;}
            col++;
        }
        row++;
    }
    return true;
}

// Function to check for a win
char checkWinner() {
    // Check rows and columns
    int num = 0;
    while(num < SIZE){
        if (board[num][0] == board[num][1] && board[num][1] == board[num][2] && board[num][0] != ' ')
            return board[num][0];
        if (board[0][num] == board[1][num] && board[1][num] == board[2][num] && board[0][num] != ' ')
            return board[0][num];
        num++;
    }
    
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' '){
        return board[0][0];}
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '){
        return board[0][2];}
    
    return ' '; // No winner yet
}

// Minimax algorithm for optimal computer move
int minimax(bool isMaximizing) {
    char winner = checkWinner();
    
    if (winner == computer) {return 10;}
    if (winner == human) {return -10;}
    if (isBoardFull()) {return 0;}

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        int row = 0;
        int col;
        while(row < SIZE){
            col = 0;
            while(col < SIZE){
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
        int row = 0;
        int col;
        while(row < SIZE){
            col = 0;
            while(col < SIZE){
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
        return bestScore;
    }
}

// Find the best move for the computer
pair<int, int> findBestMove() {
    int bestScore = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    int row = 0;
    int col;
    while(row < SIZE){
        col = 0;
        while(col < SIZE){
            if (board[row][col] == ' ') {
                board[row][col] = computer;
                int score = minimax(false);
                board[row][col] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {row, col};
                }
            }
            col++;
        }
        row++;
    }
    return bestMove;
}

// Function to check if the move is valid
bool isValidMove(int row, int col) {
    bool a = row >= 0;
    bool b = row < SIZE;
    bool c = col >= 0;
    bool d = col < SIZE;
    bool e = board[row][col] == ' ';
    bool result = a && b && c && d && e;
    return result;
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
        else if (isBoardFull()) {
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
        else if (isBoardFull()) {
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
