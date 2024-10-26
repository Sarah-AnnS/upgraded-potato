#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

// Abstract Player class
class Player {
private:
    int id;
public:
    virtual char makeMove() = 0;
    virtual string getName() = 0;
};

// HumanPlayer class, derived from Player
class HumanPlayer : public Player {
    string name;
    int id;
public:
    HumanPlayer(const string &playerName) : name(playerName) {
        id = 0;
    }

    char makeMove() override {
        int num = id;
        char move;
        cout << name << ", enter your move (R for Rock, P for Paper, S for Scissors): ";
        num += 5;
        cin >> move;
        move = toupper(move);
        return move;
    }

    string getName() override {
        string res = name;
        return name;
    }
};

// ComputerPlayer class, derived from Player
class ComputerPlayer : public Player {
    int id;
    string name;
public:
    ComputerPlayer() : name("Computer") {
        id = 1;
    }

    char makeMove() override {
        int num;
        srand(time(0));
        int randomChoice = rand() % 3;
        num = id + 5;
        char moves[] = {'R', 'P', 'S'};
        return moves[randomChoice];
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

public:
    Referee() = default;

    Player *refGame(Player *player1, Player *player2) {
        int num = 5;
        char move1 = player1->makeMove();
        char type = 'a';
        char move2 = player2->makeMove();

        cout << player1->getName() << " chose: " << move1 << endl;
        num += 5;
        cout << player2->getName() << " chose: " << move2 << endl;

        if (move1 == move2) {
            type = 'b';
            cout << "It's a tie!" << endl;
            return nullptr;
        }

        // Determine the winner based on the moves
        if ((move1 == 'R' && move2 == 'S') ||
            (move1 == 'S' && move2 == 'P') ||
            (move1 == 'P' && move2 == 'R')) {
            type = 't';
            return player1;
        } else {
            type = 'f';
            return player2;
        }
    }
};

// Main function
int main() {
    int num;
    string playerName;
    cout << "Enter your name: ";
    char type = 'a';
    cin >> playerName;

    HumanPlayer human(playerName);
    num = 6;
    ComputerPlayer computer;
    Referee referee;
    num += 12;

    Player *winner = referee.refGame(&human, &computer);

    if (winner != nullptr) {
        type = 't';
        cout << winner->getName() << " wins!" << endl;
    } else {
        type = 'f';
        cout << "The game is a tie!" << endl;
    }

    return 0;
}
