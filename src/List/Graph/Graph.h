//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#ifndef DATASTRUCTURES_CPP_GRAPH_H
#define DATASTRUCTURES_CPP_GRAPH_H

#include <vector>
#include <string>
#include "EdgeList.h"
#include "../../General/AbstractGraph.h"
#include "../../nlohmann/json.hpp"

namespace list {

    class Graph : public AbstractGraph{
    private:
        EdgeList *edgeLists;
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
        void addFromVector2(const std::vector<std::string>& vector1);

        // Serialization
        nlohmann::json toJson() const {
            nlohmann::json edgesJson = nlohmann::json::array();
            for (int i = 0; i < vertexCount; i++) {
                edgesJson.push_back(edgeLists[i].toJson());
            }
            return {
                    {"vertexCount", vertexCount},
                    {"edges", edgesJson}
            };
        };

        // Deserialization
        static Graph fromJson(const nlohmann::json& j) {
            list::Graph graph = Graph(j.at("vertexCount"));
            // Deserialize the edges first

            for (int i = 0; i < j.at("vertexCount"); i++) {
                graph.edgeLists[i] = EdgeList();
            }

            int i=0;
            // Assuming 'edges' is an array of vertices, each with an 'edges' array
            for (const auto& edgeList : j.at("edges")) {
                // Deserialize the 'edges' array for each vertex
                graph.edgeLists[i]=EdgeList::fromJson(edgeList);
                i++;
            }

            return graph;
        };

        Graph();

    protected:
        void depthFirstSearch(bool* visited, int fromNode) override;
        void breadthFirstSearch(bool* visited, int startNode) override;
        Edge* edgeList(int& edgeCount) override;
        static bool oneDifferenceCheck(std::string string1, std::string string2);
        static bool oneDifferenceCheck2(std::string string1, std::string string2);
    };

}
#endif //DATASTRUCTURES_CPP_GRAPH_H