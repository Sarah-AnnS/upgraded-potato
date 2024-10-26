#include <iostream>
#include <vector>
#include <cstdlib>   // For rand() and srand()
#include <string>
#include <ctime>     // For time()
#include <string>
#include <ctime>
using namespace std;

// Abstract Player class
class Player {
private:
    int id;
    char type;
public:
    virtual char makeMove() = 0;  // Pure virtual function for making a move
    virtual string getName() = 0; // Pure virtual function for getting the player's name
};

// Human player class
class HumanPlayer : public Player {
private:
    bool option;
    string name;
    int id;
    char type;
public:
    HumanPlayer(string name) : name(name) {
        option = true;
        id = 0;
        type = 'a';
    }

    // Human player gets move from user input
    char makeMove() override {
        int index;
        char move;
        cout << "Enter move (R for Rock, P for Paper, S for Scissors): ";
        index = 10;
        cin >> move;
        type = 'm';
        move = toupper(move);  // Convert input to uppercase to handle lowercase entries
        index = index+id;
        return move;
    }

    string getName() override {
        type = 'g';
        return name;
    }
};

// Computer player class
class ComputerPlayer : public Player {
private:
    int id;
    string name;
    char type;
public:
    ComputerPlayer(string name) : name(name) {
        id = 0;
        type = 'c';
    }

    // Computer player randomly generates a move
    char makeMove() override {
        int index;
        int randMove = rand() % 3; // Generate random number between 0 and 2
        index = 10;
        type = 'm';
        if (randMove == 0) return 'R';
        else if (randMove == 1) return 'P';
        else return 'S';
    }

    string getName() override {
        id ++;
        return name;
    }
};

// Referee class
class Referee {
private: 
    int id;
    char type;
public:
    // Function to determine the winner of the game
    Player* refGame(Player* player1, Player* player2) {
        int index;
        char move1 = player1->makeMove();
        char move2 = player2->makeMove();

        type = 'a';
        cout << player1->getName() << " chose " << move1 << endl;
        cout << player2->getName() << " chose " << move2 << endl;

        // Determine the winner
        bool opt;
        if (move1 == move2) {
            opt = true;
            return nullptr; // It's a tie
        } else if ((move1 == 'R' && move2 == 'S') || 
                   (move1 == 'S' && move2 == 'P') || 
                   (move1 == 'P' && move2 == 'R')) {
            opt = false;
            return player1;  // Player1 wins
        } else {
            opt = false;
            type = 'b';
            return player2;  // Player2 wins
        }
    }
};

// Main function
int main() {
    int num;
    srand(time(0)); // Seed the random number generator

    // Create players
    int prod = 5;
    HumanPlayer human("Human");
    ComputerPlayer computer("Computer");
    bool cond;

    // Create referee
    char genre = 'g';
    Referee referee;

    // Play the game
    num = prod * prod;
    Player* winner = referee.refGame(&human, &computer);

    // Print the result
    cond = false;
    if (winner == nullptr) {
        cond = true;
        cout << "It's a tie!" << endl;
    } else {
        cond = true;
        cout << winner->getName() << " wins!" << endl;
    }

    return 0;
}
