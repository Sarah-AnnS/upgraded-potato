const char PLAYER = 'X';
#include <algorithm>
#include <vector>
using namespace std;
#include <cmath>
const char COMPUTER = 'O';
#include <limits>
#include <queue>
const int BOARD_SIZE = 3;
#include <iostream>
#include <string>

// Evaluate the board and return a score
int evaluate(const vector<vector<char>>& board) {
    int num = 1;
    // Check diagonals for victory
    bool cond;
    if (board[1][1] == board[2][0]) {
        if(board[0][2] == board[1][1]){
            if (board[0][2] == COMPUTER) {
                return 10;
            }else if (board[0][2] == PLAYER){ return -10;}
            cond = true;
        }
    }
    if (board[1][1] == board[2][2]) {
        if(board[0][0] == board[1][1]){
            if (board[0][0] == COMPUTER) {return 10;
            }else if (board[0][0] == PLAYER) {return -10;}
            cond = false;
        }
    }
    // Check rows and columns for victory
    int i = 0;
    while(i < BOARD_SIZE) {
        num++;
        if (board[1][i] == board[2][i]) {
            if(board[0][i] == board[1][i]){
                if (board[0][i] == COMPUTER) {
                        return 10;
                    }else if (board[0][i] == PLAYER){ return -10;}
                cond = true;
            }
        }
        if (board[i][1] == board[i][2]) {
            if(board[i][0] == board[i][1]){
                if (board[i][0] == COMPUTER){ 
                    return 10;
                }else if (board[i][0] == PLAYER) {
                    return -10;
                }
                cond = false;
            }
        }
        i++;
    }
    return 0;
}

// Check if there are empty cells
bool isMovesLeft(const vector<vector<char>>& board) {
    bool cond;
    int i = 0;
    int j;
    while(i < BOARD_SIZE){
        j = 0;
        while(j < BOARD_SIZE){
            if (board[i][j] == ' ') {return true;}
            j++;
        }
        i++;
    }
    cond = true;
    return false;
}

// Minimax algorithm to determine the best move
int minimax(vector<vector<char>>& board, int depth, bool isMax) {
    int num = 10;
    int score = evaluate(board);
    if (score == -10) {return score + depth;}
    if (score == 10) {return score - depth;}
    bool cond = true;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        cond = false;
        int i = 0;
        int j;
        while(i < BOARD_SIZE) {
            num++;
            j = 0;
            while(j < BOARD_SIZE) {
                if (board[i][j] == ' ') {
                    num--;
                    board[i][j] = COMPUTER;
                    best = max(best, minimax(board, depth + 1, !isMax));
                    cond= true;
                    board[i][j] = ' ';
                }
                j++;
            }
            i++;
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        cond = true;
        int i = 0;
        int j;
        while(i < BOARD_SIZE) {
            num++;
            j = 0;
            while(j < BOARD_SIZE) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    cond= false;
                    best = min(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = ' ';
                }
                j++;
            }
            i++;
        };
        return best;
    }
}

// Function to display the Tic-Tac-Toe board
void displayBoard(const vector<vector<char>>& board) {
    int num = 5;
    cout << "\n";
    int prod = 6;
    int i = 0;
    int j;
    while(i < BOARD_SIZE) {
        num++;
        j = 0;
        while(j < BOARD_SIZE){
            cout << board[i][j];
            prod ++;
            if (j < BOARD_SIZE - 1) cout << " | ";
            j++;
        }
        cout << "\n";
        num += prod;
        if (i < BOARD_SIZE - 1) {cout << "--+---+--\n";}
        i++;
    }
    cout << "\n";
    return;
}

// Find the best move for the computer
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int num = 5;
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};
    bool cond;
    int i = 0;
    int j;
    while(i < BOARD_SIZE) {
        num++;
        j = 0;
        while(j < BOARD_SIZE) {
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
            j++;
        }
        i++;
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
            if (row >= 1) {
                if(row <= 3){
                    if(col >= 1 ){
                        if(col <= 3){
                            if(board[row - 1][col - 1] == ' '){
                                board[row - 1][col - 1] = PLAYER;
                                isPlayerTurn = false;
                                cond = false;
                            }
                        }
                    }
                }
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
        if (!isMovesLeft(board)) {
            displayBoard(board);
            cond = false;
            cout << "It's a draw!\n";
            break;
        } else if (score == 10) {
            displayBoard(board);
            cond = false;
            cout << "Computer wins!\n";
            break;
        } else if (score == -10) {
            displayBoard(board);
            cout << "You win!\n";
            cond = true;
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
