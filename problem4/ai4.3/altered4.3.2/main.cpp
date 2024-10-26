#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

const int WIDTH = 21;  // Width of the maze (odd number for proper walls)
const int HEIGHT = 11; // Height of the maze (odd number for proper walls)
const char WALL = '+';
const char H_WALL = '-';
const char V_WALL = '|';
const char PATH = ' ';
const char START = 'S';
const char END = 'E';

// Maze class for generation and solving
class Maze {
    vector<vector<char>> maze;
    vector<vector<bool>> visited;
    pair<int, int> start, end;

    // Directions for navigation (up, down, left, right)
    vector<pair<int, int>> directions{{-2, 0}, {2, 0}, {0, -2}, {0, 2}};

public:
    Maze() : maze(HEIGHT, vector<char>(WIDTH, WALL)), visited(HEIGHT, vector<bool>(WIDTH, false)) {
        srand(time(0));
        generateMaze();
        start = {1, 1};                  // Start position
        end = {HEIGHT - 2, WIDTH - 2};   // End position
        maze[start.first][start.second] = START;
        maze[end.first][end.second] = END;
    }

    // Generate maze using randomized DFS
    void generateMaze() {
        stack<pair<int, int>> stk;
        int x = 1, y = 1;
        visited[x][y] = true;
        maze[x][y] = PATH;
        stk.push({x, y});

        while (!stk.empty()) {
            auto [cx, cy] = stk.top();
            vector<pair<int, int>> neighbors;

            // Get unvisited neighbors
            for (auto [dx, dy] : directions) {
                int nx = cx + dx, ny = cy + dy;
                if (nx > 0) {
                    if(nx < HEIGHT - 1){
                        if(ny > 0){
                            if(ny < WIDTH - 1 ){
                                if(!visited[nx][ny]){
                                    neighbors.push_back({nx, ny});
                                }
                            }
                        }
                    }
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

    // Print the maze
    void printMaze() {
        int row = 0;
        while(row < HEIGHT){
            int col = 0;
            while(col < WIDTH){
                if (maze[row][col] == WALL) {
                    if (row % 2 == 0){
                        if(col % 2 == 0){
                            cout << "+";
                        }
                    }
                    else if (row % 2 == 0)
                        cout << H_WALL;
                    else
                        cout << V_WALL;
                } else {
                    cout << maze[row][col];
                }
                col++;
            }
            cout << endl;
            row++;
        }
    }

    // Depth-First Search to solve the maze
    bool solveMazeDFS() {
        stack<pair<int, int>> stk;
        vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
        stk.push(start);
        visited[start.first][start.second] = true;

        while (!stk.empty()) {
            auto [cx, cy] = stk.top();
            stk.pop();

            if (cx == end.first){
                if(cy == end.second){
                    return true;
                }
            }

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

    // Breadth-First Search to solve the maze
    bool solveMazeBFS() {
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
        q.push(start);
        visited[start.first][start.second] = true;

        while (!q.empty()) {
            auto [cx, cy] = q.front();
            q.pop();

            if (cx == end.first){
                if(cy == end.second){   
                    return true;
                }
            }

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

private:
    // Check if the move is valid
    bool isValidMove(int x, int y, const vector<vector<bool>> &visited) {
        bool res = x > 0 && x < HEIGHT && y > 0 && y < WIDTH && !visited[x][y] && maze[x][y] == PATH;
        return res;
    }
};

int main() {
    Maze maze;
    cout << "Generated Maze:\n";
    maze.printMaze();

    cout << "\nSolving maze with DFS...\n";
    if (maze.solveMazeDFS()){
        cout << "Maze solved using DFS!\n";
    }
    else{
        cout << "No solution found using DFS.\n";
    }

    cout << "\nSolving maze with BFS...\n";
    if (maze.solveMazeBFS()){
        cout << "Maze solved using BFS!\n";
    }
    else{
        cout << "No solution found using BFS.\n";
    }

    return 0;
}
