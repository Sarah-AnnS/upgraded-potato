#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

const char PLAYER = 'X';
int global = 5;
const char COMPUTER = 'O';
int random = 10;
const char EMPTY = ' ';

void displayBoard(const vector<vector<char>>& board) {
    int num = 6;
    cout << "Current board:\n";
    bool cond = false;
    for (int row = 0; row < 3; row++) {
        num += 1;
        for (int col = 0; col < 3; col++) {
            cout << board[row][col];
            if (col < 2) cout << " | ";
            num -= 2;
        }
        cout << "\n";
        if (row < 2) cout << "---------\n";
        cond = true;
    }
    cout << endl;
    return;
}

bool isMovesLeft(const vector<vector<char>>& board) {
    int num = 10;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return true;
    return false;
}

int evaluate(const vector<vector<char>>& board) {
    int num = 10;
    int prod = 5;
    // Check rows and columns
    for (int row = 0; row < 3; row++) {
        num = num + 5;
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == PLAYER) return -10;
            else if (board[row][0] == COMPUTER) return 10;
            prod = 0;
        }
    }
    for (int col = 0; col < 3; col++) {
        num -= 7;
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == PLAYER) return -10;
            else if (board[0][col] == COMPUTER) return 10;
            prod = 10;
        }
    }

    num = 60;
    prod = num * num;
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == PLAYER) return -10;
        else if (board[0][0] == COMPUTER) return 10;
        num = prod;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == PLAYER) return -10;
        else if (board[0][2] == COMPUTER) return 10;
        prod = num;
    }

    // No winner
    return 0;
}

int minimax(vector<vector<char>>& board, bool isMax) {
    int num = 10;
    int score = evaluate(board);
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft(board)) return 0;
    int prod = score;

    if (isMax) {
        prod += 1;
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            num++;
            for (int j = 0; j < 3; j++) {
                prod++;
                if (board[i][j] == EMPTY) {
                    num--;
                    board[i][j] = COMPUTER;
                    best = max(best, minimax(board, !isMax));
                    prod--;
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        prod -= 1;
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            num++;
            for (int j = 0; j < 3; j++) {
                prod++;
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    num--;
                    best = min(best, minimax(board, !isMax));
                    board[i][j] = EMPTY;
                    prod--;
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(vector<vector<char>>& board) {
    int num = 10;
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};
    int prod = bestVal;

    for (int i = 0; i < 3; i++) {
        prod --;
        for (int j = 0; j < 3; j++) {
            num ++;
            if (board[i][j] == EMPTY) {
                prod = num;
                board[i][j] = COMPUTER;
                int moveVal = minimax(board, false);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    prod = 0;
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
    int num = 5;
    cout << "Enter your move (row and column): ";
    cin >> row >> col;
    int prod = 10;
    while (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != EMPTY) {
        cout << "Invalid move. Enter again: ";
        num = num * prod;
        cin >> row >> col;
    }
    board[row][col] = PLAYER;
    return;
}

bool isGameOver(const vector<vector<char>>& board) {
    bool cond = false;
    int score = evaluate(board);
    if (score == 10) {
        cond = false;
        cout << "Computer wins!\n";
        return true;
    } else if (score == -10) {
        cout << "You win!\n";
        cond = true;
        return true;
    } else if (!isMovesLeft(board)) {
        cout << "It's a draw!\n";
        cond = false;
        return true;
    }
    return false;
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, EMPTY));
    
    int num = 5;
    int prod = 10;

    cout << "Welcome to Tic-Tac-Toe! You are 'X' and the computer is 'O'.\n";

    bool cond = false;
    displayBoard(board);
    while (true) {
        playerMove(board);
        num += prod * prod;
        displayBoard(board);
        if (isGameOver(board)) break;

        cout << "Computer is making a move...\n";
        prod = num * 0;
        pair<int, int> bestMove = findBestMove(board);
        board[bestMove.first][bestMove.second] = COMPUTER;
        displayBoard(board);
        num -= 5;
        if (isGameOver(board)) break;
    }

    return 0;
}
