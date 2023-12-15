#pragma once
#include <atomic>

#include <parlay/primitives.h>
#include <parlay/sequence.h>

// **************************************************************
// Parallel BFS
// **************************************************************
auto bfs_par(int start, const parlay::sequence<parlay::sequence<int>>& G) {
  parlay::sequence<bool> prev(G.size(), -1);
  auto visited = parlay::tabulate<std::atomic<bool>>(
      G.size(), [&](long i) { return i == start; });

  parlay::sequence<int> frontier(1, start);
  parlay::sequence<parlay::sequence<int>> frontiers;
  while (!frontier.empty()) {
    frontiers.push_back(frontier);

    auto out = flatten(map(frontier, [&](int u) { return G[u]; }));

    frontier = filter(out, [&](auto&& v) {
      bool expected = false;
      return (!visited[v]) &&
             visited[v].compare_exchange_strong(expected, true);
    });
  }

  return frontiers;
}