#include <iostream>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()
#include <string>
using namespace std;

// Abstract Player class
class Player {
public:
    virtual char makeMove() = 0;  // Pure virtual function for making a move
    virtual string getName() = 0; // Pure virtual function for getting the player's name
};

// Human player class
class HumanPlayer : public Player {
private:
    string name;
public:
    HumanPlayer(string name) : name(name) {}

    // Human player gets move from user input
    char makeMove() override {
        char move;
        cout << "Enter move (R for Rock, P for Paper, S for Scissors): ";
        cin >> move;
        move = toupper(move);  // Convert input to uppercase to handle lowercase entries
        return move;
    }

    string getName() override {
        return name;
    }
};

// Computer player class
class ComputerPlayer : public Player {
private:
    string name;
public:
    ComputerPlayer(string name) : name(name) {}

    // Computer player randomly generates a move
    char makeMove() override {
        int randMove = rand() % 3; // Generate random number between 0 and 2
        if (randMove == 0) return 'R';
        else if (randMove == 1) return 'P';
        else return 'S';
    }

    string getName() override {
        return name;
    }
};

// Referee class
class Referee {
public:
    // Function to determine the winner of the game
    Player* refGame(Player* player1, Player* player2) {
        char move1 = player1->makeMove();
        char move2 = player2->makeMove();

        cout << player1->getName() << " chose " << move1 << endl;
        cout << player2->getName() << " chose " << move2 << endl;

        // Determine the winner
        if (move1 == move2) {
            return nullptr; // It's a tie
        } else if ((move1 == 'R' && move2 == 'S') || 
                   (move1 == 'S' && move2 == 'P') || 
                   (move1 == 'P' && move2 == 'R')) {
            return player1;  // Player1 wins
        } else {
            return player2;  // Player2 wins
        }
    }
};

// Main function
int main() {
    srand(time(0)); // Seed the random number generator

    // Create players
    HumanPlayer human("Human");
    ComputerPlayer computer("Computer");

    // Create referee
    Referee referee;

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
