#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int WIDTH = 20;  // Width of the maze
const int HEIGHT = 10; // Height of the maze

// Represent the maze with a 2D array of characters
vector<vector<char>> maze(HEIGHT * 2 + 1, vector<char>(WIDTH * 2 + 1, '+'));

// Directions for moving: right, down, left, up
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

// Function to generate the maze using Depth-First Search
void generateMaze(int x, int y) {
    maze[y][x] = ' ';  // Mark starting cell as empty

    // Shuffle directions randomly
    vector<int> dir = {0, 1, 2, 3};
    random_shuffle(dir.begin(), dir.end());

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[dir[i]] * 2;
        int ny = y + dy[dir[i]] * 2;

        if (nx > 0 && ny > 0 && nx < WIDTH * 2 && ny < HEIGHT * 2 && maze[ny][nx] == '+') {
            maze[y + dy[dir[i]]][x + dx[dir[i]]] = ' ';  // Remove wall
            generateMaze(nx, ny);
        }
    }
}

// Function to print the maze
void printMaze() {
    for (const auto &row : maze) {
        for (char cell : row) {
            cout << cell;
        }
        cout << endl;
    }
}

// Depth-First Search to solve the maze
bool solveMazeDFS(int x, int y) {
    if (x == WIDTH * 2 - 1 && y == HEIGHT * 2 - 1) {
        maze[y][x] = '.';  // Mark path in solution
        return true;
    }
    if (maze[y][x] == ' ' || maze[y][x] == '.') {
        maze[y][x] = '.';  // Mark visited

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (solveMazeDFS(nx, ny)) return true;
        }

        maze[y][x] = ' ';  // Unmark if no solution on this path
    }
    return false;
}

// Breadth-First Search to solve the maze
bool solveMazeBFS() {
    queue<pair<int, int>> q;
    q.push({1, 1});
    maze[1][1] = '.';  // Mark start point in BFS solution

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (x == WIDTH * 2 - 1 && y == HEIGHT * 2 - 1) return true;  // Reached end

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (maze[ny][nx] == ' ') {
                maze[ny][nx] = '.';  // Mark visited
                q.push({nx, ny});
            }
        }
    }
    return false;
}

int main() {
    srand(time(0));
    generateMaze(1, 1);

    cout << "Generated Maze:\n";
    printMaze();

    // Solve using DFS
    cout << "\nMaze Solved using DFS:\n";
    solveMazeDFS(1, 1);
    printMaze();

    // Reset maze
    generateMaze(1, 1);
    cout << "\nMaze Solved using BFS:\n";
    solveMazeBFS();
    printMaze();

    return 0;
}
