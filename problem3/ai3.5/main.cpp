#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char PLAYER = 'X';
const char COMPUTER = 'O';
const int BOARD_SIZE = 3;

// Function to display the Tic-Tac-Toe board
void displayBoard(const vector<vector<char>>& board) {
    cout << "\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j];
            if (j < BOARD_SIZE - 1) cout << " | ";
        }
        cout << "\n";
        if (i < BOARD_SIZE - 1) cout << "--+---+--\n";
    }
    cout << "\n";
}

// Check if there are empty cells
bool isMovesLeft(const vector<vector<char>>& board) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == ' ') return true;
    return false;
}

// Evaluate the board and return a score
int evaluate(const vector<vector<char>>& board) {
    // Check rows and columns for victory
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == COMPUTER) return 10;
            else if (board[i][0] == PLAYER) return -10;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == COMPUTER) return 10;
            else if (board[0][i] == PLAYER) return -10;
        }
    }
    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == COMPUTER) return 10;
        else if (board[0][0] == PLAYER) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == COMPUTER) return 10;
        else if (board[0][2] == PLAYER) return -10;
    }
    return 0;
}

// Minimax algorithm to determine the best move
int minimax(vector<vector<char>>& board, int depth, bool isMax) {
    int score = evaluate(board);
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = COMPUTER;
                    best = max(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
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
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                int moveVal = minimax(board, 0, false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove = {i, j};
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
    bool isPlayerTurn = true;

    while (true) {
        displayBoard(board);

        if (isPlayerTurn) {
            int row, col;
            cout << "Enter your move (row and column): ";
            cin >> row >> col;
            if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row - 1][col - 1] == ' ') {
                board[row - 1][col - 1] = PLAYER;
                isPlayerTurn = false;
            } else {
                cout << "Invalid move. Try again.\n";
                continue;
            }
        } else {
            cout << "Computer's turn...\n";
            pair<int, int> bestMove = findBestMove(board);
            board[bestMove.first][bestMove.second] = COMPUTER;
            isPlayerTurn = true;
        }

        int score = evaluate(board);
        if (score == 10) {
            displayBoard(board);
            cout << "Computer wins!\n";
            break;
        } else if (score == -10) {
            displayBoard(board);
            cout << "You win!\n";
            break;
        } else if (!isMovesLeft(board)) {
            displayBoard(board);
            cout << "It's a draw!\n";
            break;
        }
    }
}

int main() {
    cout << "Welcome to Tic-Tac-Toe! You are X and the computer is O.\n";
    playGame();
    return 0;
}
