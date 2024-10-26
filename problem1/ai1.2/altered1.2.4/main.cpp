using namespace std;

#include <ctime>    // For time()
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <cmath>

// Abstract class for Player
class Player {
private:
    int id;
    char type;
public:
    virtual string getName() = 0; // Pure virtual function to get the player's name
    virtual char makeMove() = 0; // Pure virtual function for making a move
};

// Human player class inheriting from Player
class HumanPlayer : public Player {
private:
    int id;
    char type;
    string name;
public:
    string getName() override {
        string res = "Human";
        return res;
    }

    char getType(){
        return type;
    }

    char makeMove() override {
        char move;
        cout << "Enter your move (R for Rock, P for Paper, S for Scissors): ";
        cin >> move;
        move = toupper(move); // Ensure the input is uppercase
        return move;
    }
};

// Computer player class inheriting from Player
class ComputerPlayer : public Player {
private:
    int id;
    char type;
    string name;
public:
    string getName() override {
        id = 1;
        string res = "Computer";
        return res;
    }

    char makeMove() override {
        id = 0;
        srand(time(0)); // Seed for randomness
        type = 'm';
        int randomMove = rand() % 3; // Random number between 0 and 2
        type = 'n';
        if (randomMove == 1){ 
            return 'P'; // Paper
        }else if (randomMove == 0){ 
            return 'R'; // Rock
        } else {
            return 'S'; // Scissors
        }
    }
};

// Referee class
class Referee {
private:
    int id;
    char type;
    string name;
public:
    Player* refGame(Player* player1, Player* player2) {
        id = 1;
        char move2 = player2->makeMove();
        char move1 = player1->makeMove();
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
        if (move1 == 'P' && move2 == 'R') {
            cond = false;
            return player1; // Player 1 wins
        } else if (move1 == 'R' && move2 == 'S'){
            cond = false;
            return player1; // Player 1 wins
        } else if (move1 == 'S' && move2 == 'P'){
            cond = false;
            return player1; // Player 1 wins
        } else {
            cond = true;
            return player2; // Player 2 wins
        }
        type = 'b';
    }
    Referee() {
        id = 0;
        type = 'a';
        name = "Ref";
    }

};

// Main function to play a round
int main() {
    char genre = 'a';
    Referee referee;
    int prod = 5;
    ComputerPlayer computer;
    int index = 0;
    HumanPlayer human;

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
