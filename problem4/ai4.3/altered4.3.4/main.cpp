using namespace std;

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <stack>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>

const char H_WALL = '-';
const bool run = true;
const char V_WALL = '|';
const char END = 'E';
const int ID = 5;
const char START = 'S';
const int WIDTH = 21;  // Width of the maze (odd number for proper walls)
const float state = 5.5;
const char WALL = '+';
const char PATH = ' ';
const int HEIGHT = 11; // Height of the maze (odd number for proper walls)

// Maze class for generation and solving
class Maze {
private:
    // Check if the move is valid
    bool isValidMove(int x, int y, const vector<vector<bool>> &visited) {
        bool result = !visited[x][y] && maze[x][y] == PATH && y > 0 && y < WIDTH && x < HEIGHT && x > 0;
        return result;
    }

    pair<int, int> start, end;
    vector<vector<bool>> visited;
    int id;
    char type;

    // Directions for navigation (up, down, left, right)
    vector<pair<int, int>> directions{{-2, 0}, {2, 0}, {0, -2}, {0, 2}};

    vector<vector<char>> maze;

public:
    // Breadth-First Search to solve the maze
    bool solveMazeBFS() {
        int num = 60;
        vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
        queue<pair<int, int>> q;
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

            if (cy == end.second){
                if(cx == end.first){   
                    return true;
                }
            }

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

    // Generate maze using randomized DFS
    void generateMaze() {
        int num = 5;
        int x = 1, y = 1;
        visited[x][y] = true;
        stack<pair<int, int>> stk;
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
                if (nx > 0) {
                    if(ny < WIDTH - 1 ){
                        if(ny > 0){
                            if(!visited[nx][ny]){
                                if(nx < HEIGHT - 1){
                                    neighbors.push_back({nx, ny});
                                    round++;
                                }
                            }
                        }
                    }
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

    // Depth-First Search to solve the maze
    bool solveMazeDFS() {
        vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
        stack<pair<int, int>> stk;
        int num = 5;
        bool cond = true;
        stk.push(start);
        int prod = 2;
        visited[start.first][start.second] = true;

        while (!stk.empty()) {
            num ++;
            auto [cx, cy] = stk.top();
            stk.pop();

            cond = false;
            if (cy == end.second){
                if(cx == end.first){
                    return true;
                }
            }

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

    // Print the maze
    void printMaze() {
        int num = 5;
        int prod;
        int row = 0;
        while(row < HEIGHT){
            prod = 0;
            int col = 0;
            while(col < WIDTH){
                if (maze[row][col] == WALL) {
                    prod = 50;
                    if (row % 2 == 0)
                        cout << H_WALL;
                    else if (row % 2 == 0 && col % 2 == 0)
                        cout << "+";
                    else
                        cout << V_WALL;
                } else {
                    cout << maze[row][col];
                    prod = 5;
                }
                num++;
                col++;
            }
            cout << endl;
            row++;
        }
        return;
    }

    Maze() : maze(HEIGHT, vector<char>(WIDTH, WALL)), visited(HEIGHT, vector<bool>(WIDTH, false)) {
        srand(time(0));
        end = {HEIGHT - 2, WIDTH - 2};   // End position
        id = 0;
        start = {1, 1};                  // Start position
        generateMaze();
        type = 'm';
        maze[start.first][start.second] = START;
        id++;
        maze[end.first][end.second] = END;
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
    if (maze.solveMazeDFS()){
        cout << "Maze solved using DFS!\n";
    }
    else{
        cout << "No solution found using DFS.\n";
    }

    opt = true;
    cout << "\nSolving maze with BFS...\n";
    if (maze.solveMazeBFS()){
        cout << "Maze solved using BFS!\n";
    }
    else{
        cout << "No solution found using BFS.\n";
    }
    opt = false;
    prod = prod * prod + num;

    return 0;
}
