//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#ifndef DATASTRUCTURES_CPP_EDGE_H
#define DATASTRUCTURES_CPP_EDGE_H


#include <string>
#include "../../nlohmann/json.hpp"

class Edge {
private:
    int from;
    int to;
    int weight;
    Edge* next;
public:
    Edge();
    Edge(int from, int to, int weight);
    void setNext(Edge* _next);
    Edge* getNext() const;
    int getFrom() const;
    int getTo() const;
    int getWeight() const;

    // Serialization
    nlohmann::json toJson() const {
        return {
                {"from", from},
                {"to", to},
                {"weight", weight}
                // Add more fields as needed
        };
    }

    // Deserialization
    static Edge fromJson(const nlohmann::json& j) {
        Edge edge;
        edge.from = j.at("from").get<int>();
        edge.to = j.at("to").get<int>();
        edge.weight = j.at("weight").get<int>();
        // Retrieve other fields as needed
        return edge;
    }
};


#endif //DATASTRUCTURES_CPP_EDGE_H