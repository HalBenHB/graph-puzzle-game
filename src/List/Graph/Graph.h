//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#ifndef DATASTRUCTURES_CPP_GRAPH_H
#define DATASTRUCTURES_CPP_GRAPH_H


#include <vector>
#include <string>
#include "EdgeList.h"
#include "../../General/AbstractGraph.h"

namespace list {

    class Graph : public AbstractGraph{
    private:
        EdgeList *edges;
    public:
        explicit Graph(int vertexCount);
        EdgeList getEdgeList(int n);
        ~Graph();
        void addEdge(int from, int to);
        void addEdge(int from, int to, int weight);
        void connectedComponentsDisjointSet();
        Path* bellmanFord(int source);
        Path* dijkstra(int source);
        void prim();
        void addFromVector(const std::vector<std::string>& vector1);
        std::string BFSearch(std::string word1,std::string word2);
        std::string DijkstraSearch(std::string word1,std::string word2);

    protected:
        void depthFirstSearch(bool* visited, int fromNode) override;
        void breadthFirstSearch(bool* visited, int startNode) override;
        Edge* edgeList(int& edgeCount) override;

        static bool oneDifferenceCheck(std::string string1, std::string string2);
    };

}
#endif //DATASTRUCTURES_CPP_GRAPH_H