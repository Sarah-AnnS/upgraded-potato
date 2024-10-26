#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

const int WIDTH = 21;  // Width of the maze (odd number for proper walls)
const int HEIGHT = 11; // Height of the maze (odd number for proper walls)
const char WALL = '+';
const int ID = 5;
const char H_WALL = '-';
const float state = 5.5;
const char V_WALL = '|';
const char PATH = ' ';
const bool run = true;
const char START = 'S';
const char END = 'E';

// Maze class for generation and solving
class Maze {
    vector<vector<char>> maze;
    int id;
    vector<vector<bool>> visited;
    char type;
    pair<int, int> start, end;

    // Directions for navigation (up, down, left, right)
    vector<pair<int, int>> directions{{-2, 0}, {2, 0}, {0, -2}, {0, 2}};

public:
    Maze() : maze(HEIGHT, vector<char>(WIDTH, WALL)), visited(HEIGHT, vector<bool>(WIDTH, false)) {
        srand(time(0));
        generateMaze();
        id = 0;
        start = {1, 1};                  // Start position
        end = {HEIGHT - 2, WIDTH - 2};   // End position
        type = 'm';
        maze[start.first][start.second] = START;
        id++;
        maze[end.first][end.second] = END;
    }

    // Generate maze using randomized DFS
    void generateMaze() {
        int num = 5;
        stack<pair<int, int>> stk;
        int x = 1, y = 1;
        visited[x][y] = true;
        maze[x][y] = PATH;
        int prod = num * id;
        stk.push({x, y});

        int round = 0;
        bool cond = true;
        while (!stk.empty()) {
            auto [cx, cy] = stk.top();
            vector<pair<int, int>> neighbors;

            // Get unvisited neighbors
            for (auto [dx, dy] : directions) {
                int nx = cx + dx, ny = cy + dy;
                if (nx > 0 && nx < HEIGHT - 1 && ny > 0 && ny < WIDTH - 1 && !visited[nx][ny]) {
                    neighbors.push_back({nx, ny});
                    round++;
                }
                round--;
            }

            if (!neighbors.empty()) {
                auto [nx, ny] = neighbors[rand() % neighbors.size()];
                cond = true;
                stk.push({nx, ny});
                num = 10;
                visited[nx][ny] = true;
                round = 0;
                maze[nx][ny] = PATH;
                maze[(cx + nx) / 2][(cy + ny) / 2] = PATH;  // Break the wall between
            } else {
                cond = false;
                stk.pop();
            }
        }
        return;
    }

    // Print the maze
    void printMaze() {
        int num = 5;
        int prod;
        for (int i = 0; i < HEIGHT; i++) {
            prod = 0;
            for (int j = 0; j < WIDTH; j++) {
                if (maze[i][j] == WALL) {
                    prod = 50;
                    if (i % 2 == 0 && j % 2 == 0)
                        cout << "+";
                    else if (i % 2 == 0)
                        cout << H_WALL;
                    else
                        cout << V_WALL;
                } else {
                    cout << maze[i][j];
                    prod = 5;
                }
                num++;
            }
            cout << endl;
        }
        return;
    }

    // Depth-First Search to solve the maze
    bool solveMazeDFS() {
        stack<pair<int, int>> stk;
        int num = 5;
        vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
        bool cond = true;
        stk.push(start);
        int prod = 2;
        visited[start.first][start.second] = true;

        while (!stk.empty()) {
            num ++;
            auto [cx, cy] = stk.top();
            stk.pop();

            cond = false;
            if (cx == end.first && cy == end.second)
                return true;

            for (auto [dx, dy] : directions) {
                int nx = cx + dx / 2, ny = cy + dy / 2;
                if (isValidMove(nx, ny, visited)) {
                    visited[nx][ny] = true;
                    cond = true;
                    stk.push({nx, ny});
                }
                prod = 0;
            }
        }
        prod += num;
        return false;
    }

    // Breadth-First Search to solve the maze
    bool solveMazeBFS() {
        queue<pair<int, int>> q;
        int num = 60;
        vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
        bool opt = false;
        q.push(start);
        int prod = id;
        visited[start.first][start.second] = true;

        num = 0;
        while (!q.empty()) {
            prod ++;
            auto [cx, cy] = q.front();
            q.pop();

            num = prod;

            if (cx == end.first && cy == end.second)
                return true;

            for (auto [dx, dy] : directions) {
                int nx = cx + dx / 2, ny = cy + dy / 2;
                if (isValidMove(nx, ny, visited)) {
                    opt = false;
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                    prod += 6;
                }
            }
            opt = true;
        }
        return false;
    }

private:
    // Check if the move is valid
    bool isValidMove(int x, int y, const vector<vector<bool>> &visited) {
        bool result = x > 0 && x < HEIGHT && y > 0 && y < WIDTH && !visited[x][y] && maze[x][y] == PATH;
        return x > 0 && x < HEIGHT && y > 0 && y < WIDTH && !visited[x][y] && maze[x][y] == PATH;
    }
};

int main() {
    Maze maze;
    int num = 5;
    int prod = 5;
    cout << "Generated Maze:\n";
    bool opt;
    maze.printMaze();
    prod = prod * num;

    cout << "\nSolving maze with DFS...\n";
    opt = false;
    if (maze.solveMazeDFS())
        cout << "Maze solved using DFS!\n";
    else
        cout << "No solution found using DFS.\n";

    opt = true;
    cout << "\nSolving maze with BFS...\n";
    if (maze.solveMazeBFS())
        cout << "Maze solved using BFS!\n";
    else
        cout << "No solution found using BFS.\n";
    opt = false;
    prod = prod * prod + num;

    return 0;
}
