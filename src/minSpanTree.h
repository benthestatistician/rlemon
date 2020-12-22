#include <Rcpp.h>
#include <lemon/kruskal.h>
#include <lemon/list_graph.h>
#include <lemon/min_cost_arborescence.h>
#include <vector>

using namespace lemon;

//' MST Algorithms
//' @name Minimum-Spanning-Tree-Algorithms
//' @param arcSources, a vector corresponding to the source nodes of a graph's edges
//' @param arcTargets, a vector corresponding to the destination nodes of a graph's edges
//' @param arcDistances, a vector corresponding to the distances of nodes of a graph's edges
//' @param numNodes, the number of nodes in the graph
//' @return A list containing three entries: 1) Two vectors corresponding the source and target nodes of the edges in the trre, and 2) the total minimum spanning tree value.
//> NULL

//' Arborescence Algorithms
//' @name Minimum-Cost-Arborescence-Algorithms
//' @param arcSources, a vector corresponding to the source nodes of a graph's edges
//' @param arcTargets, a vector corresponding to the destination nodes of a graph's edges
//' @param arcDistances, a vector corresponding to the distances of nodes of a graph's edges
//' @param sourceNode, the source node
//' @param numNodes, the number of nodes in the graph
//' @return A list containing three entries: 1) Two vectors corresponding the source and target nodes of the edges in the tree, and 2) the total minimum spanning tree value.
//> NULL

//' @rdname Minimum-Spanning-Tree-Algorithms
// [[Rcpp::export]]
Rcpp::List KruskalRunner(std::vector<int> arcSources,
                         std::vector<int> arcTargets,
                         std::vector<int> arcDistances, int numNodes) {
  ListDigraph g;

  std::vector<ListDigraph::Node> nodes;

  for (int i = 0; i < numNodes; ++i) {
    ListDigraph::Node n = g.addNode();
    nodes.push_back(n);
  }
  int NUM_ARCS = arcSources.size();
  ListDigraph::ArcMap<int> dists(g);
  std::vector<ListDigraph::Arc> tree;
  std::vector<ListDigraph::Arc> arcs;

  for (int i = 0; i < NUM_ARCS; ++i) {
    ListDigraph::Arc a = g.addArc(nodes[arcSources[i]], nodes[arcTargets[i]]);
    arcs.push_back(a);
    dists[a] = arcDistances[i];
  }
  int treeVal = kruskal(g, dists, std::back_inserter(tree));
  std::vector<int> treeSources;
  std::vector<int> treeTargets;
  for (int i = 0; i < tree.size(); i++) {
    treeSources.push_back(g.id(g.source(tree[i])));
    treeTargets.push_back(g.id(g.target(tree[i])));
  }
  return Rcpp::List::create(treeSources, treeTargets, treeVal);
}

//' @rdname Minimum-Cost-Arborescence-Algorithms
// [[Rcpp::export]]
Rcpp::List MinCostArborescenceRunner(std::vector<int> arcSources,
                                     std::vector<int> arcTargets,
                                     std::vector<int> arcDistances,
                                     int sourceNode, int numNodes) {
  ListDigraph g;

  std::vector<ListDigraph::Node> nodes;

  for (int i = 0; i < numNodes; ++i) {
    ListDigraph::Node n = g.addNode();
    nodes.push_back(n);
  }
  int NUM_ARCS = arcSources.size();
  ListDigraph::ArcMap<int> dists(g);
  std::vector<ListDigraph::Arc> tree;
  std::vector<ListDigraph::Arc> arcs;

  for (int i = 0; i < NUM_ARCS; ++i) {
    ListDigraph::Arc a = g.addArc(nodes[arcSources[i]], nodes[arcTargets[i]]);
    arcs.push_back(a);
    dists[a] = arcDistances[i];
  }
  ListDigraph::ArcMap<int> arbs(g);
  int arbVal = minCostArborescence(g, dists, nodes[sourceNode], arbs);
  std::vector<int> treeSources;
  std::vector<int> treeTargets;
  for (int i = 0; i < NUM_ARCS; i++) {
    if (arbs[arcs[i]]) {
      treeSources.push_back(g.id(g.source(arcs[i])));
      treeTargets.push_back(g.id(g.target(arcs[i])));
    }
  }
  return Rcpp::List::create(treeSources, treeTargets, arbVal);
}