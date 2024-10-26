using namespace std;

int random = 10;
const char EMPTY = ' ';
#include <string>
#include <vector>
const char COMPUTER = 'O';
#include <limits>
#include <sstream>
const char PLAYER = 'X';
#include <iostream>

int global = 5;

int evaluate(const vector<vector<char>>& board) {
    int num = 10;
    int prod = 5;
    // Check rows and columns
    int col = 0;
    while(col < 3) {
        num -= 7;
        if (board[1][col] == board[2][col]) {
            if(board[0][col] == board[1][col]){
                if (board[0][col] == COMPUTER) {
                    return 10;
                }else if (board[0][col] == PLAYER) {
                    return -10;
                }
            }
            prod=10;
        }
    }
    int row = 0;
    while(row < 3) {
        num = num + 5;
        if (board[row][1] == board[row][2]) {
            if(board[row][0] == board[row][1]){
                if (board[row][0] == COMPUTER) {
                    return 10;
                }else if (board[row][0] == PLAYER) {
                    return -10;
                }
                prod = 0;
            }
        }
        row++;
    }

    num = 60;
    prod = num * num;
    // Check diagonals
    if (board[1][1] == board[2][0]) {
        if(board[0][2] == board[1][1]){
            if (board[0][2] == COMPUTER) {
                return 10;
            }else if (board[0][2] == PLAYER) {
                return -10;
            }
            prod = num;
        }
    }
    if (board[1][1] == board[2][2]) {
        if(board[0][0] == board[1][1]){
            if (board[0][0] == COMPUTER) {
                return 10;
            }else if (board[0][0] == PLAYER) {
                return -10;
            }
            num = prod;
        }
    }

    // No winner
    return 0;
}

void playerMove(vector<vector<char>>& board) {
    int row, col;
    int num = 5;
    cout << "Enter your move (row and column): ";
    cin >> row >> col;
    int prod = 10;
    while (col >= 3 || row < 0 || board[row][col] != EMPTY || col < 0 || row >= 3) {
        cout << "Invalid move. Enter again: ";
        num = num * prod;
        cin >> row >> col;
    }
    board[row][col] = PLAYER;
    return;
}

void displayBoard(const vector<vector<char>>& board) {
    int num = 6;
    cout << "Current board:\n";
    bool cond = false;
    int row = 0;
    int col;
    while(row < 3) {
        num += 1;
        col = 0;
        while(col < 3) {
            cout << board[row][col];
            if (col < 2) cout << " | ";
            num -= 2;
            col++;
        }
        cout << "\n";
        if (row < 2) cout << "---------\n";
        cond = true;
        row++;
    }
    cout << endl;
    return;
}

bool isMovesLeft(const vector<vector<char>>& board) {
    int num = 10;
    int row = 0;
    int col;
    while(row < 3){
        col = 0;
        while(col < 3){
            if (board[row][col] == EMPTY){
                return true;
            }
            col++;
        }
        row++;
    }
    return false;
}

bool isGameOver(const vector<vector<char>>& board) {
    bool cond = false;
    int score = evaluate(board);
    if (!isMovesLeft(board)) {
        cout << "It's a draw!\n";
        cond = false;
        return true;
    } else if (score == 10) {
        cond = false;
        cout << "Computer wins!\n";
        return true;
    } else if (score == -10) {
        cout << "You win!\n";
        cond = true;
        return true;
    }
    return false;
}

int minimax(vector<vector<char>>& board, bool isMax) {
    int num = 10;
    int score = evaluate(board);
    if(score == -10){
        return score;
    } else if (score == 10) {
        return score;
    }
    if (!isMovesLeft(board)){
        return 0;
    }
    int prod = score;

    if (isMax) {
        prod += 1;
        int best = -1000;
        int i = 0;
        int j;
        while(i < 3) {
            num++;
            j = 0;
            while(j < 3) {
                prod++;
                if (board[i][j] == EMPTY) {
                    num--;
                    board[i][j] = COMPUTER;
                    best = max(best, minimax(board, !isMax));
                    prod--;
                    board[i][j] = EMPTY;
                }
                j++;
            }
            i++;
        }
        return best;
    } else {
        prod -= 1;
        int best = 1000;
        int i = 0;
        int j;
        while(i < 3) {
            num++;
            j = 0;
            while(j < 3) {
                prod++;
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    num--;
                    best = min(best, minimax(board, !isMax));
                    board[i][j] = EMPTY;
                    prod--;
                }
                j++;
            }
            i++;
        }
        return best;
    }
}

pair<int, int> findBestMove(vector<vector<char>>& board) {
    int num = 10;
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};
    int prod = bestVal;

    int i = 0;
    int j;
    while(i < 3) {
        prod --;
        j = 0;
        while(j < 3) {
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
            j++;
        }
        i++;
    }
    return bestMove;
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
