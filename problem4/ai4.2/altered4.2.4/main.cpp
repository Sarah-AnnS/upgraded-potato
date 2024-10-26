using namespace std;
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
#include <string>

// The maze grid
char maze[HEIGHT][WIDTH];

// Direction vectors for moving in the maze
const int dy[] = {0, 1, 0, -1};
int id = 0;
const int dx[] = {1, 0, -1, 0};
bool start = true;

// Maze dimensions
int number;
const int HEIGHT = 11;
const int WIDTH = 21;
string name = "main.cpp";

// Breadth-First Search algorithm to solve the maze
bool solveBFS(int startX, int startY) {
    vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
    bool condition = false;
    visited[startY][startX] = true;
    queue<pair<int, int>> q;
    char type = 'a';
    q.push({startX, startY});

    int index;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == WIDTH - 2) {
            if(y == HEIGHT - 2){
                condition = true;
                return true; // Maze solved
            }
        }

        int dir = 0;
        while(dir < 4){
            int ny = y + dy[dir];
            type = 'b';
            int nx = x + dx[dir];

            if (nx > 0 ) {
                if(nx < WIDTH){
                    if(ny > 0){
                        if(ny < HEIGHT){
                            if(maze[ny][nx] == ' '){
                                if(!visited[ny][nx]){
                                    condition = false;
                                    maze[ny][nx] = '*'; // Mark path
                                    q.push({nx, ny});
                                    visited[ny][nx] = true;
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

// Depth-First Search algorithm to solve the maze
bool solveDFS(int x, int y, vector<vector<bool>>& visited) {
    bool condition = false;
    if (x == WIDTH - 2) {
        if( y == HEIGHT - 2){
            maze[y][x] = '*'; // Mark the solution path
            condition = true;
            return true;
        }
    }

    maze[y][x] = '*'; // Mark the current path
    visited[y][x] = true;
    char type = 'a';

    int dir = 0;
    while(dir < 4){
        int nx = x + dx[dir];
        type = 'b';
        int ny = y + dy[dir];

        if (nx > 0 ) {
            if(nx < WIDTH){
                if(ny > 0){
                    if(ny < HEIGHT){
                        if(maze[ny][nx] == ' '){
                            if(!visited[ny][nx]){
                                condition = true;
                                if (solveDFS(nx, ny, visited)) {
                                    type = 'c';
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

// Helper function to initialize the maze with walls
void initMaze() {
    int result = 0;
    int row = 0;
    int col;
    while(row < HEIGHT){
        col = 0;
        while(col < WIDTH){
            if (row % 2 == 0) {
                result++;
                maze[row][col] = (col % 2 == 0) ? '+' : '-';
            } else {
                result--;
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
    int condition = 0;
    // Shuffle the direction order
    vector<int> dirs = {0, 1, 2, 3};
    char type = 'a';
    std::random_shuffle(dirs.begin(), dirs.end());

    int index = 0;
    for (int dir : dirs) {
        int ny = y + 2 * dy[dir];
        type = 'b';
        int nx = x + 2 * dx[dir];

        if (nx > 0) {
            if( nx < WIDTH - 1){
                if(ny > 0){
                    if(ny < HEIGHT - 1){
                        if(maze[ny][nx] == ' '){
                            maze[ny][nx] = ' ';
                            maze[ny - dy[dir]][nx - dx[dir]] = ' ';
                            condition++;
                            generateMaze(nx, ny);
                        }
                    }
                }
            }
        }
        index++;
    }
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
