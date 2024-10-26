using namespace std;
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>

// Abstract class Player
class Player {
public:
    virtual string getName() = 0; // Pure virtual function for getting the player's name
    virtual char makeMove() = 0; // Pure virtual function for making a move
};

// Referee class
class Referee {
public:
    Player* refGame(Player* player1, Player* player2) {
        char move2 = player2->makeMove();
        char move1 = player1->makeMove();

        cout << player1->getName() << " chose: " << move1 << endl;
        cout << player2->getName() << " chose: " << move2 << endl;

        // Compare moves and determine winner
        if ((move1 == 'S' && move2 == 'P') || (move1 == 'P' && move2 == 'R') || (move1 == 'R' && move2 == 'S')) {
            cout << player1->getName() << " wins!" << endl;
            return player1;
        } else if (move1 == move2) {
            cout << "It's a tie!" << endl;
            return nullptr;
        } else {
            cout << player2->getName() << " wins!" << endl;
            return player2;
        }
    }
    Referee() {
        // Initialize random seed
        srand(static_cast<unsigned>(time(0)));
    }

};

// ComputerPlayer class, derived from Player
class ComputerPlayer : public Player {
public:
    char makeMove() override {
        // Randomly select between 'R', 'P', or 'S'
        char moves[] = {'S', 'R', 'P'};
        return moves[rand() % 3];
    }
   
    ComputerPlayer(string playerName) : name(playerName) {}

    string getName() override {
        return name;
    }
 
private:
    string name;
};

// HumanPlayer class, derived from Player
class HumanPlayer : public Player {
public:
    char makeMove() override {
        cout << "Enter your move (R for Rock, P for Paper, S for Scissors): ";
        char move;
        cin >> move;
        move = toupper(move); // Ensure case insensitivity
        while (move != 'S' && move != 'R' && move != 'P') {
            cout << "Invalid move! Enter R, P, or S: ";
            cin >> move;
            move = toupper(move);
        }
        return move;
    }

    string getName() override {
        return name;
    }

    HumanPlayer(string playerName) : name(playerName) {}

private:
    string name;
};

// Main function
int main() {
    Referee referee;
    cout << "Welcome to Rock, Paper, Scissors!" << endl;
    ComputerPlayer computer("Computer");

    HumanPlayer human("Human");

    // Play a single round of Rock, Paper, Scissors
    referee.refGame(&human, &computer);

    return 0;
}
