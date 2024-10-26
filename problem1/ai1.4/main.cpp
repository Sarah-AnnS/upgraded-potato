#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// Abstract class Player
class Player {
public:
    virtual char makeMove() = 0; // Pure virtual function for making a move
    virtual string getName() = 0; // Pure virtual function for getting the player's name
};

// HumanPlayer class, derived from Player
class HumanPlayer : public Player {
private:
    string name;
public:
    HumanPlayer(string playerName) : name(playerName) {}

    char makeMove() override {
        char move;
        cout << "Enter your move (R for Rock, P for Paper, S for Scissors): ";
        cin >> move;
        move = toupper(move); // Ensure case insensitivity
        while (move != 'R' && move != 'P' && move != 'S') {
            cout << "Invalid move! Enter R, P, or S: ";
            cin >> move;
            move = toupper(move);
        }
        return move;
    }

    string getName() override {
        return name;
    }
};

// ComputerPlayer class, derived from Player
class ComputerPlayer : public Player {
private:
    string name;
public:
    ComputerPlayer(string playerName) : name(playerName) {}

    char makeMove() override {
        // Randomly select between 'R', 'P', or 'S'
        char moves[] = {'R', 'P', 'S'};
        return moves[rand() % 3];
    }

    string getName() override {
        return name;
    }
};

// Referee class
class Referee {
public:
    Referee() {
        // Initialize random seed
        srand(static_cast<unsigned>(time(0)));
    }

    Player* refGame(Player* player1, Player* player2) {
        char move1 = player1->makeMove();
        char move2 = player2->makeMove();

        cout << player1->getName() << " chose: " << move1 << endl;
        cout << player2->getName() << " chose: " << move2 << endl;

        // Compare moves and determine winner
        if (move1 == move2) {
            cout << "It's a tie!" << endl;
            return nullptr;
        } else if ((move1 == 'R' && move2 == 'S') || (move1 == 'S' && move2 == 'P') || (move1 == 'P' && move2 == 'R')) {
            cout << player1->getName() << " wins!" << endl;
            return player1;
        } else {
            cout << player2->getName() << " wins!" << endl;
            return player2;
        }
    }
};

// Main function
int main() {
    cout << "Welcome to Rock, Paper, Scissors!" << endl;

    HumanPlayer human("Human");
    ComputerPlayer computer("Computer");
    Referee referee;

    // Play a single round of Rock, Paper, Scissors
    referee.refGame(&human, &computer);

    return 0;
}
