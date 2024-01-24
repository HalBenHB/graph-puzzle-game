//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#ifndef DATASTRUCTURES_CPP_EDGELIST_H
#define DATASTRUCTURES_CPP_EDGELIST_H


#include "Edge.h"

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
};


#endif //DATASTRUCTURES_CPP_EDGELIST_H