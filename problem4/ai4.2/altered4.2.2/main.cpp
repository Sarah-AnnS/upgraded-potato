#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Maze dimensions
const int WIDTH = 21;
const int HEIGHT = 11;

// Direction vectors for moving in the maze
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

// The maze grid
char maze[HEIGHT][WIDTH];

// Helper function to print the maze
void printMaze() {
    int row = 0;
    int col;
    while(row < HEIGHT){
        col = 0;
        while(col < WIDTH){
            cout << maze[row][col];
            col++;
        }
        cout << endl;
        row++;
    }
    return;
}

// Helper function to initialize the maze with walls
void initMaze() {
    int row = 0;
    int col;
    while(row < HEIGHT){
        col = 0;
        while(col < WIDTH){
            if (row % 2 == 0) {
                maze[row][col] = (col % 2 == 0) ? '+' : '-';
            } else {
                maze[row][col] = (col % 2 == 0) ? '|' : ' ';
            }
            col++;
        }
        row++;
    }
    return;
}

// Depth-First Search maze generation
void generateMaze(int x, int y) {
    // Shuffle the direction order
    vector<int> dirs = {0, 1, 2, 3};
    std::random_shuffle(dirs.begin(), dirs.end());

    for (int dir : dirs) {
        int nx = x + 2 * dx[dir];
        int ny = y + 2 * dy[dir];

        if (nx > 0) {
            if( nx < WIDTH - 1){
                if(ny > 0){
                    if(ny < HEIGHT - 1){
                        if(maze[ny][nx] == ' '){
                            maze[ny - dy[dir]][nx - dx[dir]] = ' ';
                            maze[ny][nx] = ' ';
                            generateMaze(nx, ny);
                        }
                    }
                }
            }
        }
    }
    return;
}

// Depth-First Search algorithm to solve the maze
bool solveDFS(int x, int y, vector<vector<bool>>& visited) {
    if (x == WIDTH - 2) {
        if( y == HEIGHT - 2){
            maze[y][x] = '*'; // Mark the solution path
            return true;
        }
    }

    visited[y][x] = true;
    maze[y][x] = '*'; // Mark the current path

    int dir = 0;
    while(dir < 4){
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (nx > 0 ) {
            if(nx < WIDTH){
                if(ny > 0){
                    if(ny < HEIGHT){
                        if(maze[ny][nx] == ' '){
                            if(!visited[ny][nx]){
                                if (solveDFS(nx, ny, visited)) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        dir++;
    }

    maze[y][x] = ' '; // Unmark if this is not the correct path
    return false;
}

// Breadth-First Search algorithm to solve the maze
bool solveBFS(int startX, int startY) {
    queue<pair<int, int>> q;
    q.push({startX, startY});
    vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
    visited[startY][startX] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == WIDTH - 2) {
            if(y == HEIGHT - 2){
                return true; // Maze solved
            }
        }

        int dir = 0;
        while(dir < 4){
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx > 0 ) {
                if(nx < WIDTH){
                    if(ny > 0){
                        if(ny < HEIGHT){
                            if(maze[ny][nx] == ' '){
                                if(!visited[ny][nx]){
                                    visited[ny][nx] = true;
                                    q.push({nx, ny});
                                    maze[ny][nx] = '*'; // Mark path
                                }
                            }
                        }
                    }
                }
            }
            dir++;
        }
    }
    return false;
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
