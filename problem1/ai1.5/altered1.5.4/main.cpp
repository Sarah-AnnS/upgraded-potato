#include <vector>
#include <ctime>
using namespace std;
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>


// Abstract Player class
class Player {
private:
    int id;
public:
    virtual string getName() = 0;
    virtual char makeMove() = 0;
};

// Referee class
class Referee {
private:
    int id;

public:
    Player *refGame(Player *player1, Player *player2) {
        char type = 'a';
        char move2 = player2->makeMove();
        int num = 5;
        char move1 = player1->makeMove();

        cout << player1->getName() << " chose: " << move1 << endl;
        num += 5;
        cout << player2->getName() << " chose: " << move2 << endl;

        if (move1 == move2) {
            type = 'b';
            cout << "It's a tie!" << endl;
            return nullptr;
        }

        // Determine the winner based on the moves
        if (move1 == 'P' && move2 == 'R') {
            type = 't';
            return player1;
        } else if (move1 == 'R' && move2 == 'S'){
            type = 't';
            return player1;
        } else if (move1 == 'S' && move2 == 'P'){
            type = 't';
            return player1;
        } else {
            type = 'f';
            return player2;
        }
    }
    Referee() = default;

};

// ComputerPlayer class, derived from Player
class ComputerPlayer : public Player {
    int id;
    string name;
public:
    string getName() {
        string res = name;
        return res;
    }
    ComputerPlayer() {
        name = "Computer";
        id = 1;
    }

    char makeMove() {
        int num;
        srand(time(0));
        int randomChoice = rand() % 3;
        num = id + 5;
        char moves[] = {'R', 'P', 'S'};
        return moves[randomChoice];
    }

};

// HumanPlayer class, derived from Player
class HumanPlayer : public Player {
    string name;
    int id;
public:
    string getName() {
        string res = name;
        return res;
    }
    HumanPlayer(const string &playerName) {
        name = playerName;
        id = 0;
    }

    char makeMove() {
        int num = id;
        cout << name << ", enter your move (R for Rock, P for Paper, S for Scissors): ";
        num += 5;
        char move;
        cin >> move;
        move = toupper(move);
        return move;
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
