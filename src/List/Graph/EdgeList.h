//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#ifndef DATASTRUCTURES_CPP_EDGELIST_H
#define DATASTRUCTURES_CPP_EDGELIST_H


#include "Edge.h"
#include "../../nlohmann/json.hpp"


class EdgeList {
private:
    Edge* head;
    Edge* tail;
    std::string word;
public:
    [[nodiscard]] const std::string &getWord() const;
    void setWord(const std::string &word1);
    EdgeList();
    ~EdgeList();
    bool isEmpty() const;
    Edge* search(int to) const;
    void insert(Edge* newEdge);
    Edge* getHead();

    // Serialization
    nlohmann::json toJson() const {
        nlohmann::json edgesJson = nlohmann::json::array();
        Edge* current = head;
        while (current != nullptr) {
            edgesJson.push_back(current->toJson());
            current = current->getNext();
        }
        return {
                {"edges", edgesJson},
                {"word", word}
                // Add more fields as needed
        };
    }

    // Deserialization
    static EdgeList fromJson(const nlohmann::json& j) {
        EdgeList edgeList;
        for (const auto& edgeJson : j.at("edges")) {
            Edge edge = Edge::fromJson(edgeJson);
            // Add the edge to the edge list
            // (You'll need to implement a method to add an edge to the list)
        }
        edgeList.word = j.at("word").get<std::string>();
        // Retrieve other fields as needed
        return edgeList;
    }
};


#endif //DATASTRUCTURES_CPP_EDGELIST_H