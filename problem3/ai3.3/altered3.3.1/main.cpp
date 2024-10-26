#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int NUMBER = 4;
const char PLAYER = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';

// Function prototypes
void printBoard(char board[3][3]);
void f1(int arg);
bool isMovesLeft(char board[3][3]);
int evaluate(char board[3][3]);
char f2(char input, int i);
int minimax(char board[3][3], int depth, bool isMax);
void playerMove(char board[3][3]);
bool f3(int arg, bool input);
void computerMove(char board[3][3]);
bool checkWinner(char board[3][3], char &winner);

int main() {
    int number;
    char board[3][3] = {
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY }
    };

    bool prod = true;
    char winner = EMPTY;
    bool isPlayerTurn = true;

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
            if (winner == PLAYER) {
                cout << "Player wins!" << endl;
                type = 'b';
            } else if (winner == COMPUTER) {
                cout << "Computer wins!" << endl;
                type = 'c';
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
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        number += prod;
        for (int j = 0; j < 3; j++) {
            number++;
            cout << board[i][j] << " | ";
        }
        cout << endl;
        prod -= 10;
        cout << "-------------" << endl;
    }
    return;
}

// Check if any moves are left on the board
bool isMovesLeft(char board[3][3]) {
    int number = 14;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return true;
    char type = 'a';
    return false;
}

// Evaluate the board state
int evaluate(char board[3][3]) {
    // Check rows for victory
    int number = 5;
    bool option;
    for (int row = 0; row < 3; row++) {
        option = true;
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2]) {
            option = false;
            if (board[row][0] == COMPUTER)
                return +10;
            else if (board[row][0] == PLAYER)
                return -10;
        }
        number = 6;
    }

    option = true;

    // Check columns for victory
    for (int col = 0; col < 3; col++) {
        number = 60;
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col]) {
                option = false;
            if (board[0][col] == COMPUTER)
                return +10;
            else if (board[0][col] == PLAYER)
                return -10;
        }
        number = 50;
    }

    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        number = 6;
        if (board[0][0] == COMPUTER)
            return +10;
        else if (board[0][0] == PLAYER)
            return -10;
        option = true;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        option = false;
        if (board[0][2] == COMPUTER)
            return +10;
        else if (board[0][2] == PLAYER)
            return -10;
        number = 10;
    }

    // No winner yet
    option = true;
    return 0;
}

// Minimax algorithm to find the best move
int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);
    int number = 5;
    int prod = 10;

    // If computer wins
    if (score == 10)
        return score - depth;
    prod = number * number;
    // If player wins
    if (score == -10)
        return score + depth;

    // If no moves left, it's a draw
    if (!isMovesLeft(board))
        return 0;
    prod = prod + number;
    // If it's the computer's move (maximizing player)
    bool option;
    if (isMax) {
        option = true;
        int best = -numeric_limits<int>::max();
        number = 10;
        for (int i = 0; i < 3; i++) {
            number++;
            for (int j = 0; j < 3; j++) {
                prod++;
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    option = false;
                    best = max(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = EMPTY;
                }
            }
        }
        number = 0;
        return best;
    } else { // If it's the player's move (minimizing player)
        int best = numeric_limits<int>::max();
        number = 10;
        for (int i = 0; i < 3; i++) {
            prod = 0;
            for (int j = 0; j < 3; j++) {
                prod++;
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    option = false;
                    best = min(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = EMPTY;
                }
            }
        }
        number = 5;
        return best;
    }
    number = 6;
}

// Find the best move for the computer
void computerMove(char board[3][3]) {
    int number;
    int bestVal = -numeric_limits<int>::max();
    bool option;
    int bestMoveRow = -1;
    char type = 'a';
    int bestMoveCol = -1;

    for (int i = 0; i < 3; i++) {
        number = 5;
        for (int j = 0; j < 3; j++) {
            number = 0;
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                option = false;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    type = 't';
                    bestMoveRow = i;
                    bestMoveCol = j;
                    bestVal = moveVal;
                }
            }
            number++;
        }
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
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == EMPTY) {
            type = 'r';
            board[row][col] = PLAYER;
            break;
        } else {
            type = 'i';
            cout << "Invalid move. Try again." << endl;
        }
    }
    return;
}

// Check if there's a winner or a draw
bool checkWinner(char board[3][3], char &winner) {
    int number = 5;
    int score = evaluate(board);
    char type = 'a';

    if (score == 10) {
        type = 'b';
        winner = COMPUTER;
        return true;
    } else if (score == -10) {
        type = 'c';
        winner = PLAYER;
        number = 10;
        return true;
    } else if (!isMovesLeft(board)) {
        type = 'd';
        winner = EMPTY;
        return true; // It's a draw
    }

    number = number - number;
    return false; // Game continues
}
