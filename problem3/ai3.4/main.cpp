#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char PLAYER = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';

void displayBoard(const vector<vector<char>>& board) {
    cout << "Current board:\n";
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            cout << board[row][col];
            if (col < 2) cout << " | ";
        }
        cout << "\n";
        if (row < 2) cout << "---------\n";
    }
    cout << endl;
}

bool isMovesLeft(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return true;
    return false;
}

int evaluate(const vector<vector<char>>& board) {
    // Check rows and columns
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == PLAYER) return -10;
            else if (board[row][0] == COMPUTER) return 10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == PLAYER) return -10;
            else if (board[0][col] == COMPUTER) return 10;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == PLAYER) return -10;
        else if (board[0][0] == COMPUTER) return 10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == PLAYER) return -10;
        else if (board[0][2] == COMPUTER) return 10;
    }

    // No winner
    return 0;
}

int minimax(vector<vector<char>>& board, bool isMax) {
    int score = evaluate(board);
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    best = max(best, minimax(board, !isMax));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    best = min(best, minimax(board, !isMax));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                int moveVal = minimax(board, false);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void playerMove(vector<vector<char>>& board) {
    int row, col;
    cout << "Enter your move (row and column): ";
    cin >> row >> col;
    while (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != EMPTY) {
        cout << "Invalid move. Enter again: ";
        cin >> row >> col;
    }
    board[row][col] = PLAYER;
}

bool isGameOver(const vector<vector<char>>& board) {
    int score = evaluate(board);
    if (score == 10) {
        cout << "Computer wins!\n";
        return true;
    } else if (score == -10) {
        cout << "You win!\n";
        return true;
    } else if (!isMovesLeft(board)) {
        cout << "It's a draw!\n";
        return true;
    }
    return false;
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, EMPTY));

    cout << "Welcome to Tic-Tac-Toe! You are 'X' and the computer is 'O'.\n";

    displayBoard(board);
    while (true) {
        playerMove(board);
        displayBoard(board);
        if (isGameOver(board)) break;

        cout << "Computer is making a move...\n";
        pair<int, int> bestMove = findBestMove(board);
        board[bestMove.first][bestMove.second] = COMPUTER;
        displayBoard(board);
        if (isGameOver(board)) break;
    }

    return 0;
}
