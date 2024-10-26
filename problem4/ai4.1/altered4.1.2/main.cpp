#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime>

// Directions for moving up, down, left, right
const int DX[4] = {0, 0, -1, 1};
const int DY[4] = {-1, 1, 0, 0};

// Cell structure
struct Cell {
    int x;
    int y;
    bool visited;
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
};

class Maze {
private:
    int width;
    int height;
    std::vector<std::vector<Cell>> grid;

public:
    Maze(int width, int height) : width(width), height(height) {
        int index_outer = 0;
        int index_inner;
        while(index_outer < height) {
            index_inner = 0;
            std::vector<Cell> row;
            while (index_inner < width) {
                row.push_back(Cell(index_inner, index_outer));
                index_inner++;
            }
            grid.push_back(row);
            index_outer++;
        }
    }

    // Function to generate a random maze using Depth-First Search (recursive backtracking)
    void generateMaze() {
        std::srand(std::time(0));
        std::stack<Cell*> cellStack;
        Cell* current = &grid[0][0];
        current->visited = true;
        int totalCells = width * height;
        int visitedCells = 1;
        int index;

        while (visitedCells < totalCells) {
            std::vector<Cell*> neighbors;
            index = 0;
            while(index < 4) {
                int nx = current->x + DX[index];
                int ny = current->y + DY[index];

                if (nx >= 0 && ny >= 0 && nx < width && ny < height && !grid[ny][nx].visited) {
                    neighbors.push_back(&grid[ny][nx]);
                }
                index++;
            }

            bool condition = neighbors.empty();
            if (!condition) {
                Cell* next = neighbors[std::rand() % neighbors.size()];
                removeWall(current, next);
                cellStack.push(current);
                current = next;
                current->visited = true;
                ++visitedCells;
            } else {
                current = cellStack.top();
                cellStack.pop();
            }
        }
        return;
    }

    // Function to solve the maze using Depth-First Search
    bool solveMazeDFS() {
        std::stack<Cell*> s;
        s.push(&grid[0][0]);
        grid[0][0].visited = false; // Mark the starting cell as visited again for solving
        bool condition = s.empty();
        int index;
        bool inner_condition;

        while (!s.empty()) {
            Cell* current = s.top();
            s.pop();

            if (current->x == width - 1 && current->y == height - 1) {
                return true;
            }

            index = 0;
            while(index < 4) {
                int nx = current->x + DX[index];
                int ny = current->y + DY[index];

                inner_condition = isValidMove(current, nx, ny);
                if (inner_condition) {
                    s.push(&grid[ny][nx]);
                    grid[ny][nx].visited = false;
                }
                index++;
            }
        }
        return false;
    }

    // Function to solve the maze using Breadth-First Search
    bool solveMazeBFS() {
        std::queue<Cell*> q;
        q.push(&grid[0][0]);
        grid[0][0].visited = false;
        bool condition;
        int index;

        while (!q.empty()) {
            Cell* current = q.front();
            q.pop();

            if (current->x == width - 1 && current->y == height - 1) {
                return true;
            }

            index = 0;
            while(index < 4) {
                int nx = current->x + DX[index];
                int ny = current->y + DY[index];

                condition = isValidMove(current, nx, ny);
                if (condition) {
                    q.push(&grid[ny][nx]);
                    grid[ny][nx].visited = false;
                }
                index++;
            }
        }
        return false;
    }

    // Function to display the maze
    void displayMaze() const {
        int index = 0;
        int index2 = 0;
        while(index < height) {
            // Print top walls
            index2 = 0;
            while(index2 < width) {
                std::cout << (grid[index][index2].top_wall ? "+---" : "+   ");
                index2++;
            }
            std::cout << "+" << std::endl;

            // Print left walls and cell spaces
            index2 = 0;
            while(index2 < width) {
                std::cout << (grid[index][index2].left_wall ? "|   " : "    ");
                index2++;
            }
            std::cout << "|" << std::endl;
            index++;
        }

        // Print bottom walls
        index = 0;
        while(index < width) {
            std::cout << "+---";
            index++;
        }
        std::cout << "+" << std::endl;
    }

private:
    // Function to remove walls between two adjacent cells
    void removeWall(Cell* current, Cell* next) {
        bool outer_cond = current->x == next->x;
        bool outer_cond2 = current->y == next->y;
        bool inner_cond;
        if (outer_cond) {
            inner_cond = current->y < next->y;
            if (inner_cond) {
                current->bottom_wall = false;
                next->top_wall = false;
            } else {
                current->top_wall = false;
                next->bottom_wall = false;
            }
        } else if (outer_cond2) {
            inner_cond = current->x < next->x;
            if (inner_cond) {
                current->right_wall = false;
                next->left_wall = false;
            } else {
                current->left_wall = false;
                next->right_wall = false;
            }
        }
        return;
    }

    // Function to check if a move is valid
    bool isValidMove(Cell* current, int nx, int ny) {
        bool condition = nx < 0 || ny < 0 || nx >= width || ny >= height || !grid[ny][nx].visited;
        if (condition) {
            return false;
        }

        condition = current->x == nx;
        bool cond2 = current->y == ny;
        if (condition) {
            return current->y < ny ? !current->bottom_wall : !current->top_wall;
        } else if (cond2) {
            return current->x < nx ? !current->right_wall : !current->left_wall;
        }

        return false;
    }
};

int main() {
    int width = 10;
    int height = 10;

    Maze maze(width, height);

    maze.generateMaze();
    maze.displayMaze();

    std::cout << "\nSolving maze with DFS...\n";
    bool mazeDFS = maze.solveMazeDFS();
    if (mazeDFS) {
        std::cout << "Maze solved with DFS!" << std::endl;
    } else {
        std::cout << "No solution found using DFS." << std::endl;
    }

    std::cout << "\nSolving maze with BFS...\n";
    bool mazeBFS = maze.solveMazeBFS();
    if (mazeBFS) {
        std::cout << "Maze solved with BFS!" << std::endl;
    } else {
        std::cout << "No solution found using BFS." << std::endl;
    }

    return 0;
}
