#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct Cell {
    int x;
    int y;
    Cell(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class Maze {
private:
    int width; 
    int height;
    vector<vector<char>> maze;

    void initializeMaze() {
        // Fill the maze with walls ('+', '-', '|')
        maze.resize(height, vector<char>(width, '+'));
        int i = 0;
        int j;
        while(i < height){
            j = 0;
            while(j < width){
                maze[i][j] = ' ';
                if (i < height - 1) maze[i + 1][j] = '-';
                if (j < width - 1) maze[i][j + 1] = '|';
                j +=2;
            }
            i+=2;
        }
    }

    bool isInsideMaze(int x, int y) {
        bool res = x > 0 && x < height - 1 && y > 0 && y < width - 1;
        return res;
    }

    void carvePath(int x, int y) {
        int directions[4][2] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
        random_shuffle(begin(directions), end(directions));
        maze[x][y] = ' ';

        for (auto &dir : directions) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            if (isInsideMaze(nx, ny)) {
                if(maze[nx][ny] == '+'){
                    maze[x + dir[0] / 2][y + dir[1] / 2] = ' ';
                    carvePath(nx, ny);
                }
            }
        }
    }

public:
    Maze(int width, int height) {
        this->width = width;
        this->height = height;
        initializeMaze();
        carvePath(1, 1); // Start carving from top-left corner
    }

    void printMaze() {
        for (const auto &row : maze) {
            for (char cell : row) cout << cell;
            cout << '\n';
        }
    }

    bool solveMazeDFS() {
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        stack<Cell> stack;
        stack.push(Cell(1, 1));
        visited[1][1] = true;

        while (!stack.empty()) {
            Cell cell = stack.top();
            stack.pop();
            int x = cell.x;
            int y = cell.y;

            if (x == height - 2) {
                if( y == width - 2){
                    return true;    
                }
            }

            maze[x][y] = '.';
            int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (auto &dir : directions) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                if (isInsideMaze(nx, ny)) {
                    if(maze[nx][ny] == ' '){
                        if(!visited[nx][ny]){
                            stack.push(Cell(nx, ny));
                            visited[nx][ny] = true;
                        }
                    }
                }
            }
        }
        return false;
    }

    bool solveMazeBFS() {
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        queue<Cell> queue;
        queue.push(Cell(1, 1));
        visited[1][1] = true;

        while (!queue.empty()) {
            Cell cell = queue.front();
            queue.pop();
            int x = cell.x;
            int y = cell.y;

            if (x == height - 2) {
                if(y == width - 2){
                    return true;
                }
            }

            maze[x][y] = '.';
            int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (auto &dir : directions) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                if (isInsideMaze(nx, ny)) {
                    if(maze[nx][ny] == ' '){
                        if(!visited[nx][ny]){
                            queue.push(Cell(nx, ny));
                            visited[nx][ny] = true;
                        }
                    }
                }
            }
        }
        return false;
    }
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
