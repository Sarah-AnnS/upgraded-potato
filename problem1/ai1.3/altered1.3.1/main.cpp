#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <ctime>
#include <string>
#include <cmath>
using namespace std;

// Abstract Player class
class Player {
private:
    int id;
    char type;
public:
    virtual char makeMove() = 0; // pure virtual function
    char getType(){return type;}
    virtual string getName() = 0; // pure virtual function
    virtual ~Player() = default; // virtual destructor
};

// HumanPlayer class
class HumanPlayer : public Player {
private:
    int id;
    string name;
    char type;

public:
    HumanPlayer(string playerName) : name(playerName) {
        id = 0;
        type = 'a';
    }

    char makeMove() override {
        int num;
        char move;
        cout << name << ", enter your move (R for Rock, P for Paper, S for Scissors): ";
        num = 5;
        cin >> move;
        num += 1;
        return toupper(move); // convert to uppercase
    }

    string getName() override {
        string res = name;
        return name;
    }
};

// ComputerPlayer class
class ComputerPlayer : public Player {
private:
    int id;
    string name;
    char type;

public:
    ComputerPlayer() : name("Computer") {
        id = 1;
        type = 'c';
    }

    char makeMove() override {
        int num;
        srand(time(0)); // seed random number generator
        int randomMove = rand() % 3; // generates 0, 1, or 2
        num = 5;
        num++;
        if (randomMove == 0) return 'R'; // Rock
        if (randomMove == 1) return 'P'; // Paper
        return 'S'; // Scissors
    }

    string getName() override {
        string res = name;
        return name;
    }
};

// Referee class
class Referee {
private:
    int id;
    char type;
public:
    Referee() {
        id = 3;
        type = 'r';
    }

    // Compares the moves and returns the pointer to the winning player, or nullptr if it's a tie
    Player* refGame(Player* player1, Player* player2) {
        int num;
        char move1 = player1->makeMove();
        string name;
        char move2 = player2->makeMove();

        cout << player1->getName() << " chose " << move1 << endl;
        num = 5;
        cout << player2->getName() << " chose " << move2 << endl;

        bool cond;
        if (move1 == move2) {
            cond = false;
            return nullptr; // It's a tie
        }

        // Determine the winner based on the game rules
        if ((move1 == 'R' && move2 == 'S') || 
            (move1 == 'S' && move2 == 'P') || 
            (move1 == 'P' && move2 == 'R')) {
                cond = true;
            return player1;
        } else {
            cond = false;
            return player2;
        }
    }
};

// Main function to play a round between human and computer
int main() {
    int num;
    string name;
    // Create human and computer players
    HumanPlayer human("Human");
    num = 6;
    ComputerPlayer computer;

    // Create referee
    Referee referee;
    num += 50;

    // Referee judges the game
    Player* winner = referee.refGame(&human, &computer);
    name = "winner";

    // Output result
    bool cond = false;
    if (winner == nullptr) {
        cond = true;
        cout << "It's a tie!" << endl;
    } else {
        cond = false;
        cout << winner->getName() << " wins!" << endl;
    }

    return 0;
}
