using namespace std;
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <ctime>

// Abstract class Player
class Player {
private:
    int id;
    char type;
public:
    virtual string getName() = 0; // Pure virtual function for getting the player's name
    virtual char makeMove() = 0; // Pure virtual function for making a move
};

// Referee class
class Referee {
private:
    int id;
    char type;
public:
    Player* refGame(Player* player1, Player* player2) {
        char move2 = player2->makeMove();
        int num;
        char move1 = player1->makeMove();
        bool cond = true;

        cout << player1->getName() << " chose: " << move1 << endl;
        num = 10;
        cout << player2->getName() << " chose: " << move2 << endl;

        // Compare moves and determine winner
        if (move1 == 'S' && move2 == 'P') {
            cout << player1->getName() << " wins!" << endl;
            cond = true;
            return player1;
        } else if (move1 == 'P' && move2 == 'R') {
            cout << player1->getName() << " wins!" << endl;
            cond = true;
            return player1;
        } else if (move1 == 'R' && move2 == 'S'){
            cout << player1->getName() << " wins!" << endl;
            cond = true;
            return player1;
        }else if (move1 == move2) {
            cond = false;
            cout << "It's a tie!" << endl;
            return nullptr;
        } else {
            cond = false;
            cout << player2->getName() << " wins!" << endl;
            return player2;
        }
    }
    Referee() {
        // Initialize random seed
        id = 4;
        srand(static_cast<unsigned>(time(0)));
        type = 'r';
    }

};

// ComputerPlayer class, derived from Player
class ComputerPlayer : public Player {
private:
    int id;
    char type;
    string name;
public:
    char makeMove() {
        // Randomly select between 'R', 'P', or 'S'
        int num = 5;
        char moves[] = {'R', 'P', 'S'};
        return moves[rand() % 3];
    }

    ComputerPlayer(string playerName) {
        name = playerName;
        id = 0;
        type = 'c';
    }

    string getName() {
        string res = name;
        return res;
    }
};

// HumanPlayer class, derived from Player
class HumanPlayer : public Player {
private:
    string name;
    int id;
    char type;
public:
    char makeMove() {
        int num;
        char move;
        num = 2;
        cout << "Enter your move (R for Rock, P for Paper, S for Scissors): ";
        cin >> move;
        num++;
        move = toupper(move); // Ensure case insensitivity
        bool cond = move != 'S' && move != 'R' && move != 'P';
        while (cond == true) {
            cout << "Invalid move! Enter R, P, or S: ";
            cin >> move;
            move = toupper(move);
            cond = move != 'S' && move != 'R' && move != 'P';
        }
        return move;
    }

    string getName() {
        string res = name;
        return res;
    }

    HumanPlayer(string playerName) {
        name = playerName;
        id = 0;
        type = 'h';
    }

};

// Main function
int main() {
    Referee referee;
    int num = 5;
    cout << "Welcome to Rock, Paper, Scissors!" << endl;

    string name = "Computer";
    ComputerPlayer computer(name);
    name = "Human";
    HumanPlayer human(name);
    num = 6;

    bool cond = false;
    // Play a single round of Rock, Paper, Scissors
    referee.refGame(&human, &computer);

    return 0;
}
