#include "tree_packing.hpp"

#include <cmath>
#include "spanning_tree.hpp"

TreePacking::TreePacking(const MultiGraph& graph, double epsilon) : mGraph(graph) {
    mEpsilon = epsilon;
    mTreeWeight = epsilon / (std::log(graph.numSimpleEdges()) * 3);

    size_t numEdges = graph.edges().size();
    std::vector<EdgeWeight> loads(numEdges, 0.0);
    std::vector<EdgeMultiplicity> simpleEdgeCounters(numEdges, 0);

    while(true) {
        EdgeSelection selection(graph.numVertices() - 1);
        if (!minSpanningTree(selection.data(), selection.size(), graph, loads.data(), loads.size())) {
            return;
        }
        for (size_t edgeIndex : selection) {
            if (loads[edgeIndex] + mTreeWeight > 1.0) {
                return;
            }
            simpleEdgeCounters[edgeIndex]++;
            if (simpleEdgeCounters[edgeIndex] >= graph.edges()[edgeIndex].multiplicity()) {
                simpleEdgeCounters[edgeIndex] = 0;
                loads[edgeIndex] += mTreeWeight;
            }
        }
        mTrees.push_back(std::move(selection));
    }
}