#include "Graph.hh"

// 二分图
struct Bipartite {
  bool bipartite{true};
  ns::deque<bool> color;
  ns::deque<bool> marked;
  ns::deque<int> edgeTo;
  ns::deque<int> cycle;
  Bipartite(const Graph &G)
      : color(G.V, false), marked(G.V, false), edgeTo(G.V, -1) {
    for (int v = 0; v < G.V; v++)
      if (!marked[v]) {
        dfs(G, v);
        if (!cycle.empty())
          return;
      }
  }
  void dfs(const Graph &G, int v) {
    marked[v] = true;
    for (int w : G.adj[v]) {
      if (!marked[w]) {
        edgeTo[w] = v;
        color[w] = !color[v];
        dfs(G, w);
        if (!cycle.empty())
          return;
      } else if (color[w] == color[v]) {
        bipartite = false;
        cycle.push_back(w);
        for (int x = v; x != w; x = edgeTo[x]) {
          cycle.push_back(x);
        }
        cycle.push_back(w);
        return;
      }
    }
  }
  bool isBipartite() { return !cycle.empty(); }
};

int main() {
  constexpr int v{8}, e{8};
  Graph G(v);
  generateGraph(G, e);
  printGraph(G);
  Bipartite bp(G);
  if (bp.bipartite)
    std::print("IsBipartite");
  else {
    std::print("cycle\t");
    for (int v : bp.cycle)
      std::print("{}\t", v);
  }
  std::print("\n");
}