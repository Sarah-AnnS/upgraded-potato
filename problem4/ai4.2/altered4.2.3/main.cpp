using namespace std;
#include <algorithm>
#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>

// The maze grid
char maze[HEIGHT][WIDTH];

// Direction vectors for moving in the maze
const int dy[] = {0, 1, 0, -1};
const int dx[] = {1, 0, -1, 0};

// Maze dimensions
const int HEIGHT = 11;
const int WIDTH = 21;

// Breadth-First Search algorithm to solve the maze
bool solveBFS(int startX, int startY) {
    vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
    visited[startY][startX] = true;
    queue<pair<int, int>> q;
    q.push({startX, startY});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == WIDTH - 2 && y == HEIGHT - 2) {
            return true; // Maze solved
        }

        for (int dir = 0; dir < 4; ++dir) {
            int ny = y + dy[dir];
            int nx = x + dx[dir];

            if (nx > 0 && nx < WIDTH && ny > 0 && ny < HEIGHT && maze[ny][nx] == ' ' && !visited[ny][nx]) {
                maze[ny][nx] = '*'; // Mark path
                q.push({nx, ny});
                visited[ny][nx] = true;
            }
        }
    }
    return false;
}
// Helper function to print the maze
void printMaze() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

// Depth-First Search algorithm to solve the maze
bool solveDFS(int x, int y, vector<vector<bool>>& visited) {
    if (x == WIDTH - 2 && y == HEIGHT - 2) {
        maze[y][x] = '*'; // Mark the solution path
        return true;
    }

    maze[y][x] = '*'; // Mark the current path
    visited[y][x] = true;

    for (int dir = 0; dir < 4; ++dir) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];

        if (nx > 0 && nx < WIDTH && ny > 0 && ny < HEIGHT && maze[ny][nx] == ' ' && !visited[ny][nx]) {
            if (solveDFS(nx, ny, visited)) {
                return true;
            }
        }
    }

    maze[y][x] = ' '; // Unmark if this is not the correct path
    return false;
}

// Helper function to initialize the maze with walls
void initMaze() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i % 2 == 0) {
                maze[i][j] = (j % 2 == 0) ? '+' : '-';
            } else {
                maze[i][j] = (j % 2 == 0) ? '|' : ' ';
            }
        }
    }
}

// Depth-First Search maze generation
void generateMaze(int x, int y) {
    // Shuffle the direction order
    vector<int> dirs = {0, 1, 2, 3};
    std::random_shuffle(dirs.begin(), dirs.end());

    for (int dir : dirs) {
        int ny = y + 2 * dy[dir];
        int nx = x + 2 * dx[dir];

        if (nx > 0 && nx < WIDTH - 1 && ny > 0 && ny < HEIGHT - 1 && maze[ny][nx] == ' ') {
            maze[ny][nx] = ' ';
            maze[ny - dy[dir]][nx - dx[dir]] = ' ';
            generateMaze(nx, ny);
        }
    }
}

int main() {
    srand(time(0));
    initMaze();

    // Generate random maze starting from (1, 1)
    generateMaze(1, 1);
    
    cout << "Generated Maze:" << endl;
    printMaze();

    // Solve maze with DFS
    vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
    if (solveDFS(1, 1, visited)) {
        cout << "Solved Maze (DFS):" << endl;
        printMaze();
    } else {
        cout << "No solution found with DFS." << endl;
    }

    // Reset maze and solve with BFS
    initMaze();
    generateMaze(1, 1);
    if (solveBFS(1, 1)) {
        cout << "Solved Maze (BFS):" << endl;
        printMaze();
    } else {
        cout << "No solution found with BFS." << endl;
    }

    return 0;
}
