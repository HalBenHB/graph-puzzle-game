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
        nlohmann::json j;
        j["from"] = from;
        j["to"] = to;
        j["weight"] = weight;
        // Assuming next is a pointer to another Edge
        if (next) {
            j["next"] = next->toJson();  // Recursively serialize next
        }
        return j;
    }

// Deserialization
    static Edge fromJson(const nlohmann::json& j) {
        int from = j["from"].get<int>();
        int to = j["to"].get<int>();
        int weight = j["weight"].get<int>();

        Edge edge(from, to, weight);

        // Check if "next" key exists in JSON
        if (j.find("next") != j.end()) {
            *edge.next = Edge::fromJson(j["next"]);  // Recursively deserialize next
        }

        return edge;
    }
};


#endif //DATASTRUCTURES_CPP_EDGE_H