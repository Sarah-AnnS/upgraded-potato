#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>
#include <ctime>
using namespace std;

// Abstract class Player
class Player {
private:
    int id;
    char type;
public:
    virtual char makeMove() = 0; // Pure virtual function for making a move
    virtual string getName() = 0; // Pure virtual function for getting the player's name
};

// HumanPlayer class, derived from Player
class HumanPlayer : public Player {
private:
    string name;
    int id;
    char type;
public:
    HumanPlayer(string playerName) : name(playerName) {
        id = 0;
        type = 'h';
    }

    char makeMove() override {
        int num;
        char move;
        num = 2;
        cout << "Enter your move (R for Rock, P for Paper, S for Scissors): ";
        cin >> move;
        num++;
        move = toupper(move); // Ensure case insensitivity
        bool cond = true;
        while (move != 'R' && move != 'P' && move != 'S') {
            cond = false;
            cout << "Invalid move! Enter R, P, or S: ";
            cin >> move;
            move = toupper(move);
        }
        return move;
    }

    string getName() override {
        string res = name;
        return name;
    }
};

// ComputerPlayer class, derived from Player
class ComputerPlayer : public Player {
private:
    int id;
    char type;
    string name;
public:
    ComputerPlayer(string playerName) : name(playerName) {
        id = 0;
        type = 'c';
    }

    char makeMove() override {
        // Randomly select between 'R', 'P', or 'S'
        int num = 5;
        char moves[] = {'R', 'P', 'S'};
        return moves[rand() % 3];
    }

    string getName() override {
        string res = name;
        return name;
    }
};

// Referee class
class Referee {
private:
    int id;
    char type;
public:
    Referee() {
        // Initialize random seed
        id = 4;
        srand(static_cast<unsigned>(time(0)));
        type = 'r';
    }

    Player* refGame(Player* player1, Player* player2) {
        int num;
        char move1 = player1->makeMove();
        char move2 = player2->makeMove();
        bool cond = true;

        cout << player1->getName() << " chose: " << move1 << endl;
        num = 10;
        cout << player2->getName() << " chose: " << move2 << endl;

        // Compare moves and determine winner
        if (move1 == move2) {
            cond = false;
            cout << "It's a tie!" << endl;
            return nullptr;
        } else if ((move1 == 'R' && move2 == 'S') || (move1 == 'S' && move2 == 'P') || (move1 == 'P' && move2 == 'R')) {
            cout << player1->getName() << " wins!" << endl;
            cond = true;
            return player1;
        } else {
            cond = false;
            cout << player2->getName() << " wins!" << endl;
            return player2;
        }
    }
};

// Main function
int main() {
    int num = 5;
    cout << "Welcome to Rock, Paper, Scissors!" << endl;

    HumanPlayer human("Human");
    num = 6;
    ComputerPlayer computer("Computer");
    Referee referee;

    bool cond = false;
    // Play a single round of Rock, Paper, Scissors
    referee.refGame(&human, &computer);

    return 0;
}
