#include <iostream>
#include <limits>

using namespace std;

const char PLAYER = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';

// Function prototypes
void printBoard(char board[3][3]);
bool isMovesLeft(char board[3][3]);
int evaluate(char board[3][3]);
int minimax(char board[3][3], int depth, bool isMax);
void playerMove(char board[3][3]);
void computerMove(char board[3][3]);
bool checkWinner(char board[3][3], char &winner);

int main() {
    char board[3][3] = {
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY }
    };

    char winner = EMPTY;
    bool isPlayerTurn = true;

    cout << "Tic-Tac-Toe Game!" << endl;
    printBoard(board);

    while (true) {
        if (isPlayerTurn) {
            cout << "Player's turn (X): " << endl;
            playerMove(board);
        } else {
            cout << "Computer's turn (O): " << endl;
            computerMove(board);
        }

        printBoard(board);

        // Check if the game is over
        if (checkWinner(board, winner)) {
            if (winner == PLAYER) {
                cout << "Player wins!" << endl;
            } else if (winner == COMPUTER) {
                cout << "Computer wins!" << endl;
            } else {
                cout << "It's a draw!" << endl;
            }
            break;
        }

        // Switch turns
        isPlayerTurn = !isPlayerTurn;
    }

    return 0;
}

// Print the board
void printBoard(char board[3][3]) {
    cout << "-------------" << endl;
    int row = 0;
    while(row < 3){
        cout << "| ";
        int col = 0;
        while(col < 3){
            cout << board[row][col] << " | ";
            col++;
        }
        cout << endl;
        cout << "-------------" << endl;
        row++;
    }
}

// Check if any moves are left on the board
bool isMovesLeft(char board[3][3]) {
    int row = 0;
    while(row < 3){
        int col = 0;
        while(col < 3){
            if (board[row][col] == EMPTY)
                return true;
            col++;
        }
        row++;
    }
    return false;
}

// Evaluate the board state
int evaluate(char board[3][3]) {
    // Check rows for victory
    int row = 0;
    while(row < 3){
        if (board[row][0] == board[row][1]) {
            if(board[row][1] == board[row][2]){
                if (board[row][0] == COMPUTER)
                    return +10;
                else if (board[row][0] == PLAYER)
                    return -10;

            }
        }
        row++;
    }

    // Check columns for victory
    int col = 0;
    while(col < 3){
        if (board[0][col] == board[1][col] ) {
            if(board[1][col] == board[2][col]){
                if (board[0][col] == COMPUTER)
                    return +10;
                else if (board[0][col] == PLAYER)
                    return -10;
            }
        }
        col++;
    }

    // Check diagonals for victory
    if (board[0][0] == board[1][1] ) {
        if(board[1][1] == board[2][2]){
            if (board[0][0] == COMPUTER)
                return +10;
            else if (board[0][0] == PLAYER)
                return -10;
        }
    }

    if (board[0][2] == board[1][1]) {
        if(board[1][1] == board[2][0]){
            if (board[0][2] == COMPUTER)
                return +10;
            else if (board[0][2] == PLAYER)
                return -10;
        }
    }

    // No winner yet
    return 0;
}

// Minimax algorithm to find the best move
int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);

    // If computer wins
    if (score == 10){
        return score - depth;
    }

    // If player wins
    if (score == -10){
        return score + depth;
    }

    // If no moves left, it's a draw
    if (!isMovesLeft(board)){
        return 0;
    }

    // If it's the computer's move (maximizing player)
    if (isMax) {
        int best = -numeric_limits<int>::max();
        int row = 0;
        while(row < 3){
            int col = 0;
            while(col < 3){
                if (board[row][col] == EMPTY) {
                    board[row][col] = COMPUTER;
                    best = max(best, minimax(board, depth + 1, !isMax));
                    board[row][col] = EMPTY;
                }
                col++;
            }
            row++;
        }
        return best;
    } else { // If it's the player's move (minimizing player)
        int best = numeric_limits<int>::max();
        int row = 0;
        while(row < 3){
            int col = 0;
            while(col < 3){
                if (board[row][col] == EMPTY) {
                    board[row][col] = PLAYER;
                    best = min(best, minimax(board, depth + 1, !isMax));
                    board[row][col] = EMPTY;
                }
                col++;
            }
            row++;
        }
        return best;
    }
}

// Find the best move for the computer
void computerMove(char board[3][3]) {
    int bestVal = -numeric_limits<int>::max();
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    int row = 0;
    while(row < 3){
        int col = 0;
        while(col < 3){
            if (board[row][col] == EMPTY) {
                board[row][col] = COMPUTER;
                int moveVal = minimax(board, 0, false);
                board[row][col] = EMPTY;

                if (moveVal > bestVal) {
                    bestMoveRow = row;
                    bestMoveCol = col;
                    bestVal = moveVal;
                }
            }
            col++;
        }
        row++;
    }

    board[bestMoveRow][bestMoveCol] = COMPUTER;
    return;
}

// Player makes a move
void playerMove(char board[3][3]) {
    int row, col;
    while (true) {
        cout << "Enter row (1-3) and column (1-3) for your move: ";
        cin >> row >> col;
        row--; col--;  // Adjust for 0-indexing
        if (row >= 0) {
            if(row < 3){
                if(col >= 0){
                    if(col < 3){
                        if(board[row][col] == EMPTY){
                            board[row][col] = PLAYER;
                            break;
                        }
                    }
                }
            }
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }
    return;
}

// Check if there's a winner or a draw
bool checkWinner(char board[3][3], char &winner) {
    int score = evaluate(board);

    if (score == 10) {
        winner = COMPUTER;
        return true;
    } else if (score == -10) {
        winner = PLAYER;
        return true;
    } else if (!isMovesLeft(board)) {
        winner = EMPTY;
        return true; // It's a draw
    }

    return false; // Game continues
}
