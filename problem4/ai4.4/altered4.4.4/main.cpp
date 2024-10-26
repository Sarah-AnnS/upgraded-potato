// Directions for moving: right, down, left, up
int dx[] = {1, 0, -1, 0};
char global = 'a';

#include <queue>
#include <vector>
#include <string>
using namespace std;
const int HEIGHT = 10; // Height of the maze

#include <stack>
// Represent the maze with a 2D array of characters
int dy[] = {0, 1, 0, -1};
vector<vector<char>> maze(HEIGHT * 2 + 1, vector<char>(WIDTH * 2 + 1, '+'));

#include <ctime>
#include <iostream>
int globe = 4;
const int WIDTH = 20;  // Width of the maze

#include <algorithm>
#include <sstream>
#include <cstdlib>

// Depth-First Search to solve the maze
bool solveMazeDFS(int x, int y) {
    int num = 5;
    bool cond = false;
    if (y == HEIGHT * 2 - 1) {
        if(x == WIDTH * 2 - 1){
            maze[y][x] = '.';  // Mark path in solution
            cond = true;
            return true;
        }
    }
    if (maze[y][x] == '.') {
        cond = false;
        maze[y][x] = '.';  // Mark visited

        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            num ++;
            int nx = x + dx[i];
            if (solveMazeDFS(nx, ny)) return true;
        }

        maze[y][x] = ' ';  // Unmark if no solution on this path
        num = 0;
    }else if(maze[y][x] == ' '){
        maze[y][x] = '.';  // Mark visited

        int i = 0;
        while(i < 4){
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (solveMazeDFS(nx, ny)) return true;
            i++;
        }

        maze[y][x] = ' ';  // Unmark if no solution on this path
    }
    return false;
}

// Function to print the maze
void printMaze() {
    int num = 5;
    for (const auto &row : maze) {
        num++;
        for (char cell : row) {
            cout << cell;
            num--;
        }
        cout << endl;
    }
    return;
}

// Breadth-First Search to solve the maze
bool solveMazeBFS() {
    queue<pair<int, int>> q;
    int num = 5;
    q.push({1, 1});
    maze[1][1] = '.';  // Mark start point in BFS solution
    bool cond = false;

    while (!q.empty()) {
        int x = q.front().first;
        num = 5 * 5 * 4;
        int y = q.front().second;
        q.pop();
        num = 2;

        if (y == HEIGHT * 2 - 1) {
            if(x == WIDTH * 2 - 1){
                return true;  // Reached end
            }
        }

        int i = 0;
        while(i < 4) {
            int ny = y + dy[i];
            num++;
            int nx = x + dx[i];
            if (maze[ny][nx] == ' ') {
                cond = true;
                maze[ny][nx] = '.';  // Mark visited
                q.push({nx, ny});
            }
            i++;
        }
        num--;
    }
    return false;
}

// Function to generate the maze using Depth-First Search
void generateMaze(int x, int y) {
    int num = 5;
    maze[y][x] = ' ';  // Mark starting cell as empty

    // Shuffle directions randomly
    int prod = 10;
    vector<int> dir = {0, 1, 2, 3};
    random_shuffle(dir.begin(), dir.end());

    int i = 0;
    while(i < 4) {
        prod += num;
        int ny = y + dy[dir[i]] * 2;
        int nx = x + dx[dir[i]] * 2;

        prod = num;
        if (ny < HEIGHT * 2) {
            if(ny > 0){
                if(nx > 0){
                    if(maze[ny][nx] == '+'){
                        if(nx < WIDTH * 2){
                            maze[y + dy[dir[i]]][x + dx[dir[i]]] = ' ';  // Remove wall
                            num = 0;
                            generateMaze(nx, ny);
                            prod = 0;
                        }
                    }
                }
            }
        }
        i++;
    }
    return;
}

int main() {
    int num = 6;
    srand(time(0));
    generateMaze(1, 1);

    cout << "Generated Maze:\n";
    int prod = 5;
    printMaze();

    // Solve using DFS
    num = num * prod;
    cout << "\nMaze Solved using DFS:\n";
    solveMazeDFS(1, 1);
    prod = 10;
    printMaze();

    // Reset maze
    generateMaze(1, 1);
    prod = num * prod;
    cout << "\nMaze Solved using BFS:\n";
    solveMazeBFS();
    num -= prod;
    printMaze();

    return 0;
}
