#include <ctime>
#include <stack>
#include <vector>
#include <queue>
#include <cstdlib>
#include <iostream>

// Cell structure
struct Cell {
    Cell(int x, int y) : x(x), y(y), visited(false),
                         top_wall(true), bottom_wall(true), 
                         left_wall(true), right_wall(true) {}

    bool top_wall, bottom_wall, left_wall, right_wall;
    bool visited;
    int x, y;
};

// Directions for moving up, down, left, right
const int DY[4] = {-1, 1, 0, 0};
const int DX[4] = {0, 0, -1, 1};

class Maze {
public:
    // Function to solve the maze using Breadth-First Search
    bool solveMazeBFS() {
        grid[0][0].visited = false;
        std::queue<Cell*> q;
        q.push(&grid[0][0]);

        while (!q.empty()) {
            Cell* current = q.front();
            q.pop();

            if (current->x == width - 1 && current->y == height - 1) {
                return true;
            }

            for (int i = 0; i < 4; ++i) {
                int ny = current->y + DY[i];
                int nx = current->x + DX[i];

                if (isValidMove(current, nx, ny)) {
                    q.push(&grid[ny][nx]);
                    grid[ny][nx].visited = false;
                }
            }
        }
        return false;
    }

    // Function to display the maze
    void displayMaze() const {
        for (int i = 0; i < height; ++i) {
            // Print top walls
            for (int j = 0; j < width; ++j) {
                std::cout << (grid[i][j].top_wall ? "+---" : "+   ");
            }
            std::cout << "+" << std::endl;

            // Print left walls and cell spaces
            for (int j = 0; j < width; ++j) {
                std::cout << (grid[i][j].left_wall ? "|   " : "    ");
            }
            std::cout << "|" << std::endl;
        }

        // Print bottom walls
        for (int j = 0; j < width; ++j) {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl;
    }
    
    // Function to solve the maze using Depth-First Search
    bool solveMazeDFS() {
        grid[0][0].visited = false; // Mark the starting cell as visited again for solving
        std::stack<Cell*> s;
        s.push(&grid[0][0]);

        while (!s.empty()) {
            Cell* current = s.top();
            s.pop();

            if (current->x == width - 1 && current->y == height - 1) {
                return true;
            }

            for (int i = 0; i < 4; ++i) {
                int ny = current->y + DY[i];
                int nx = current->x + DX[i];

                if (isValidMove(current, nx, ny)) {
                    s.push(&grid[ny][nx]);
                    grid[ny][nx].visited = false;
                }
            }
        }
        return false;
    }

    // Function to generate a random maze using Depth-First Search (recursive backtracking)
    void generateMaze() {
        int visitedCells = 1;
        std::srand(std::time(0));
        Cell* current = &grid[0][0];
        int totalCells = width * height;
        std::stack<Cell*> cellStack;
        current->visited = true;

        while (visitedCells < totalCells) {
            std::vector<Cell*> neighbors;

            for (int i = 0; i < 4; ++i) {
                int ny = current->y + DY[i];
                int nx = current->x + DX[i];

                if (ny >= 0 && ny < height && nx >= 0 && !grid[ny][nx].visited && nx < width) {
                    neighbors.push_back(&grid[ny][nx]);
                }
            }

            if (!neighbors.empty()) {
                ++visitedCells;
                Cell* next = neighbors[std::rand() % neighbors.size()];
                removeWall(current, next);
                cellStack.push(current);
                current = next;
                current->visited = true;
            } else {
                current = cellStack.top();
                cellStack.pop();
            }
        }
    }

    Maze(int width, int height) : width(width), height(height) {
        for (int i = 0; i < height; ++i) {
            std::vector<Cell> row;
            for (int j = 0; j < width; ++j) {
                row.push_back(Cell(j, i));
            }
            grid.push_back(row);
        }
    }

private:
    // Function to remove walls between two adjacent cells
    void removeWall(Cell* current, Cell* next) {
        if (current->x == next->x) {
            if (current->y < next->y) {
                current->bottom_wall = false;
                next->top_wall = false;
            } else {
                current->top_wall = false;
                next->bottom_wall = false;
            }
        } else if (current->y == next->y) {
            if (current->x < next->x) {
                current->right_wall = false;
                next->left_wall = false;
            } else {
                current->left_wall = false;
                next->right_wall = false;
            }
        }
    }

    // Function to check if a move is valid
    bool isValidMove(Cell* current, int nx, int ny) {
        if (nx < 0 || ny < 0 || nx >= width || ny >= height || !grid[ny][nx].visited) {
            return false;
        }

        if (current->x == nx) {
            return current->y < ny ? !current->bottom_wall : !current->top_wall;
        } else if (current->y == ny) {
            return current->x < nx ? !current->right_wall : !current->left_wall;
        }

        return false;
    }

private:
    std::vector<std::vector<Cell>> grid;
    int width, height;

};

int main() {
    int width = 10;
    int height = 10;

    Maze maze(width, height);

    maze.generateMaze();
    maze.displayMaze();

    std::cout << "\nSolving maze with DFS...\n";
    if (maze.solveMazeDFS()) {
        std::cout << "Maze solved with DFS!" << std::endl;
    } else {
        std::cout << "No solution found using DFS." << std::endl;
    }

    std::cout << "\nSolving maze with BFS...\n";
    if (maze.solveMazeBFS()) {
        std::cout << "Maze solved with BFS!" << std::endl;
    } else {
        std::cout << "No solution found using BFS." << std::endl;
    }

    return 0;
}
