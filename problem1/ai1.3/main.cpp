#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// Abstract Player class
class Player {
public:
    virtual char makeMove() = 0; // pure virtual function
    virtual string getName() = 0; // pure virtual function
    virtual ~Player() = default; // virtual destructor
};

// HumanPlayer class
class HumanPlayer : public Player {
private:
    string name;

public:
    HumanPlayer(string playerName) : name(playerName) {}

    char makeMove() override {
        char move;
        cout << name << ", enter your move (R for Rock, P for Paper, S for Scissors): ";
        cin >> move;
        return toupper(move); // convert to uppercase
    }

    string getName() override {
        return name;
    }
};

// ComputerPlayer class
class ComputerPlayer : public Player {
private:
    string name;

public:
    ComputerPlayer() : name("Computer") {}

    char makeMove() override {
        srand(time(0)); // seed random number generator
        int randomMove = rand() % 3; // generates 0, 1, or 2
        if (randomMove == 0) return 'R'; // Rock
        if (randomMove == 1) return 'P'; // Paper
        return 'S'; // Scissors
    }

    string getName() override {
        return name;
    }
};

// Referee class
class Referee {
public:
    Referee() {}

    // Compares the moves and returns the pointer to the winning player, or nullptr if it's a tie
    Player* refGame(Player* player1, Player* player2) {
        char move1 = player1->makeMove();
        char move2 = player2->makeMove();

        cout << player1->getName() << " chose " << move1 << endl;
        cout << player2->getName() << " chose " << move2 << endl;

        if (move1 == move2) {
            return nullptr; // It's a tie
        }

        // Determine the winner based on the game rules
        if ((move1 == 'R' && move2 == 'S') || 
            (move1 == 'S' && move2 == 'P') || 
            (move1 == 'P' && move2 == 'R')) {
            return player1;
        } else {
            return player2;
        }
    }
};

// Main function to play a round between human and computer
int main() {
    // Create human and computer players
    HumanPlayer human("Human");
    ComputerPlayer computer;

    // Create referee
    Referee referee;

    // Referee judges the game
    Player* winner = referee.refGame(&human, &computer);

    // Output result
    if (winner == nullptr) {
        cout << "It's a tie!" << endl;
    } else {
        cout << winner->getName() << " wins!" << endl;
    }

    return 0;
}
