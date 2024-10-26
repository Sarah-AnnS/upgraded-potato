
struct Cell {
    int x, y;
    Cell(int x, int y) : x(x), y(y) {}
};

using namespace std;
#include <algorithm>
#include <queue>
#include <ctime>
#include <vector>
#include <iostream>
#include <stack>
#include <cstdlib>

class Maze {

public:
    void printMaze() {
        for (const auto &row : maze) {
            for (char cell : row) cout << cell;
            cout << '\n';
        }
    }

    bool solveMazeBFS() {
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        queue<Cell> queue;
        queue.push(Cell(1, 1));
        visited[1][1] = true;

        while (!queue.empty()) {
            Cell cell = queue.front();
            queue.pop();
            int x = cell.x, y = cell.y;

            if (x == height - 2 && y == width - 2) return true;

            maze[x][y] = '.';
            int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (auto &dir : directions) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                if (isInsideMaze(nx, ny) && !visited[nx][ny] && maze[nx][ny] == ' ') {
                    queue.push(Cell(nx, ny));
                    visited[nx][ny] = true;
                }
            }
        }
        return false;
    }
    
    bool solveMazeDFS() {
        stack<Cell> stack;
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        stack.push(Cell(1, 1));
        visited[1][1] = true;

        while (!stack.empty()) {
            Cell cell = stack.top();
            stack.pop();
            int x = cell.x, y = cell.y;

            if (x == height - 2 && y == width - 2) return true;

            maze[x][y] = '.';
            int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (auto &dir : directions) {
                int ny = y + dir[1];
                int nx = x + dir[0];
                if (isInsideMaze(nx, ny) && maze[nx][ny] == ' ' && !visited[nx][ny]) {
                    stack.push(Cell(nx, ny));
                    visited[nx][ny] = true;
                }
            }
        }
        return false;
    }

    Maze(int width, int height) : width(width), height(height) {
        initializeMaze();
        carvePath(1, 1); // Start carving from top-left corner
    }

private:
    void carvePath(int x, int y) {
        int directions[4][2] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
        random_shuffle(begin(directions), end(directions));
        maze[x][y] = ' ';

        for (auto &dir : directions) {
            int ny = y + dir[1];
            int nx = x + dir[0];
            if (isInsideMaze(nx, ny) && maze[nx][ny] == '+') {
                maze[x + dir[0] / 2][y + dir[1] / 2] = ' ';
                carvePath(nx, ny);
            }
        }
    }
    
    void initializeMaze() {
        // Fill the maze with walls ('+', '-', '|')
        maze.resize(height, vector<char>(width, '+'));
        for (int i = 1; i < height; i += 2) {
            for (int j = 1; j < width; j += 2) {
                maze[i][j] = ' ';
                if (i < height - 1) maze[i + 1][j] = '-';
                if (j < width - 1) maze[i][j + 1] = '|';
            }
        }
    }

    bool isInsideMaze(int x, int y) {
        return x > 0 && x < height - 1 && y > 0 && y < width - 1;
    }

    vector<vector<char>> maze;
    int height, width;


};

int main() {
    srand(time(0));

    int width = 21, height = 21;
    Maze maze(width, height);

    cout << "Generated Maze:\n";
    maze.printMaze();

    cout << "\nSolving Maze with DFS...\n";
    if (maze.solveMazeDFS()) {
        cout << "Maze solved with DFS:\n";
        maze.printMaze();
    } else {
        cout << "No solution found using DFS.\n";
    }

    cout << "\nSolving Maze with BFS...\n";
    if (maze.solveMazeBFS()) {
        cout << "Maze solved with BFS:\n";
        maze.printMaze();
    } else {
        cout << "No solution found using BFS.\n";
    }

    return 0;
}
