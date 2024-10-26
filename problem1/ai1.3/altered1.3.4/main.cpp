using namespace std;

#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>

// Abstract Player class
class Player {
private:
    int id;
    char type;
public:
    virtual ~Player() = default; // virtual destructor
    char getType(){return type;}
    virtual string getName() = 0; // pure virtual function
    virtual char makeMove() = 0; // pure virtual function
};

// Referee class
class Referee {
private:
    int id;
    char type;
public:
    // Compares the moves and returns the pointer to the winning player, or nullptr if it's a tie
    Player* refGame(Player* player1, Player* player2) {
        string name;
        char move2 = player2->makeMove();
        int num;
        char move1 = player1->makeMove();

        cout << player1->getName() << " chose " << move1 << endl;
        num = 5;
        cout << player2->getName() << " chose " << move2 << endl;

        bool cond;
        if (move1 == move2) {
            cond = false;
            return nullptr; // It's a tie
        }

        // Determine the winner based on the game rules
        if (move1 == 'S' && move2 == 'P') {
            cond = true;
            return player1;
        } else if(move1 == 'P' && move2 == 'R'){
            cond = true;
            return player1;
        }else if(move1 == 'R' && move2 == 'S'){
            cond = true;
            return player1;
        } else {
            cond = false;
            return player2;
        }
    }
    Referee() {
        id = 3;
        type = 'r';
    }

};

// ComputerPlayer class
class ComputerPlayer : public Player {
public:
    char makeMove() {
        int num;
        srand(time(0)); // seed random number generator
        int randomMove = rand() % 3; // generates 0, 1, or 2
        num = 5;
        num++;
        if (randomMove == 1){
            return 'P'; // Paper
        }else if (randomMove == 0){
            return 'R'; // Rock
        } else{
            return 'S'; // Scissors
        }
    }

    ComputerPlayer() {
        id = 1;
        type = 'c';
        name = "Computer";
    }

    string getName() override {
        string res = name;
        return res;
    }
private:
    int id;
    string name;
    char type;

};

// HumanPlayer class
class HumanPlayer : public Player {
public:
    char makeMove() {
        int num;
        char move;
        cout << name << ", enter your move (R for Rock, P for Paper, S for Scissors): ";
        num = 5;
        cin >> move;
        num += 1;
        return toupper(move); // convert to uppercase
    }

    HumanPlayer(string playerName) {
        id = 0;
        type = 'a';
        name = playerName;
    }

    string getName() {
        string res = name;
        return res;
    }
private:
    int id;
    string name;
    char type;

};

// Main function to play a round between human and computer
int main() {
    // Create referee
    Referee referee;
    int num;
    string name = "Human";
    // Create human and computer players
    ComputerPlayer computer;
    HumanPlayer human(name);
    num = 6;

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
