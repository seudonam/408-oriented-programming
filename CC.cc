#include "DepthFirstOrder.hh"
#include "Graph.hh"

// 图连通性
struct CC {
  ns::deque<bool> marked;
  ns::deque<int> id;
  int count;

  CC(const Graph &G) : marked(G.V, false), id(G.V), count{0} {
    for (int v = 0; v < G.V; ++v)
      if (!marked[v]) {
        bfs(G, v);
        ++count;
      }
  }
  void dfs(const Graph &G, int v) {
    // 首次发现时标记顶点
    marked[v] = true;
    id[v] = count;
    for (int w : G.adj[v]) {
      if (!marked[w])
        dfs(G, w);
    }
  }
  void bfs(const Graph &G, int s) {
    // 首次发现时标记顶点
    marked[s] = true;
    id[s] = count;
    ns::deque<int> queue;
    queue.push_back(s);
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop_front();
      for (int w : G.adj[v])
        if (!marked[w]) {
          marked[w] = true;
          id[w] = count;
          queue.push_back(w);
        }
    }
  }
  bool connected(int v, int w) const { return id[v] == id[w]; }
};

// 有向图都是以强连通块为顶点的有向无环图
struct KosarajuSCC {
  ns::deque<bool> marked;
  ns::deque<int> id;
  int count;

  KosarajuSCC(const Digraph &G) : marked(G.V, false), id(G.V), count{0} {
    DepthFirstOrder DFS(G.reverse());
    for (int v : DFS.reversePost())
      if (!marked[v]) {
        dfs(G, v);
        ++count;
      }
  }
  void dfs(const Digraph &G, int v) {
    marked[v] = true;
    id[v] = count;
    for (int w : G.adj[v]) {
      if (!marked[w])
        dfs(G, w);
    }
  }
  bool connected(int v, int w) const { return id[v] == id[w]; }
};

struct TarjanSCC {
  ns::deque<bool> marked;
  ns::deque<int> id, low, stack;
  int pre, count;
  TarjanSCC(const Digraph &G)
      : marked(G.V, false), id(G.V), low(G.V, 0), pre{0}, count{0} {
    for (int v = 0; v < G.V; v++)
      if (!marked[v])
        dfs(G, v);
  }

  void dfs(const Digraph &G, int v) {
    marked[v] = true;
    low[v] = pre++;
    int min = low[v];
    stack.push_back(v);
    for (int w : G.adj[v]) {
      if (!marked[w])
        dfs(G, w);
      if (low[w] < min)
        min = low[w];
    }
    if (min < low[v]) {
      low[v] = min;
      return;
    }
    int w;
    do {
      w = stack.back();
      stack.pop_back();
      id[w] = count;
      low[w] = G.V;
    } while (w != v);
    count++;
  }
  bool connected(int v, int w) const { return id[v] == id[w]; }
};

template <class CC, class Graph> void printCC(const Graph &G) {
  CC cc(G);
  std::print("vertex\t");
  for (int i = 0; i < G.V; ++i)
    std::print("v{}\t", i);
  std::print("\n");
  std::print("id\t");
  for (int i = 0; i < G.V; ++i)
    std::print("{}\t", cc.id[i]);
  std::print("\n");
}

int main() {
  constexpr int v{8}, e{8};
  Graph G(v);
  generateGraph(G, e);
  printGraph(G);
  std::print("\n");
  printCC<CC>(G);
  std::print("\n");

  Digraph DG(v);
  generateGraph(DG, e);
  printGraph(DG);
  std::print("\nKosaraju\n");
  printCC<KosarajuSCC>(DG);
  std::print("\nTarjan\n");
  printCC<TarjanSCC>(DG);
}