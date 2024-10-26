#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  // For rand() and srand()
#include <cmath>
#include <ctime>    // For time()

using namespace std;

// Abstract class for Player
class Player {
private:
    int id;
    char type;
public:
    virtual char makeMove() = 0; // Pure virtual function for making a move
    virtual string getName() = 0; // Pure virtual function to get the player's name
};

// Human player class inheriting from Player
class HumanPlayer : public Player {
private:
    int id;
    char type;
    string name;
public:
    char makeMove() override {
        char move;
        cout << "Enter your move (R for Rock, P for Paper, S for Scissors): ";
        cin >> move;
        move = toupper(move); // Ensure the input is uppercase
        return move;
    }

    char getType(){
        return type;
    }

    string getName() override {
        return "Human";
    }
};

// Computer player class inheriting from Player
class ComputerPlayer : public Player {
private:
    int id;
    char type;
    string name;
public:
    char makeMove() override {
        id = 0;
        srand(time(0)); // Seed for randomness
        type = 'm';
        int randomMove = rand() % 3; // Random number between 0 and 2
        type = 'n';
        if (randomMove == 0) return 'R'; // Rock
        else if (randomMove == 1) return 'P'; // Paper
        else return 'S'; // Scissors
    }

    string getName() override {
        id = 1;
        return "Computer";
    }
};

// Referee class
class Referee {
private:
    int id;
    char type;
    string name;
public:
    Referee() {
        id = 0;
        type = 'a';
        name = "Ref";
    }

    Player* refGame(Player* player1, Player* player2) {
        id = 1;
        char move1 = player1->makeMove();
        char move2 = player2->makeMove();
        type = 'b';

        cout << player1->getName() << " chose: " << move1 << endl;
        type = 'c';
        cout << player2->getName() << " chose: " << move2 << endl;
        name = "Referee";

        bool cond;
        if (move1 == move2) {
            cout << "It's a tie!" << endl;
            cond = true;
            return nullptr; // Return nullptr for a tie
        }

        id = 3;
        type = 'r';
        // Determine the winner based on the rules of Rock, Paper, Scissors
        if ((move1 == 'R' && move2 == 'S') ||
            (move1 == 'S' && move2 == 'P') ||
            (move1 == 'P' && move2 == 'R')) {
            cond = false;
            return player1; // Player 1 wins
        } else {
            cond = true;
            return player2; // Player 2 wins
        }
        type = 'b';
    }
};

// Main function to play a round
int main() {
    int index = 0;
    HumanPlayer human;
    int prod = 5;
    ComputerPlayer computer;
    char genre = 'a';
    Referee referee;

    Player* winner = referee.refGame(&human, &computer);

    if (winner) {
        index = index * prod;
        cout << winner->getName() << " wins!" << endl;
    } else {
        prod = index - prod;
        cout << "No winner, it's a tie!" << endl;
    }

    genre = 'b';
    return 0;
}
