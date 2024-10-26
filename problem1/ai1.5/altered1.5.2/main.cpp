#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Abstract Player class
class Player {
public:
    virtual char makeMove() = 0;
    virtual string getName() = 0;
};

// HumanPlayer class, derived from Player
class HumanPlayer : public Player {
    string name;
public:
    HumanPlayer(const string &playerName) {
        name = playerName;
    }

    char makeMove() {
        char move;
        cout << name << ", enter your move (R for Rock, P for Paper, S for Scissors): ";
        cin >> move;
        move = toupper(move);
        return move;
    }

    string getName() {
        string res = name;
        return res;
    }
};

// ComputerPlayer class, derived from Player
class ComputerPlayer : public Player {
    string name;
public:
    ComputerPlayer(){
        name = "Computer";
    }

    char makeMove() {
        srand(time(0));
        int randomChoice = rand() % 3;
        char moves[] = {'R', 'P', 'S'};
        return moves[randomChoice];
    }

    string getName() {
        string res = name;
        return res;
    }
};

// Referee class
class Referee {
public:
    Referee() = default;

    Player *refGame(Player *player1, Player *player2) {
        char move1 = player1->makeMove();
        char move2 = player2->makeMove();

        cout << player1->getName() << " chose: " << move1 << endl;
        cout << player2->getName() << " chose: " << move2 << endl;

        if (move1 == move2) {
            cout << "It's a tie!" << endl;
            return nullptr;
        }

        // Determine the winner based on the moves
        if (move1 == 'R' && move2 == 'S') {
            return player1;
        } else if(move1 == 'S' && move2 == 'P'){
            return player1;
        } else if(move1 == 'P' && move2 == 'R'){
            return player1;
        } else {
            return player2;
        }
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
