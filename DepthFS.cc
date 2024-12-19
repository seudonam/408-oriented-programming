#include "vector.hh"
#include <cstdlib>
#include <ctime>
#include <print>

enum class genre { UNDISCOVERED, DISCOVERED, VISITED };
using AdjVec = ns::vector<ns::vector<int>>;

struct DepthFirstSearch {
  int clock{0};
  ns::vector<genre> status;
  ns::vector<int> dTime, fTime, parent;
  DepthFirstSearch(const AdjVec &adj)
      : status(adj.size(), genre::UNDISCOVERED), dTime(adj.size()),
        fTime(adj.size()), parent(adj.size(), -1) {
    for (int v = 0; v < adj.size(); v++)
      if (status[v] == genre::UNDISCOVERED)
        dfs(adj, v);
  }
  // Tree Edge: DISCOVERED v  to UNDISCOVERED w
  // Backward Edge: DISCOVERED v to DISCOVERED w
  // Forward Edge: DISCOVERED v to VISITED w && dTime(v) < dTime(w)
  // Cross Edge: DISCOVERED v to VISITED w && dTime(v) > dTime(w)
  void dfs(const AdjVec &adj, int v) {
    dTime[v] = clock++;
    status[v] = genre::DISCOVERED;

    for (int w : adj[v])
      switch (status[w]) {
      case genre::UNDISCOVERED:
        parent[w] = v;
        dfs(adj, w);
        break;
      case genre::DISCOVERED:
        break;
      case genre::VISITED:
        break;
      }

    status[v] = genre::VISITED;
    fTime[v] = clock++;
  }
};

int main() {
  constexpr int v{8}, e{16};
  std::srand(std::time(nullptr));
  AdjVec G(v);
  ns::vector<int> a(e), b(e);
  int i{0};
  while (i < e) {
    a[i] = std::rand() % v, b[i] = std::rand() % v;
    if (a[i] == b[i])
      continue;
    int j{0};
    for (; j < i; ++j) {
      if (a[i] == a[j] && b[i] == b[j])
        break;
      if (a[i] == b[j] && b[i] == a[j])
        break;
    }
    if (i != j)
      continue;
    G[a[i]].push_back(b[i]);
    ++i;
  }
  DepthFirstSearch DepthFirstPaths(G);
  for (int v : DepthFirstPaths.dTime)
    std::print("{}\t", v);
  std::print("\n");
  for (int v : DepthFirstPaths.fTime)
    std::print("{}\t", v);
  std::print("\n");
  for (int v : DepthFirstPaths.parent)
    std::print("{}\t", v);
  std::print("\n");
}