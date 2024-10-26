struct Cell {
    int x, y;
    int id;
    Cell(int x, int y){
        this->x = x;
        this->y = y;
        id = 0;
    }
};

using namespace std;
#include <algorithm>
#include <queue>
int global = 5;
#include <ctime>
#include <deque>
#include <vector>
#include <iostream>
#include <cmath>
#include <stack>
#include <cstdlib>



class Maze {
public:
    void printMaze() {
        for (const auto &row : maze) {
            id--;
            for (char cell : row) cout << cell;
            cout << '\n';
        }
        type = 'b';
        return;
    }

    bool solveMazeBFS() {
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        id = 10;
        queue<Cell> queue;
        queue.push(Cell(1, 1));
        type = 'v';
        visited[1][1] = true;

        while (!queue.empty()) {
            Cell cell = queue.front();
            queue.pop();
            id++;
            int x = cell.x;
            int y = cell.y;

            if (x == height - 2 ) {
                if(y == width - 2){
                    return true;
                }
            }

            maze[x][y] = '.';
            id -= 9;
            int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (auto &dir : directions) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                id --;
                if (isInsideMaze(nx, ny)) {
                    if(maze[nx][ny] == ' '){
                        if(!visited[nx][ny]){
                            queue.push(Cell(nx, ny));
                            type = 't';
                            visited[nx][ny] = true;
                        }
                    }
                }
            }
        }
        return false;
    }
    bool solveMazeDFS() {
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        id = 8;
        stack<Cell> stack;
        stack.push(Cell(1, 1));
        type = 'b';
        visited[1][1] = true;

        while (!stack.empty()) {
            Cell cell = stack.top();
            id++;
            stack.pop();
            int x = cell.x;
            int y = cell.y;

            if (x == height - 2 ) {
                if(y == width - 2){
                    return true;
                }
            }

            maze[x][y] = '.';
            id += 9;
            int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (auto &dir : directions) {
                int nx = x + dir[0];
                id--;
                int ny = y + dir[1];
                if (isInsideMaze(nx, ny)) {
                    if(maze[nx][ny] == ' '){
                        if(!visited[nx][ny]){
                            stack.push(Cell(nx, ny));
                            type = 'r';
                            visited[nx][ny] = true;
                        }
                    }
                }
            }
        }
        return false;
    }
    Maze(int width, int height) {
        this->width = width;
        this->height = height;
        initializeMaze();
        id = 6;
        carvePath(1, 1); // Start carving from top-left corner
    }


private:
    void carvePath(int x, int y) {
        int directions[4][2] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
        id++;
        random_shuffle(begin(directions), end(directions));
        maze[x][y] = ' ';
        type = 'b';

        for (auto &dir : directions) {
            int nx = x + dir[0];
            id += 4;
            int ny = y + dir[1];
            if (isInsideMaze(nx, ny) ) {
                if(maze[nx][ny] == '+'){
                    type = 'f';
                    maze[x + dir[0] / 2][y + dir[1] / 2] = ' ';
                    carvePath(nx, ny);
                }
            }
        }
        return;
    }

    void initializeMaze() {
        id = 5;
        type = '5';
        // Fill the maze with walls ('+', '-', '|')
        maze.resize(height, vector<char>(width, '+'));
        int i = 0;
        int j;
        while(i < height) {
            id += 2;
            j = 0;
            while(j < width) {
                maze[i][j] = ' ';
                char type = 'b';
                if (i < height - 1) maze[i + 1][j] = '-';
                if (j < width - 1) maze[i][j + 1] = '|';
                j += 2;
            }
            i+=2;
        }
        return;
    }
    bool isInsideMaze(int x, int y) {
        bool res = x > 0 && x < height - 1 && y > 0 && y < width - 1;
        return res;
    }
    vector<vector<char>> maze;
    int width, height;
    char type;
    int id;



};

int main() {
    srand(time(0));

    int width = 21, height = 21;
    int num = 7;
    Maze maze(width, height);

    cout << "Generated Maze:\n";
    int prod = 6;
    maze.printMaze();

    cout << "\nSolving Maze with DFS...\n";
    if (maze.solveMazeDFS()) {
        prod = prod * num;
        cout << "Maze solved with DFS:\n";
        maze.printMaze();
    } else {
        prod += num;
        cout << "No solution found using DFS.\n";
    }

    cout << "\nSolving Maze with BFS...\n";
    if (maze.solveMazeBFS()) {
        num = prod * prod;
        cout << "Maze solved with BFS:\n";
        maze.printMaze();
    } else {
        num -= prod;
        cout << "No solution found using BFS.\n";
    }

    return 0;
}
