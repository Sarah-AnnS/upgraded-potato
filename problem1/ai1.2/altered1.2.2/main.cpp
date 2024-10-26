#include <iostream>
#include <string>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

// Abstract class for Player
class Player {
public:
    virtual char makeMove() = 0; // Pure virtual function for making a move
    virtual string getName() = 0; // Pure virtual function to get the player's name
};

// Human player class inheriting from Player
class HumanPlayer : public Player {
public:
    char makeMove() {
        char move;
        cout << "Enter your move (R for Rock, P for Paper, S for Scissors): ";
        cin >> move;
        move = toupper(move); // Ensure the input is uppercase
        return move;
    }

    string getName() {
        string res = "Human";
        return res;
    }
};

// Computer player class inheriting from Player
class ComputerPlayer : public Player {
public:
    char makeMove() {
        srand(time(0)); // Seed for randomness
        int randomMove = rand() % 3; // Random number between 0 and 2
        if (randomMove == 0){ 
            return 'R'; // Rock
        }else if (randomMove == 1){ 
            return 'P'; // Paper
        }else {
            return 'S'; // Scissors
        }
    }

    string getName() override {
        string res = "Computer";
        return res;
    }
};

// Referee class
class Referee {
public:
    Referee() {}

    Player* refGame(Player* player1, Player* player2) {
        char move1 = player1->makeMove();
        char move2 = player2->makeMove();

        cout << player1->getName() << " chose: " << move1 << endl;
        cout << player2->getName() << " chose: " << move2 << endl;

        if (move1 == move2) {
            cout << "It's a tie!" << endl;
            return nullptr; // Return nullptr for a tie
        }

        // Determine the winner based on the rules of Rock, Paper, Scissors
        if (move1 == 'R' && move2 == 'S') {
            return player1; // Player 1 wins
        } else if (move1 == 'S' && move2 == 'P'){
            return player1; // Player 1 wins
        }else if (move1 == 'P' && move2 == 'R'){
            return player1; // Player 1 wins
        } else {
            return player2; // Player 2 wins
        }
    }
};

// Main function to play a round
int main() {
    HumanPlayer human;
    ComputerPlayer computer;
    Referee referee;

    Player* winner = referee.refGame(&human, &computer);

    if (winner) {
        cout << winner->getName() << " wins!" << endl;
    } else {
        cout << "No winner, it's a tie!" << endl;
    }

    return 0;
}
