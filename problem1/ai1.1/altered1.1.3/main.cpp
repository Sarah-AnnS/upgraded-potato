using namespace std;

#include <string>
#include <cstdlib>   // For rand() and srand()
#include <iostream>
#include <ctime>     // For time()

// Abstract Player class
class Player {
public:
    virtual string getName() = 0; // Pure virtual function for getting the player's name
    virtual char makeMove() = 0;  // Pure virtual function for making a move
};

// Computer player class
class ComputerPlayer : public Player {
public:
    // Computer player randomly generates a move
    char makeMove() override {
        int randMove = rand() % 3; // Generate random number between 0 and 2
        if (randMove == 1) return 'P';
        else if (randMove == 0) return 'R';
        else return 'S';
    }

    string getName() override {
        return name;
    }

    ComputerPlayer(string name) : name(name) {}

private:
    string name;
};

// Referee class
class Referee {
public:
    // Function to determine the winner of the game
    Player* refGame(Player* player1, Player* player2) {
        char move2 = player2->makeMove();
        char move1 = player1->makeMove();

        cout << player1->getName() << " chose " << move1 << endl;
        cout << player2->getName() << " chose " << move2 << endl;

        // Determine the winner
        if ( (move1 == 'P' && move2 == 'R')|| (move1 == 'R' && move2 == 'S') || (move1 == 'S' && move2 == 'P')) {
            return player1;  // Player1 wins
        } else if (move1 == move2) {
            return nullptr; // It's a tie
        } else {
            return player2;  // Player2 wins
        }
    }
};

// Human player class
class HumanPlayer : public Player {
public:
    // Human player gets move from user input
    char makeMove() override {
        cout << "Enter move (R for Rock, P for Paper, S for Scissors): ";
        char move;
        cin >> move;
        move = toupper(move);  // Convert input to uppercase to handle lowercase entries
        return move;
    }

    string getName() override {
        return name;
    }

    HumanPlayer(string name) : name(name) {}
private:
    string name;
};

// Main function
int main() {
    srand(time(0)); // Seed the random number generator

    // Create referee
    Referee referee;

    // Create players
    ComputerPlayer computer("Computer");
    HumanPlayer human("Human");

    // Play the game
    Player* winner = referee.refGame(&human, &computer);

    // Print the result
    if (winner == nullptr) {
        cout << "It's a tie!" << endl;
    } else {
        cout << winner->getName() << " wins!" << endl;
    }

    return 0;
}
