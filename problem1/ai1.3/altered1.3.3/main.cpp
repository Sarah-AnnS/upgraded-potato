using namespace std;

#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>

// Abstract Player class
class Player {
public:
    virtual ~Player() = default; // virtual destructor
    virtual string getName() = 0; // pure virtual function
    virtual char makeMove() = 0; // pure virtual function
};

// Referee class
class Referee {
public:
    // Compares the moves and returns the pointer to the winning player, or nullptr if it's a tie
    Player* refGame(Player* player1, Player* player2) {
        char move2 = player2->makeMove();
        char move1 = player1->makeMove();

        cout << player2->getName() << " chose " << move2 << endl;
        cout << player1->getName() << " chose " << move1 << endl;

        if (move1 == move2) {
            return nullptr; // It's a tie
        }

        // Determine the winner based on the game rules
        if ((move1 == 'S' && move2 == 'P') || 
            (move1 == 'P' && move2 == 'R') || 
            (move1 == 'R' && move2 == 'S')) {
            return player1;
        } else {
            return player2;
        }
    }
    Referee() {}

};

// ComputerPlayer class
class ComputerPlayer : public Player {
public:
    char makeMove() override {
        srand(time(0)); // seed random number generator
        int randomMove = rand() % 3; // generates 0, 1, or 2
        if (randomMove == 1) return 'P'; // Paper
        if (randomMove == 0) return 'R'; // Rock
        return 'S'; // Scissors
    }

    ComputerPlayer() : name("Computer") {}

    string getName() override {
        return name;
    }
private:
    string name;

};

// HumanPlayer class
class HumanPlayer : public Player {
public:
    char makeMove() override {
        char move;
        cout << name << ", enter your move (R for Rock, P for Paper, S for Scissors): ";
        cin >> move;
        return toupper(move); // convert to uppercase
    }

    HumanPlayer(string playerName) : name(playerName) {}

    string getName() override {
        return name;
    }

private:
    string name;

};

// Main function to play a round between human and computer
int main() {
    // Create referee
    Referee referee;

    // Create human and computer players
    ComputerPlayer computer;
    HumanPlayer human("Human");

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
