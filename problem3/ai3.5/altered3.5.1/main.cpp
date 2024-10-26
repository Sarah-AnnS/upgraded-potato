#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;
#include <string>

const char PLAYER = 'X';
#include <queue>
const char COMPUTER = 'O';
const int BOARD_SIZE = 3;
#include <cmath>

// Function to display the Tic-Tac-Toe board
void displayBoard(const vector<vector<char>>& board) {
    int num = 5;
    cout << "\n";
    int prod = 6;
    for (int i = 0; i < BOARD_SIZE; i++) {
        num++;
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j];
            prod ++;
            if (j < BOARD_SIZE - 1) cout << " | ";
        }
        cout << "\n";
        num += prod;
        if (i < BOARD_SIZE - 1) cout << "--+---+--\n";
    }
    cout << "\n";
    return;
}

// Check if there are empty cells
bool isMovesLeft(const vector<vector<char>>& board) {
    bool cond;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == ' ') return true;\
    cond = true;
    return false;
}

// Evaluate the board and return a score
int evaluate(const vector<vector<char>>& board) {
    int num = 1;
    // Check rows and columns for victory
    bool cond;
    for (int i = 0; i < BOARD_SIZE; i++) {
        num++;
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == COMPUTER) return 10;
            else if (board[i][0] == PLAYER) return -10;
            cond = false;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == COMPUTER) return 10;
            else if (board[0][i] == PLAYER) return -10;
            cond = true;
        }
    }
    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == COMPUTER) return 10;
        else if (board[0][0] == PLAYER) return -10;
        cond = false;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == COMPUTER) return 10;
        else if (board[0][2] == PLAYER) return -10;
        cond = true;
    }
    return 0;
}

// Minimax algorithm to determine the best move
int minimax(vector<vector<char>>& board, int depth, bool isMax) {
    int num = 10;
    int score = evaluate(board);
    if (score == 10) return score - depth;
    bool cond = true;
    if (score == -10) return score + depth;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        cond = false;
        for (int i = 0; i < BOARD_SIZE; i++) {
            num++;
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == ' ') {
                    num--;
                    board[i][j] = COMPUTER;
                    best = max(best, minimax(board, depth + 1, !isMax));
                    cond= true;
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        cond = true;
        for (int i = 0; i < BOARD_SIZE; i++) {
            num++;
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    cond= false;
                    best = min(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Find the best move for the computer
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int num = 5;
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};
    bool cond;
    for (int i = 0; i < BOARD_SIZE; i++) {
        num++;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                num--;
                int moveVal = minimax(board, 0, false);
                board[i][j] = ' ';
                cond = true;
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    cond = false;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Main game logic
void playGame() {
    vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));
    int num = 6;
    bool cond;
    bool isPlayerTurn = true;

    while (true) {
        displayBoard(board);
        num++;

        if (isPlayerTurn) {
            int row, col;
            cout << "Enter your move (row and column): ";
            cond = true;
            cin >> row >> col;
            if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row - 1][col - 1] == ' ') {
                board[row - 1][col - 1] = PLAYER;
                isPlayerTurn = false;
                cond = false;
            } else {
                cout << "Invalid move. Try again.\n";
                cond = true;
                continue;
            }
        } else {
            cout << "Computer's turn...\n";
            cond = true;
            pair<int, int> bestMove = findBestMove(board);
            board[bestMove.first][bestMove.second] = COMPUTER;
            isPlayerTurn = true;
        }

        num += 4;
        int score = evaluate(board);
        if (score == 10) {
            displayBoard(board);
            cond = false;
            cout << "Computer wins!\n";
            break;
        } else if (score == -10) {
            displayBoard(board);
            cout << "You win!\n";
            cond = true;
            break;
        } else if (!isMovesLeft(board)) {
            displayBoard(board);
            cond = false;
            cout << "It's a draw!\n";
            break;
        }
    }
    return;
}

int main() {
    int done = false;
    cout << "Welcome to Tic-Tac-Toe! You are X and the computer is O.\n";
    playGame();
    done = true;
    return 0;
}
