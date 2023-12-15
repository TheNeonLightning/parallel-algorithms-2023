#include <iostream>
#include <string>

#include <parlay/primitives.h>
#include <parlay/sequence.h>
#include <parlay/internal/get_time.h>

#include "bfs_seq.h"
#include "bfs_par.h"
#include "graph_utils.h"

parlay::sequence<parlay::sequence<int>> createCubeGraph(int side);

// **************************************************************
// Driver
// **************************************************************
int main(int argc, char* argv[]) {
  long side = 500;
  long runs = 5;
  bool checkCorrectness = false;

  if (argc > 1) {
    try { side = std::stol(argv[1]); }
    catch (...) { std::cout << "argv[1] - expected test cube size" << std::endl; return 1; }
  }
  if (argc > 2) {
    try { runs = std::stol(argv[2]); }
    catch (...) { std::cout << "argv[2] - expected number of test runs" << std::endl; return 1; }
  }
  if (argc > 3) {
    try { checkCorrectness = std::stol(argv[3]); }
    catch (...) { std::cout << "argv[3] - expected checkCorrectness boolean as number" << std::endl; return 1; }
  }
  std::cout << "Test params: side = " << side
            << "; runs = " << runs
            << "; checkCorrectness = " << checkCorrectness
            << std::endl;

  auto graph = createCubeGraph(side);
  graph_utils<int>::print_graph_stats(graph);

  for (int run = 0; run < runs; ++run) {
    auto start_seq = std::chrono::steady_clock::now();
    auto prev_seq = bfs_seq(0, graph);
    auto stop_seq = std::chrono::steady_clock::now();
    auto time_seq = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(stop_seq - start_seq).count());

    auto start_par = std::chrono::steady_clock::now();
    auto frontiers_par = bfs_par(0, graph);
    auto stop_par = std::chrono::steady_clock::now();
    auto time_par = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(stop_par - start_par).count());

    if (checkCorrectness) {
      for (int vertex = 0; vertex < graph.size(); ++vertex) {
        int layer = resolve_path_length(0, vertex, prev_seq);
        if (std::find(frontiers_par[layer].begin(), frontiers_par[layer].end(),
                      vertex) == frontiers_par[layer].end()) {
          std::cout << "Incorrect BFS!" << std::endl;
          return 1;
        }
      }
    }

    std::cout << "time_seq = " << time_seq << "ms; "
              << "time_par = " << time_par << "ms; "
              << "seq/par coef = " << time_seq / time_par << ';'
              << std::endl;
  }
  return 0;
}

parlay::sequence<parlay::sequence<int>> createCubeGraph(int side) {
  int side_sq = side * side;
  auto coordinates_to_index =
      [&](int x, int y, int z) {
    return x * side_sq + y * side + z;
  };
  parlay::sequence<parlay::sequence<int>> graph(side_sq * side, parlay::sequence<int>());
  for (int x = 0; x < side; ++x) {
    for (int y = 0; y < side; ++y) {
      for (int z = 0; z < side; ++z) {
        if (x > 0) {
          graph[coordinates_to_index(x, y, z)].push_back(coordinates_to_index(x - 1, y, z));
        }
        if (x < side - 1) {
          graph[coordinates_to_index(x, y, z)].push_back(coordinates_to_index(x + 1, y, z));
        }
        if (y > 0) {
          graph[coordinates_to_index(x, y, z)].push_back(coordinates_to_index(x, y - 1, z));
        }
        if (y < side - 1) {
          graph[coordinates_to_index(x, y, z)].push_back(coordinates_to_index(x, y + 1, z));
        }
        if (z > 0) {
          graph[coordinates_to_index(x, y, z)].push_back(coordinates_to_index(x, y, z - 1));
        }
        if (z < side - 1) {
          graph[coordinates_to_index(x, y, z)].push_back(coordinates_to_index(x, y, z + 1));
        }
      }
    }
  }
  return graph;
}
