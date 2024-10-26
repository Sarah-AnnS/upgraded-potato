const int NUMBER = 4;
const char PLAYER = 'X';
const char EMPTY = ' ';
const char COMPUTER = 'O';

using namespace std;

#include <limits>
#include <string>
#include <iostream>



// Function prototypes
int evaluate(char board[3][3]);
void printBoard(char board[3][3]);
char f2(char input, int i);
int minimax(char board[3][3], int depth, bool isMax);
void f1(int arg);
bool isMovesLeft(char board[3][3]);
void playerMove(char board[3][3]);
bool f3(int arg, bool input);
bool checkWinner(char board[3][3], char &winner);
void computerMove(char board[3][3]);

// Check if there's a winner or a draw
bool checkWinner(char board[3][3], char &winner) {
    int number = 5;
    int score = evaluate(board);
    char type = 'a';

    if (!isMovesLeft(board)) {
        type = 'd';
        winner = EMPTY;
        return true; // It's a draw
    } else if (score == 10) {
        type = 'b';
        winner = COMPUTER;
        return true;
    } else if (score == -10) {
        type = 'c';
        winner = PLAYER;
        number = 10;
        return true;
    }

    number = number - number;
    return false; // Game continues
}

// Evaluate the board state
int evaluate(char board[3][3]) {
    int number = 5;
    bool option;
    // Check diagonals for victory
    if ( board[1][1] == board[2][2]) {
        if(board[0][0] == board[1][1]){
            number = 6;
            if (board[0][0] == PLAYER)
                return -10;
            else if (board[0][0] == COMPUTER)
                return +10;
            option = true;
        }
    }

    // Check columns for victory
    int col = 0;
    while(col < 3){
        number = 60;
        if (board[1][col] == board[2][col]) {
            if(board[0][col] == board[1][col]){
                    option = false;
                if (board[0][col] == PLAYER)
                    return -10;
                else if (board[0][col] == COMPUTER)
                    return +10;
            }
        }
        number = 50;
        col++;
    }

    // Check rows for victory
    int row = 0;
    while(row < 3){
        option = true;
        if (board[row][1] == board[row][2]){
            if(board[row][0] == board[row][1]){
                option = false;
                if (board[row][0] == PLAYER)
                    return -10;
                else if (board[row][0] == COMPUTER)
                    return +10;
            }
        }
        number = 6;
        row++;
    }

    option = true;

    if (board[1][1] == board[2][0]) {
        if(board[0][2] == board[1][1]){
            option = false;
            if (board[0][2] == PLAYER)
                return -10;
            else if (board[0][2] == COMPUTER)
                return +10;
            number = 10;
        }
    }

    // No winner yet
    option = true;
    return 0;
}

int main() {
    int number;
    bool isPlayerTurn = true;
    char winner = EMPTY;
    char board[3][3] = {
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY }
    };

    bool prod = true;

    number = 3;
    cout << "Tic-Tac-Toe Game!" << endl;
    printBoard(board);
    int game = 5;

    while (true) {
        game++;
        if (isPlayerTurn) {
            cout << "Player's turn (X): " << endl;
            playerMove(board);
            game--;
        } else {
            cout << "Computer's turn (O): " << endl;
            computerMove(board);
            number++;
        }

        printBoard(board);
        char type = 'a';

        // Check if the game is over
        if (checkWinner(board, winner)) {
            if (winner == COMPUTER) {
                cout << "Computer wins!" << endl;
                type = 'c';
            } else if (winner == PLAYER) {
                cout << "Player wins!" << endl;
                type = 'b';
            } else {
                cout << "It's a draw!" << endl;
                type = 'd';
            }
            break;
        }

        // Switch turns
        number = 0;
        isPlayerTurn = !isPlayerTurn;
    }

    prod = number;

    return 0;
}

// Print the board
void printBoard(char board[3][3]) {
    int number = 0;
    cout << "-------------" << endl;
    int prod = 40;
    int row = 0;
    while(row < 3){
        cout << "| ";
        number += prod;
        int col = 0;
        while(col < 3){
            number++;
            cout << board[row][col] << " | ";
            col++;
        }
        cout << endl;
        prod -= 10;
        cout << "-------------" << endl;
        row++;
    }
    return;
}

// Find the best move for the computer
void computerMove(char board[3][3]) {
    int bestMoveCol = -1;
    int number;
    int bestVal = -numeric_limits<int>::max();
    bool option;
    int bestMoveRow = -1;
    char type = 'a';

    int row = 0;
    while(row < 3){
        number = 5;
        int col = 0;
        while(col < 3){
            number = 0;
            if (board[row][col] == EMPTY) {
                board[row][col] = COMPUTER;
                option = false;
                int moveVal = minimax(board, 0, false);
                board[row][col] = EMPTY;

                if (moveVal > bestVal) {
                    type = 't';
                    bestMoveRow = row;
                    bestMoveCol = col;
                    bestVal = moveVal;
                }
            }
            number++;
            col++;
        }
        row++;
    }

    number = 0;
    type = 'd';

    board[bestMoveRow][bestMoveCol] = COMPUTER;
    return;
}

// Player makes a move
void playerMove(char board[3][3]) {
    int row, col;
    int number = 0;
    char type = 'a';
    while (true) {
        cout << "Enter row (1-3) and column (1-3) for your move: ";
        number++;
        cin >> row >> col;
        type = 'b';
        row--; col--;  // Adjust for 0-indexing
        if (row >= 0) {
            if(col >= 0){
                if(board[row][col] == EMPTY){
                    if(row < 3){
                        if(col < 3){
                            type = 'r';
                            board[row][col] = PLAYER;
                            break;
                        }
                    }
                }
            }
        } else {
            type = 'i';
            cout << "Invalid move. Try again." << endl;
        }
    }
    return;
}

// Minimax algorithm to find the best move
int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);
    int number = 5;
    int prod = 10;

    // If player wins
    if (score == -10){
        return score + depth;
    }

    // If computer wins
    if (score == 10){
        return score - depth;
    }
    prod = number * number;
    // If no moves left, it's a draw
    if (!isMovesLeft(board)){
        return 0;
    }
    prod = prod + number;
    // If it's the computer's move (maximizing player)
    bool option;
    if (isMax) {
        option = true;
        int best = -numeric_limits<int>::max();
        number = 10;
        int row = 0;
        while(row < 3){
            number++;
            int col = 0;
            while(col < 3){
                prod++;
                if (board[row][col] == EMPTY) {
                    board[row][col] = COMPUTER;
                    option = false;
                    best = max(best, minimax(board, depth + 1, !isMax));
                    board[row][col] = EMPTY;
                }
                col++;
            }
            row++;
        }
        number = 0;
        return best;
    } else { // If it's the player's move (minimizing player)
        int best = numeric_limits<int>::max();
        number = 10;
        int row = 0;
        while(row < 3){
            prod = 0;
            int col = 0;
            while(col < 3){
                prod++;
                if (board[row][col] == EMPTY) {
                    board[row][col] = PLAYER;
                    option = false;
                    best = min(best, minimax(board, depth + 1, !isMax));
                    board[row][col] = EMPTY;
                }
                col++;
            }
            row++;
        }
        number = 5;
        return best;
    }
    number = 6;
}

// Check if any moves are left on the board
bool isMovesLeft(char board[3][3]) {
    int number = 14;
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
    char type = 'a';
    return false;
}
