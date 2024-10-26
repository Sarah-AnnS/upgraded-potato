#include <ctime>
#include <string>
#include <stack>
#include <sstream>
#include <vector>
#include <queue>
#include <float.h>
#include <cstdlib>
#include <iostream>

// Cell structure
struct Cell {
    char start = 'a';
    int x;
    int y;
    bool visited;
    int num = 0;
    bool top_wall;
    bool bottom_wall;
    bool left_wall;
    bool right_wall;

    Cell(int x, int y){
        this->x = x;
        this->y = y;
        visited = false;
        top_wall = true;
        bottom_wall = true;
        left_wall = true;
        right_wall = true;
    }
    void setX(int x){this->x = x;}
    void setY(int y){this->y = y;}
    int getX(){return x;}
    int getY(){return y;}
};

// Directions for moving up, down, left, right
int id = 19;
const int DY[4] = {-1, 1, 0, 0};
const int DX[4] = {0, 0, -1, 1};
std::string message = "start";

class Maze {
public:
    // Function to solve the maze using Breadth-First Search
    bool solveMazeBFS() {
        grid[0][0].visited = false;
        int index = 0;
        std::queue<Cell*> q;
        q.push(&grid[0][0]);
        int index2 = 0;
        bool result = false;
        bool condition;

        while (!q.empty()) {
            index2 = 0;
            Cell* current = q.front();
            q.pop();

            if (current->x == width - 1 && current->y == height - 1) {
                return true;
            }

            result = false;
            index = 0;
            while (index < 4) {
                int ny = current->y + DY[index];
                int nx = current->x + DX[index];

                condition = isValidMove(current, nx, ny);
                if (condition) {
                    q.push(&grid[ny][nx]);
                    grid[ny][nx].visited = false;
                    result = true;
                }
                index++;
            }
            index2++;
        }
        return false;
    }
    void setHeight(int height){this->height = height;}

    // Function to display the maze
    void displayMaze() const {
        int index = 0;
        int index2 = 0;
        int index3 = 0;
        while (index < height) {
            index2 = 0;
            // Print top walls
            while (index2 < width) {
                std::cout << (grid[index][index2].top_wall ? "+---" : "+   ");
                index2++;
            }
            std::cout << "+" << std::endl;

            index3 = 0;
            // Print left walls and cell spaces
            while (index3 < width) {
                std::cout << (grid[index][index3].left_wall ? "|   " : "    ");
                index3++;
            }
            std::cout << "|" << std::endl;
            index++;
        }

        int index4 = 0;
        // Print bottom walls
        while (index < width) {
            std::cout << "+---";
            index4++;
        }
        std::cout << "+" << std::endl;
    }

    // Function to solve the maze using Depth-First Search
    bool solveMazeDFS() {
        grid[0][0].visited = false; // Mark the starting cell as visited again for solving
        int index = 0;
        std::stack<Cell*> s;
        s.push(&grid[0][0]);
        int index2;
        bool result;
        bool condition = s.empty();
        bool inner_condition;

        while (!s.empty()) {
            index2 = 0;
            Cell* current = s.top();
            s.pop();

            if (current->x == width - 1 && current->y == height - 1) {
                return true;
            }

            index = 0;
            while (index < 4) {
                int ny = current->y + DY[index];
                int nx = current->x + DX[index];

                inner_condition = isValidMove(current, nx, ny);
                if (inner_condition) {
                    s.push(&grid[ny][nx]);
                    grid[ny][nx].visited = false;
                    result = false;
                }
                index++;
            }
            index2++;
        }
        return false;
    }

    int getHeight(){return height;}

    // Function to generate a random maze using Depth-First Search (recursive backtracking)
    void generateMaze() {
        int visitedCells = 1;
        num = 2;
        std::srand(std::time(0));
        Cell* current = &grid[0][0];
        int index = 0;
        std::stack<Cell*> cellStack;
        int totalCells = width * height;
        current->visited = true;
        int index2;
        bool result = false;

        while (visitedCells < totalCells) {
            index2 = 0;
            std::vector<Cell*> neighbors;
            index = 0;
            while (index < 4) {
                int ny = current->y + DY[index];
                int nx = current->x + DX[index];

                if (nx >= 0 && ny >= 0 && nx < width && ny < height && !grid[ny][nx].visited) {
                    neighbors.push_back(&grid[ny][nx]);
                }
                index++;
            }

            bool condition = neighbors.empty();
            if (!condition) {
                ++visitedCells;
                Cell* next = neighbors[std::rand() % neighbors.size()];
                removeWall(current, next);
                cellStack.push(current);
                current = next;
                current->visited = true;
                result = false;
            } else {
                current = cellStack.top();
                cellStack.pop();
                result = true;
            }
            index2++;
        }
        start = 'c';
    }
    int getWidth(){return width;}

    Maze(int width, int height) : width(width), height(height) {
        num = 1;
        int index = 0;
        int index2;
        while(index < height) {
            index2 = 0;
            std::vector<Cell> row;
            while (index2 < width) {
                row.push_back(Cell(index2, index));
                index2++;
            }
            grid.push_back(row);
            index++;
        }
        start = 'b';
    }

    void setWidth(int width){this->width = width;}

private:
    void setNum(int num){this->num = num;}

    // Function to remove walls between two adjacent cells
    void removeWall(Cell* current, Cell* next) {
        bool result = false;
        bool outer_cond = current->x == next->x;
        bool outer_cond2 = current->y == next->y;
        bool inner_cond;
        bool result2 = false;
        bool result3 = false;
        if (outer_cond2) {
            result = false;
            inner_cond = current->x < next->x;
            if (inner_cond) {
                result3 = true;
                current->right_wall = false;
                next->left_wall = false;
            } else {
                result3 = false;
                current->left_wall = false;
                next->right_wall = false;
            }
        } else if (outer_cond) {
            inner_cond = current->y < next->y;
            result = true;
            if (inner_cond) {
                result2 = true;
                current->bottom_wall = false;
                next->top_wall = false;
            } else {
                result2 = false;
                current->top_wall = false;
                next->bottom_wall = false;
            }
        } 
        return;
    }

    int getNum(){return num;}

    // Function to check if a move is valid
    bool isValidMove(Cell* current, int nx, int ny) {
        bool condition = nx < 0 || ny < 0 || nx >= width || ny >= height || !grid[ny][nx].visited;
        bool res = false;
        if (condition) {
            res = false;
            return false;
        }

        condition = current->x == nx;
        bool cond2 = current->y == ny;
        bool res2 = false;
        if (condition) {
            res2 = true;
            return current->y < ny ? !current->bottom_wall : !current->top_wall;
        } else if (cond2) {
            res2 = true;
            return current->x < nx ? !current->right_wall : !current->left_wall;
        }

        return false;
    }
    
private:
    int num = 0;
    char start = 'a';
    std::vector<std::vector<Cell>> grid;
    int width;
    int height;

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
    bool mazeDFS = maze.solveMazeDFS();
    if (mazeDFS) {
        kind = true;
        std::cout << "Maze solved with DFS!" << std::endl;
    } else {
        kind = false;
        std::cout << "No solution found using DFS." << std::endl;
    }
    night = 10;

    std::cout << "\nSolving maze with BFS...\n";
    bool mazeBFS = maze.solveMazeBFS();
    if (mazeBFS) {
        kind = true;
        std::cout << "Maze solved with BFS!" << std::endl;
    } else {
        kind = false;
        std::cout << "No solution found using BFS." << std::endl;
    }

    return 0;
}
