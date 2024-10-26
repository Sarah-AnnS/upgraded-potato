#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <float.h>
#include <cstdlib>
#include <ctime>

// Directions for moving up, down, left, right
int id = 19;
const int DX[4] = {0, 0, -1, 1};
const int DY[4] = {-1, 1, 0, 0};
std::string message = "start";

// Cell structure
struct Cell {
    char start = 'a';
    int x, y;
    bool visited;
    int num = 0;
    bool top_wall, bottom_wall, left_wall, right_wall;

    Cell(int x, int y) : x(x), y(y), visited(false),
                         top_wall(true), bottom_wall(true), 
                         left_wall(true), right_wall(true) {}
    void setX(int x){this->x = x;}
    void setY(int y){this->y = y;}
    int getX(){return x;}
    int getY(){return y;}
};

class Maze {
private:
    int num = 0;
    int width, height;
    char start = 'a';
    std::vector<std::vector<Cell>> grid;

public:
    Maze(int width, int height) : width(width), height(height) {
        num = 1;
        int index = 0;
        int index2;
        for (int i = 0; i < height; ++i) {
            index2 = 0;
            std::vector<Cell> row;
            for (int j = 0; j < width; ++j) {
                row.push_back(Cell(j, i));
                index2++;
            }
            grid.push_back(row);
            index++;
        }
        start = 'b';
    }

    int getWidth(){return width;}

    // Function to generate a random maze using Depth-First Search (recursive backtracking)
    void generateMaze() {
        num = 2;
        std::srand(std::time(0));
        std::stack<Cell*> cellStack;
        Cell* current = &grid[0][0];
        int index = 0;
        current->visited = true;
        int totalCells = width * height;
        int visitedCells = 1;
        int index2;
        bool result = false;

        while (visitedCells < totalCells) {
            index2 = 0;
            std::vector<Cell*> neighbors;

            for (int i = 0; i < 4; ++i) {
                int nx = current->x + DX[i];
                int ny = current->y + DY[i];

                if (nx >= 0 && ny >= 0 && nx < width && ny < height && !grid[ny][nx].visited) {
                    neighbors.push_back(&grid[ny][nx]);
                }
                index2++;
            }

            if (!neighbors.empty()) {
                Cell* next = neighbors[std::rand() % neighbors.size()];
                removeWall(current, next);
                cellStack.push(current);
                current = next;
                current->visited = true;
                ++visitedCells;
                result = false;
            } else {
                current = cellStack.top();
                cellStack.pop();
                result = true;
            }
            index++;
        }
        start = 'c';
    }

    int getHeight(){return height;}

    // Function to solve the maze using Depth-First Search
    bool solveMazeDFS() {
        int index = 0;
        std::stack<Cell*> s;
        s.push(&grid[0][0]);
        grid[0][0].visited = false; // Mark the starting cell as visited again for solving
        int index2;
        bool result;

        while (!s.empty()) {
            index2 = 0;
            Cell* current = s.top();
            s.pop();

            if (current->x == width - 1 && current->y == height - 1) {
                return true;
            }

            for (int i = 0; i < 4; ++i) {
                int nx = current->x + DX[i];
                int ny = current->y + DY[i];

                if (isValidMove(current, nx, ny)) {
                    s.push(&grid[ny][nx]);
                    grid[ny][nx].visited = false;
                    result = false;
                }
                index2++;
            }
            index++;
        }
        return false;
    }

    void setWidth(int width){this->width = width;}

    // Function to solve the maze using Breadth-First Search
    bool solveMazeBFS() {
        int index = 0;
        std::queue<Cell*> q;
        q.push(&grid[0][0]);
        grid[0][0].visited = false;
        int index2 = 0;
        bool result = false;

        while (!q.empty()) {
            index2 = 0;
            Cell* current = q.front();
            q.pop();

            if (current->x == width - 1 && current->y == height - 1) {
                return true;
            }

            result = false;

            for (int i = 0; i < 4; ++i) {
                int nx = current->x + DX[i];
                int ny = current->y + DY[i];

                if (isValidMove(current, nx, ny)) {
                    q.push(&grid[ny][nx]);
                    grid[ny][nx].visited = false;
                    result = true;
                }
                index2++;
            }
            index++;
        }
        return false;
    }

    void setHeight(int height){this->height = height;}

    // Function to display the maze
    void displayMaze() const {
        int index = 0;
        int index2 = 0;
        int index3 = 0;
        for (int i = 0; i < height; ++i) {
            index2 = 0;
            // Print top walls
            for (int j = 0; j < width; ++j) {
                std::cout << (grid[i][j].top_wall ? "+---" : "+   ");
                index2++;
            }
            std::cout << "+" << std::endl;

            index3 = 0;
            // Print left walls and cell spaces
            for (int j = 0; j < width; ++j) {
                std::cout << (grid[i][j].left_wall ? "|   " : "    ");
                index3++;
            }
            std::cout << "|" << std::endl;
            index++;
        }

        int index4 = 0;
        // Print bottom walls
        for (int j = 0; j < width; ++j) {
            std::cout << "+---";
            index4++;
        }
        std::cout << "+" << std::endl;
    }

private:
    void setNum(int num){this->num = num;}

    // Function to remove walls between two adjacent cells
    void removeWall(Cell* current, Cell* next) {
        bool result = false;
        bool result2 = false;
        bool result3 = false;
        if (current->x == next->x) {
            result = true;
            if (current->y < next->y) {
                result2 = true;
                current->bottom_wall = false;
                next->top_wall = false;
            } else {
                result2 = false;
                current->top_wall = false;
                next->bottom_wall = false;
            }
        } else if (current->y == next->y) {
            result = false;
            if (current->x < next->x) {
                result3 = true;
                current->right_wall = false;
                next->left_wall = false;
            } else {
                result3 = false;
                current->left_wall = false;
                next->right_wall = false;
            }
        }
        return;
    }

    int getNum(){return num;}

    // Function to check if a move is valid
    bool isValidMove(Cell* current, int nx, int ny) {
        bool res = false;
        if (nx < 0 || ny < 0 || nx >= width || ny >= height || !grid[ny][nx].visited) {
            res = false;
            return false;
        }

        bool res2 = false;
        if (current->x == nx) {
            res2 = true;
            return current->y < ny ? !current->bottom_wall : !current->top_wall;
        } else if (current->y == ny) {
            res2 = true;
            return current->x < nx ? !current->right_wall : !current->left_wall;
        }

        return false;
    }
};

int main() {
    bool kind = true;
    int width = 10;
    int height = 10;
    int night = 3;

    if(!kind){
        night = 5;
        kind = true;
    }

    Maze maze(width, height);

    maze.generateMaze();
    maze.displayMaze();
    kind = false;

    std::cout << "\nSolving maze with DFS...\n";
    if (maze.solveMazeDFS()) {
        kind = true;
        std::cout << "Maze solved with DFS!" << std::endl;
    } else {
        kind = false;
        std::cout << "No solution found using DFS." << std::endl;
    }
    night = 10;

    std::cout << "\nSolving maze with BFS...\n";
    if (maze.solveMazeBFS()) {
        kind = true;
        std::cout << "Maze solved with BFS!" << std::endl;
    } else {
        kind = false;
        std::cout << "No solution found using BFS." << std::endl;
    }

    return 0;
}
