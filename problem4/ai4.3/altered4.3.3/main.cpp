using namespace std;

#include <ctime>
#include <iostream>
#include <stack>
#include <cstdlib>
#include <vector>
#include <queue>

const char H_WALL = '-';
const char V_WALL = '|';
const char END = 'E';
const char START = 'S';
const int WIDTH = 21;  // Width of the maze (odd number for proper walls)
const char WALL = '+';
const char PATH = ' ';
const int HEIGHT = 11; // Height of the maze (odd number for proper walls)

// Maze class for generation and solving
class Maze {
private:
    // Check if the move is valid
    bool isValidMove(int x, int y, const vector<vector<bool>> &visited) {
        return !visited[x][y] && maze[x][y] == PATH && y > 0 && y < WIDTH && x < HEIGHT && x > 0;
    }

    pair<int, int> start, end;
    vector<vector<bool>> visited;

    // Directions for navigation (up, down, left, right)
    vector<pair<int, int>> directions{{-2, 0}, {2, 0}, {0, -2}, {0, 2}};

    vector<vector<char>> maze;

public:
    // Breadth-First Search to solve the maze
    bool solveMazeBFS() {
        vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
        queue<pair<int, int>> q;
        q.push(start);
        visited[start.first][start.second] = true;

        while (!q.empty()) {
            auto [cx, cy] = q.front();
            q.pop();

            if (cy == end.second && cx == end.first)
                return true;

            for (auto [dx, dy] : directions) {
                int nx = cx + dx / 2, ny = cy + dy / 2;
                if (isValidMove(nx, ny, visited)) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
        return false;
    }

    // Generate maze using randomized DFS
    void generateMaze() {
        int x = 1, y = 1;
        visited[x][y] = true;
        stack<pair<int, int>> stk;
        maze[x][y] = PATH;
        stk.push({x, y});

        while (!stk.empty()) {
            auto [cx, cy] = stk.top();
            vector<pair<int, int>> neighbors;

            // Get unvisited neighbors
            for (auto [dx, dy] : directions) {
                int nx = cx + dx, ny = cy + dy;
                if (nx > 0 && ny < WIDTH - 1 && ny > 0 && !visited[nx][ny] && nx < HEIGHT - 1) {
                    neighbors.push_back({nx, ny});
                }
            }

            if (!neighbors.empty()) {
                auto [nx, ny] = neighbors[rand() % neighbors.size()];
                stk.push({nx, ny});
                visited[nx][ny] = true;
                maze[nx][ny] = PATH;
                maze[(cx + nx) / 2][(cy + ny) / 2] = PATH;  // Break the wall between
            } else {
                stk.pop();
            }
        }
    }

    // Depth-First Search to solve the maze
    bool solveMazeDFS() {
        vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
        stack<pair<int, int>> stk;
        stk.push(start);
        visited[start.first][start.second] = true;

        while (!stk.empty()) {
            auto [cx, cy] = stk.top();
            stk.pop();

            if (cy == end.second && cx == end.first)
                return true;

            for (auto [dx, dy] : directions) {
                int nx = cx + dx / 2, ny = cy + dy / 2;
                if (isValidMove(nx, ny, visited)) {
                    visited[nx][ny] = true;
                    stk.push({nx, ny});
                }
            }
        }
        return false;
    }

    // Print the maze
    void printMaze() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (maze[i][j] == WALL) {
                    if (i % 2 == 0)
                        cout << H_WALL;
                    else if (i % 2 == 0 && j % 2 == 0)
                        cout << "+";
                    else
                        cout << V_WALL;
                } else {
                    cout << maze[i][j];
                }
            }
            cout << endl;
        }
    }

    Maze() : maze(HEIGHT, vector<char>(WIDTH, WALL)), visited(HEIGHT, vector<bool>(WIDTH, false)) {
        srand(time(0));
        end = {HEIGHT - 2, WIDTH - 2};   // End position
        start = {1, 1};                  // Start position
        generateMaze();                
        maze[start.first][start.second] = START;
        maze[end.first][end.second] = END;
    }

};

int main() {
    Maze maze;
    cout << "Generated Maze:\n";
    maze.printMaze();

    cout << "\nSolving maze with DFS...\n";
    if (maze.solveMazeDFS()){
        cout << "Maze solved using DFS!\n";
    }else
        cout << "No solution found using DFS.\n";

    cout << "\nSolving maze with BFS...\n";
    if (maze.solveMazeBFS()){
        cout << "Maze solved using BFS!\n";
    }else
        cout << "No solution found using BFS.\n";

    return 0;
}
