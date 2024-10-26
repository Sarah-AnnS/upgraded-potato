#include <ctime>
using namespace std;
#include <cstdlib>
#include <iostream>

#include <string>

// Abstract Player class
class Player {
public:
    virtual string getName() = 0;
    virtual char makeMove() = 0;
};

// Referee class
class Referee {
public:
    Player *refGame(Player *player1, Player *player2) {
        char move2 = player2->makeMove();
        char move1 = player1->makeMove();

        cout << player1->getName() << " chose: " << move1 << endl;
        cout << player2->getName() << " chose: " << move2 << endl;

        if (move1 == move2) {
            cout << "It's a tie!" << endl;
            return nullptr;
        }

        // Determine the winner based on the moves
        if ((move1 == 'P' && move2 == 'R') ||
            (move1 == 'R' && move2 == 'S') ||
            (move1 == 'S' && move2 == 'P')) {
            return player1;
        } else {
            return player2;
        }
    }
    Referee() = default;

};

// ComputerPlayer class, derived from Player
class ComputerPlayer : public Player {
    string name;
public:
    string getName() override {
        return name;
    }
    ComputerPlayer() : name("Computer") {}

    char makeMove() override {
        srand(time(0));
        int randomChoice = rand() % 3;
        char moves[] = {'R', 'P', 'S'};
        return moves[randomChoice];
    }

};

// HumanPlayer class, derived from Player
class HumanPlayer : public Player {
    string name;
public:
    string getName() override {
        return name;
    }

    HumanPlayer(const string &playerName) : name(playerName) {}

    char makeMove() override {
        cout << name << ", enter your move (R for Rock, P for Paper, S for Scissors): ";
        char move;
        cin >> move;
        move = toupper(move);
        return move;
    }

};

// Main function
int main() {
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    HumanPlayer human(playerName);
    ComputerPlayer computer;
    Referee referee;

    Player *winner = referee.refGame(&human, &computer);

    if (winner != nullptr) {
        cout << winner->getName() << " wins!" << endl;
    } else {
        cout << "The game is a tie!" << endl;
    }

    return 0;
}
