#include <vector>
#include "bellman_ford.h"
#include "list_graph.h"

using namespace lemon;
using namespace std;

using Cost = int;

using Graph = ListDigraph;
using Node = Graph::Node;
using Arc = Graph::Arc;

template<typename ValueType>
using ArcMap = ListDigraph::ArcMap<ValueType>;

template<typename ValueType>
using NodeMap = ListDigraph::NodeMap<ValueType>;


int main()
{
    Graph g;

    vector<Node> nodes;
    for(int i = 0; i < 9; ++i)
    {
        Node n = g.addNode();
        nodes.push_back(n);
    }

    ArcMap<Cost> costs(g);
    ArcMap<Cost> preds(g);
    NodeMap<Cost> dists(g);

    vector<Arc> arcs;

    vector<int> arc_src{1, 1, 2, 2, 2, 3, 3, 4, 4,5,5,5,6,6,7};
    vector<int> arc_targ{2, 3, 3, 4, 5, 4, 7, 5, 7,7,8,6,8,9,8};
    vector<int> arc_costs{5, 2, 2, 3, 7, 3, 9, 2, 6,5,7,8,3,4,2};
    int NUM_ARCS = arc_src.size();

    for(int i = 0; i < NUM_ARCS; ++i)
    {
        Arc a = g.addArc(nodes[arc_src[i] - 1], nodes[arc_targ[i] - 1]);
        arcs.push_back(a);
        costs[arcs[i]] = arc_costs[i];
    }

    bellmanFord(g, costs).predMap(preds).distMap(dists).run(nodes[0]);

    

    return 1;
}