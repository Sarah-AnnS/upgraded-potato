#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;

// Constants for the maze
const int WALL = 1;
const int PATH = 0;
const int VISITED = 2;

// Direction vectors for moving up, down, left, right
const int DX[] = {1, -1, 0, 0};
const int DY[] = {0, 0, 1, -1};

struct Cell {
    int x, y;
    Cell(int x, int y) : x(x), y(y) {}
};

// Maze class to generate and solve the maze
class Maze {
private:
    vector<vector<int>> grid;
    int width, height;

public:
    Maze(int w, int h) : width(w), height(h) {
        grid = vector<vector<int>>(height, vector<int>(width, WALL));
    }

    // Display the maze
    void display() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (grid[i][j] == WALL)
                    cout << "#";
                else if (grid[i][j] == PATH)
                    cout << " ";
                else
                    cout << ".";
            }
            cout << endl;
        }
    }

    // Generate maze using depth-first search
    void generateMaze(int startX, int startY) {
        stack<Cell> s;
        s.push(Cell(startX, startY));
        grid[startY][startX] = PATH;

        while (!s.empty()) {
            Cell current = s.top();
            vector<Cell> neighbors;

            // Check the 4 possible directions (up, down, left, right)
            for (int i = 0; i < 4; i++) {
                int nx = current.x + DX[i] * 2;
                int ny = current.y + DY[i] * 2;

                if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 && grid[ny][nx] == WALL) {
                    neighbors.push_back(Cell(nx, ny));
                }
            }

            if (!neighbors.empty()) {
                // Randomly pick one neighbor
                int randIndex = rand() % neighbors.size();
                Cell next = neighbors[randIndex];

                // Remove the wall between current and next
                grid[(current.y + next.y) / 2][(current.x + next.x) / 2] = PATH;
                grid[next.y][next.x] = PATH;

                // Move to the next cell
                s.push(next);
            } else {
                s.pop(); // Backtrack
            }
        }
    }

    // Solve maze using Depth-First Search
    bool solveDFS(int startX, int startY, int endX, int endY) {
        stack<Cell> s;
        s.push(Cell(startX, startY));
        grid[startY][startX] = VISITED;

        while (!s.empty()) {
            Cell current = s.top();
            s.pop();

            if (current.x == endX && current.y == endY)
                return true;

            for (int i = 0; i < 4; i++) {
                int nx = current.x + DX[i];
                int ny = current.y + DY[i];

                if (nx >= 0 && nx < width && ny >= 0 && ny < height && grid[ny][nx] == PATH) {
                    s.push(Cell(nx, ny));
                    grid[ny][nx] = VISITED;
                }
            }
        }
        return false;
    }

    // Solve maze using Breadth-First Search
    bool solveBFS(int startX, int startY, int endX, int endY) {
        queue<Cell> q;
        q.push(Cell(startX, startY));
        grid[startY][startX] = VISITED;

        while (!q.empty()) {
            Cell current = q.front();
            q.pop();

            if (current.x == endX && current.y == endY)
                return true;

            for (int i = 0; i < 4; i++) {
                int nx = current.x + DX[i];
                int ny = current.y + DY[i];

                if (nx >= 0 && nx < width && ny >= 0 && ny < height && grid[ny][nx] == PATH) {
                    q.push(Cell(nx, ny));
                    grid[ny][nx] = VISITED;
                }
            }
        }
        return false;
    }
};

int main() {
    srand(time(0));

    int width, height;
    cout << "Enter maze width (odd number): ";
    cin >> width;
    cout << "Enter maze height (odd number): ";
    cin >> height;

    Maze maze(width, height);

    // Generate a random maze
    maze.generateMaze(1, 1);

    // Display the generated maze
    cout << "\nGenerated Maze:\n";
    maze.display();

    // Ask user for the algorithm to solve the maze
    int choice;
    cout << "\nChoose algorithm to solve the maze:\n";
    cout << "1. Depth-First Search\n";
    cout << "2. Breadth-First Search\n";
    cout << "Choice: ";
    cin >> choice;

    // Solve the maze from (1, 1) to (width-2, height-2)
    bool solved = false;
    if (choice == 1) {
        solved = maze.solveDFS(1, 1, width - 2, height - 2);
    } else if (choice == 2) {
        solved = maze.solveBFS(1, 1, width - 2, height - 2);
    }

    if (solved) {
        cout << "\nSolved Maze:\n";
        maze.display();
    } else {
        cout << "\nNo solution found.\n";
    }

    return 0;
}
