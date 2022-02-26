#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <deque>
 
struct Vertex {
  enum class VertexColor : uint_fast64_t {
    WHITE,
    GRAY,
    BLACK
  };
 
  static constexpr int_fast64_t INFINITY = -1;
  static constexpr uint_fast64_t NIL = -1;
 
  Vertex() : distance(INFINITY), parent(NIL), color(VertexColor::WHITE) {}
 
  int_fast64_t distance;
  uint_fast64_t parent;
  VertexColor color;
  std::set<uint_fast64_t> edges;
};
 
std::ostream &operator<<(std::ostream &os, const Vertex &vertex) {
  for (const auto &i: vertex.edges) {
    os << " --> " << i;
  }
  return os;
}
 
class Graph {
 public:
  Graph() : startVertex(0), endVertex(0) {}
 
  void AddEdge(uint_fast64_t src, uint_fast64_t dst);
  inline void setStart(uint_fast64_t _start) { startVertex = _start; }
  inline void setEnd(uint_fast64_t _end) { endVertex = _end; }
 
  void BFS();
  int_fast64_t GetDistance() const { return adj.at(endVertex).distance; }
 
  friend std::ostream &operator<<(std::ostream &os, const Graph &graph);
 
 private:
  uint_fast64_t startVertex;
  uint_fast64_t endVertex;
  std::map<uint_fast64_t, Vertex> adj;
};
 
std::ostream &operator<<(std::ostream &os, const Graph &graph) {
  os << "Start: " << graph.startVertex << std::endl;
  os << "End: " << graph.endVertex << std::endl;
  for (const auto &i: graph.adj) {
    os << i.first << " : " << i.second << std::endl;
  }
  return os;
}
 
void Graph::AddEdge(uint_fast64_t src, uint_fast64_t dst) {
  if (adj.count(src) == 0) {
    adj.insert({src, Vertex()});
  }
 
  if (adj.count(dst) == 0) {
    adj.insert({dst, Vertex()});
  }
 
  adj[src].edges.insert(dst);
  adj[dst].edges.insert(src);
}
 
void Graph::BFS() {
  adj[startVertex].color = Vertex::VertexColor::GRAY;
  adj[startVertex].distance = 0;
  adj[startVertex].parent = Vertex::NIL;
  std::deque<uint_fast64_t> traversal;
  traversal.push_back(startVertex);
  while (!traversal.empty()) {
    uint_fast64_t currVertex = traversal.front();
    traversal.pop_front();
    for (const auto &childVertex: adj[currVertex].edges) {
      if (adj[childVertex].color == Vertex::VertexColor::WHITE) {
        adj[childVertex].color = Vertex::VertexColor::GRAY;
        adj[childVertex].distance = adj[currVertex].distance + 1;
        adj[childVertex].parent = currVertex;
        traversal.push_back(childVertex);
      }
    }
    adj[currVertex].color = Vertex::VertexColor::BLACK;
  }
}
 
class Maze {
 public:
  Maze();
 
  Graph BuildGraph();
 
  void Print();
 
  static constexpr char WALL = '+';
  static constexpr char WAY = '.';
  static constexpr char START = '@';
  static constexpr char END = '#';
 
 private:
  inline void checkLeft(size_t i, size_t j, Graph &g);
  inline void checkRight(size_t i, size_t j, Graph &g);
  inline void checkUp(size_t i, size_t j, Graph &g);
  inline void checkDown(size_t i, size_t j, Graph &g);
 
  size_t cols;
  size_t rows;
  std::vector<std::vector<char>> maze;
};
 
Maze::Maze() {
  size_t N, M;
  scanf("%zu %zu\n", &N, &M);
 
  for (size_t i = 0; i < N; ++i) {
    maze.emplace_back();
    for (size_t j = 0; j < M; ++j) {
      maze.back().push_back(getchar());
    }
    getchar();
  }
 
  rows = maze.size();
  cols = maze[0].size();
}
 
void Maze::Print() {
  for (const auto &row: maze) {
    for (const auto &elem: row) {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  }
}
 
void Maze::checkLeft(size_t i, size_t j, Graph &g) {
  if (j > 0) {
    if (maze[i][j - 1] != WALL) {
      g.AddEdge(i * cols + j, i * cols + j - 1);
    }
  }
}
 
void Maze::checkRight(size_t i, size_t j, Graph &g) {
  if (j < cols - 1) {
    if (maze[i][j + 1] != WALL) {
      g.AddEdge(i * cols + j, i * cols + j + 1);
    }
  }
}
 
void Maze::checkUp(size_t i, size_t j, Graph &g) {
  if (i > 0) {
    if (maze[i - 1][j] != WALL) {
      g.AddEdge(i * cols + j, (i - 1) * cols + j);
    }
  }
}
 
void Maze::checkDown(size_t i, size_t j, Graph &g) {
  if (i < rows - 1) {
    if (maze[i + 1][j] != WALL) {
      g.AddEdge(i * cols + j, (i + 1) * cols + j);
    }
  }
}
 
Graph Maze::BuildGraph() {
  Graph result;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      char currElem = maze[i][j];
      if (currElem != WALL) {
        checkLeft(i, j, result);
        checkRight(i, j, result);
        checkUp(i, j, result);
        checkDown(i, j, result);
      }
 
      if (currElem == START) {
        result.setStart(i * cols + j);
      }
 
      if (currElem == END) {
        result.setEnd(i * cols + j);
      }
    }
  }
  return result;
}
 
int main() {
  Maze maze;
  Graph graph = maze.BuildGraph();
  graph.BFS();
  printf("%ld", graph.GetDistance());
}