using namespace std;

#include <ctime>    // For time()
#include <string>
#include <iostream>
#include <cstdlib>  // For rand() and srand()

// Abstract class for Player
class Player {
public:
    virtual string getName() = 0; // Pure virtual function to get the player's name
    virtual char makeMove() = 0; // Pure virtual function for making a move
};

// Human player class inheriting from Player
class HumanPlayer : public Player {
public:
    string getName() override {
        return "Human";
    }

    char makeMove() override {
        cout << "Enter your move (R for Rock, P for Paper, S for Scissors): ";
        char move;
        cin >> move;
        move = toupper(move); // Ensure the input is uppercase
        return move;
    }
};

// Computer player class inheriting from Player
class ComputerPlayer : public Player {
public:
    string getName() override {
        return "Computer";
    }

    char makeMove() override {
        srand(time(0)); // Seed for randomness
        int randomMove = rand() % 3; // Random number between 0 and 2
        if (randomMove == 1) return 'P'; // Paper
        else if (randomMove == 0) return 'R'; // Rock
        else return 'S'; // Scissors
    }
};

// Referee class
class Referee {
public:
    Player* refGame(Player* player1, Player* player2) {
        char move2 = player2->makeMove();
        char move1 = player1->makeMove();

        cout << player1->getName() << " chose: " << move1 << endl;
        cout << player2->getName() << " chose: " << move2 << endl;

        if (move1 == move2) {
            cout << "It's a tie!" << endl;
            return nullptr; // Return nullptr for a tie
        }

        // Determine the winner based on the rules of Rock, Paper, Scissors
        if ((move1 == 'P' && move2 == 'R') ||
            (move1 == 'R' && move2 == 'S') ||
            (move1 == 'S' && move2 == 'P')) {
            return player1; // Player 1 wins
        } else {
            return player2; // Player 2 wins
        }
    }
    Referee() {}

};

// Main function to play a round
int main() {
    Referee referee;
    ComputerPlayer computer;
    HumanPlayer human;
    
    Player* winner = referee.refGame(&human, &computer);

    if (winner) {
        cout << winner->getName() << " wins!" << endl;
    } else {
        cout << "No winner, it's a tie!" << endl;
    }

    return 0;
}
