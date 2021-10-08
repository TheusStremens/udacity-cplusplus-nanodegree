#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/// The state of a cell.
enum class State
{
  kEmpty,
  kObstacle,
  kClosed,
  kPath,
  kStart,
  kFinish
};

/// Avoid not straightforward std::vector<int> to represent a node.
struct Node
{
  int x;
  int y;
  int g; // Movement cost.
  int h; // Heuristic cost.

  Node(int _x, int _y, int _g, int _h)
    :x(_x), y(_y), g(_g), h(_h)
  {}

  int cost() { return g + h; }

  bool hasHigherCostThan(Node other_node) { return (cost() > other_node.cost()); }
};

/// To calculate the neighbors of some (x,y) point.
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

using GridState = std::vector<std::vector<State>>;

//// Check if the [x][y] cell is inside the grid and is empty.
bool checkValidCell(const int &x, const int &y, const GridState &grid)
{
  if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size()) return false;
  return (grid[x][y] == State::kEmpty);
}

/// Compare method to be used in C++ sort.
bool compare(Node a, Node b)
{
  return (a.hasHigherCostThan(b));
}

/// Sort the nodes by their cost. The last node has the lower cost.
void cellSort(std::vector<Node> &unsorted_nodes)
{
  std::sort(unsorted_nodes.begin(), unsorted_nodes.end(), compare);
}

/// Manhattan distance between two 2D points.
int heuristic(const int a[2], const int b[2])
{
  // x2 - x1 + y2 - y1
  return (std::abs(b[0] - a[0]) + std::abs(b[1] - a[1]));
}

/// Just add a new node to the list of open nodes.
void addToOpen(Node new_node,
               std::vector<Node> &open_nodes,
               GridState &grid)
{
  open_nodes.push_back(new_node);
  grid[new_node.x][new_node.y] = State::kClosed;
}

/// Check the neighbors of a node, check if they are empty. Add all empty neighbors in
/// the open nodes list.
void expandNeighbors(Node current_node,
                     std::vector<Node> &open_nodes,
                     GridState grid,
                     const int goal[2])
{
  int coord[2] = {current_node.x, current_node.y};
  for (auto increment : delta)
  {
    int neighbor_coord[2] = {coord[0] + increment[0], coord[1] + increment[1]};
    if (checkValidCell(neighbor_coord[0], neighbor_coord[1], grid))
    {
      int g = current_node.g + 1;
      int h = heuristic(neighbor_coord, goal);
      Node neighbor_node(neighbor_coord[0], neighbor_coord[1], g, h);
      addToOpen(neighbor_node, open_nodes, grid);
    }
  }
}

/// Perform the A* search in the grid.
GridState search(GridState &grid,
                  const int init[2],
                  const int goal[2])
{
  std::vector<Node> open_nodes;

  Node init_node(init[0], init[1], 0, heuristic(init, goal));
  addToOpen(init_node, open_nodes, grid);

  while (open_nodes.size() != 0)
  {
    cellSort(open_nodes);
    Node current_node = open_nodes.back();
    open_nodes.pop_back();
    grid[current_node.x][current_node.y] = State::kPath;

    if (current_node.x == goal[0] && current_node.y == goal[1])
    {
      grid[init[0]][init[1]] = State::kStart;
      grid[goal[0]][goal[1]] = State::kFinish;
      return grid;
    }
    expandNeighbors(current_node, open_nodes, grid, goal);
  }

  std::cout << "No path found!" << std::endl;
  return grid;
}

/// parse the text line into a "grid line".
std::vector<State> parseLine(const std::string &line)
{
  std::istringstream sline(line);
  int n;
  char c;
  std::vector<State> row;
  while (sline >> n >> c && c == ',')
  {
    if (n == 0)
      row.push_back(State::kEmpty);
    else
      row.push_back(State::kObstacle);
  }
  return row;
}

/// Given a file path, open the file and parse all lines in a grid.
GridState readBoardFile(const std::string &path)
{
  std::ifstream board_file(path);
  GridState board{};
  if (board_file)
  {
    std::string line;
    while (std::getline(board_file, line))
    {
      std::vector<State> row = parseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

/// Print a beautiful emoticon depending of the cell.
std::string cellString(const State &cell)
{
  switch (cell)
  {
    case State::kObstacle: return "⛰️    ";
    case State::kPath: return "🚗   ";
    case State::kStart: return "🚦   ";
    case State::kFinish: return "🏁   ";
    default: return "0    ";
  }
}

/// Print the board using emoticons.
void printBoard(const GridState &board)
{
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
      std::cout << cellString(board[i][j]);

    std::cout << "\n";
  }
}

int main()
{
  int start[2] = {0, 0};
  int goal[2] = {4, 5};
  auto board = readBoardFile("1.board");
  auto solution = search(board, start, goal);
  printBoard(solution);
  return 0;
}
