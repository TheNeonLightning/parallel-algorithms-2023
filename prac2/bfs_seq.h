#pragma once
#include <atomic>
#include <queue>

#include <parlay/primitives.h>
#include <parlay/sequence.h>

// **************************************************************
// Sequential BFS
// **************************************************************
auto bfs_seq(int start, const parlay::sequence<parlay::sequence<int>>& G) {
  parlay::sequence<int> prev(G.size(), -1);
  parlay::sequence<bool> visited(G.size(), false);
  std::queue<int> frontier;

  frontier.push(start);
  visited[start] = true;
  while (!frontier.empty()) {
    for (int next : G[frontier.front()]) {
      if (!visited[next]) {
        prev[next] = frontier.front();
        frontier.push(next);
        visited[next] = true;
      }
    }
    frontier.pop();
  }
  return prev;
}

int resolve_path_length(int start, int vertex, const parlay::sequence<int>& prev) {
  int current = vertex;
  int length;
  for (length = 0; current != -1 && current != start; ++length) {
    current = prev[current];
  }

  return current == start ? length : -1;
}