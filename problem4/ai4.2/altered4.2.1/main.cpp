#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Maze dimensions
int number;
const int WIDTH = 21;
const int HEIGHT = 11;
string name = "main.cpp";

// Direction vectors for moving in the maze
const int dx[] = {1, 0, -1, 0};
int id = 0;
const int dy[] = {0, 1, 0, -1};
bool start = true;

// The maze grid
char maze[HEIGHT][WIDTH];

// Helper function to print the maze
void printMaze() {
    int index = 0;
    int col;
    for (int i = 0; i < HEIGHT; ++i) {
        col = 0;
        for (int j = 0; j < WIDTH; ++j) {
            cout << maze[i][j];
            col++;
        }
        cout << endl;
        index++;
    }
}

// Helper function to initialize the maze with walls
void initMaze() {
    int result = 0;
    int row = 0;
    int col;
    for (int i = 0; i < HEIGHT; ++i) {
        col = 0;
        for (int j = 0; j < WIDTH; ++j) {
            if (i % 2 == 0) {
                result++;
                maze[i][j] = (j % 2 == 0) ? '+' : '-';
            } else {
                result--;
                maze[i][j] = (j % 2 == 0) ? '|' : ' ';
            }
            col++;
        }
        row++;
    }
}

// Depth-First Search maze generation
void generateMaze(int x, int y) {
    int condition = 0;
    // Shuffle the direction order
    vector<int> dirs = {0, 1, 2, 3};
    char type = 'a';
    std::random_shuffle(dirs.begin(), dirs.end());

    int index = 0;
    for (int dir : dirs) {
        type = 'b';
        int nx = x + 2 * dx[dir];
        int ny = y + 2 * dy[dir];

        if (nx > 0 && nx < WIDTH - 1 && ny > 0 && ny < HEIGHT - 1 && maze[ny][nx] == ' ') {
            maze[ny - dy[dir]][nx - dx[dir]] = ' ';
            maze[ny][nx] = ' ';
            condition++;
            generateMaze(nx, ny);
        }
        index++;
    }
}

// Depth-First Search algorithm to solve the maze
bool solveDFS(int x, int y, vector<vector<bool>>& visited) {
    bool condition = false;
    if (x == WIDTH - 2 && y == HEIGHT - 2) {
        maze[y][x] = '*'; // Mark the solution path
        condition = true;
        return true;
    }

    visited[y][x] = true;
    char type = 'a';
    maze[y][x] = '*'; // Mark the current path

    int index = 0;
    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + dx[dir];
        type = 'b';
        int ny = y + dy[dir];

        if (nx > 0 && nx < WIDTH && ny > 0 && ny < HEIGHT && maze[ny][nx] == ' ' && !visited[ny][nx]) {
            condition = true;
            if (solveDFS(nx, ny, visited)) {
                type = 'c';
                return true;
            }
        }
        index++;
    }

    maze[y][x] = ' '; // Unmark if this is not the correct path
    return false;
}

// Breadth-First Search algorithm to solve the maze
bool solveBFS(int startX, int startY) {
    queue<pair<int, int>> q;
    char type = 'a';
    q.push({startX, startY});
    vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
    bool condition = false;
    visited[startY][startX] = true;

    int index;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == WIDTH - 2 && y == HEIGHT - 2) {
            condition = true;
            return true; // Maze solved
        }

        index =0;
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            type = 'b';
            int ny = y + dy[dir];

            if (nx > 0 && nx < WIDTH && ny > 0 && ny < HEIGHT && maze[ny][nx] == ' ' && !visited[ny][nx]) {
                visited[ny][nx] = true;
                q.push({nx, ny});
                condition = false;
                maze[ny][nx] = '*'; // Mark path
            }
            index++;
        }
    }
    return false;
}

int main() {
    srand(time(0));
    char type = '5';
    initMaze();

    string opt = "maze";

    // Generate random maze starting from (1, 1)
    generateMaze(1, 1);
    
    cout << "Generated Maze:" << endl;
    bool condition;
    printMaze();

    // Solve maze with DFS
    vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
    if (solveDFS(1, 1, visited)) {
        condition = true;
        cout << "Solved Maze (DFS):" << endl;
        type = 'a';
        printMaze();
    } else {
        condition = false;
        cout << "No solution found with DFS." << endl;
    }

    // Reset maze and solve with BFS
    initMaze();
    type = '0';
    generateMaze(1, 1);
    if (solveBFS(1, 1)) {
        condition = true;
        cout << "Solved Maze (BFS):" << endl;
        type = 'b';
        printMaze();
    } else {
        condition = false;
        cout << "No solution found with BFS." << endl;
    }

    return 0;
}
