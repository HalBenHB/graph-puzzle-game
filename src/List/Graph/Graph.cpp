//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#include <iostream>
#include "Graph.h"
#include "../../Array/DisjointSet.h"
#include "../Queue.h"
#include "../../Array/Heap/MinHeap.h"

namespace list {

    Graph::Graph(int _vertexCount) : AbstractGraph(_vertexCount){
        edges = new EdgeList[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            edges[i] = EdgeList();
        }
    }

    void Graph::addEdge(int from, int to) {
        Edge* edge = new Edge(from, to, 1);
        edges[from].insert(edge);
    }

    void Graph::addEdge(int from, int to, int weight) {
        Edge* edge = new Edge(from, to, weight);
        edges[from].insert(edge);
    }

    Graph::~Graph() {
        delete[] edges;
    }

    void Graph::connectedComponentsDisjointSet() {
        Edge* edge;
        int toNode;
        DisjointSet sets = DisjointSet(vertexCount);
        for (int fromNode = 0; fromNode < vertexCount; fromNode++){
            edge = edges[fromNode].getHead();
            while (edge != nullptr){
                toNode = edge->getTo();
                if (sets.findSetRecursive(fromNode) != sets.findSetRecursive(toNode)){
                    sets.unionOfSets(fromNode, toNode);
                }
                edge = edge->getNext();
            }
        }
    }

    void Graph::depthFirstSearch(bool *visited, int fromNode) {
        Edge* edge;
        int toNode;
        edge = edges[fromNode].getHead();
        while (edge != nullptr){
            toNode = edge->getTo();
            if (!visited[toNode]){
                visited[toNode] = true;
                depthFirstSearch(visited, toNode);
            }
            edge = edge->getNext();
        }
    }

    void Graph::breadthFirstSearch(bool *visited, int startNode) {
        Edge* edge;
        int fromNode, toNode;
        Queue queue = Queue();
        queue.enqueue(new Node(startNode));
        while (!queue.isEmpty()){
            fromNode = queue.dequeue()->getData();
            edge = edges[fromNode].getHead();
            while (edge != nullptr) {
                toNode = edge->getTo();
                if (!visited[toNode]){
                    visited[toNode] = true;
                    queue.enqueue(new Node(toNode));
                }
                edge = edge->getNext();
            }
        }
    }

    Path *Graph::bellmanFord(int source) {
        Edge* edge;
        Path* shortestPaths = initializePaths(source);
        for (int i = 0; i < vertexCount - 1; i++){
            for (int fromNode = 0; fromNode < vertexCount; fromNode++){
                edge = edges[fromNode].getHead();
                while (edge != nullptr){
                    int toNode = edge->getTo();
                    int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                    if (newDistance < shortestPaths[toNode].getDistance()){
                        shortestPaths[toNode].setDistance(newDistance);
                        shortestPaths[toNode].setPrevious(fromNode);
                    }
                    edge = edge->getNext();
                }
            }
        }
        return shortestPaths;
    }

    Path *Graph::dijkstra(int source) {
        Edge* edge;
        Path* shortestPaths = initializePaths(source);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(shortestPaths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            edge = edges[fromNode].getHead();
            while (edge != nullptr){
                int toNode = edge->getTo();
                int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                if (newDistance < shortestPaths[toNode].getDistance()){
                    int position = heap.search(toNode);
                    heap.update(position, newDistance);
                    shortestPaths[toNode].setDistance(newDistance);
                    shortestPaths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }
        return shortestPaths;
    }

    Edge *Graph::edgeList(int& edgeCount) {
        Edge* list;
        edgeCount = 0;
        for (int i = 0; i < vertexCount; i++){
            Edge* edge = edges[i].getHead();
            while (edge != nullptr){
                edgeCount++;
                edge = edge->getNext();
            }
        }
        list = new Edge[edgeCount];
        int index = 0;
        for (int i = 0; i < vertexCount; i++){
            Edge* edge = edges[i].getHead();
            while (edge != nullptr){
                list[index] = Edge(edge->getFrom(), edge->getTo(), edge->getWeight());
                index++;
                edge = edge->getNext();
            }
        }
        return list;
    }

    void Graph::prim() {
        Path* paths = initializePaths(0);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(paths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            Edge* edge = edges[fromNode].getHead();
            while (edge != nullptr){
                int toNode = edge->getTo();
                if (paths[toNode].getDistance() > edge->getWeight()){
                    int position = heap.search(toNode);
                    heap.update(position, edge->getWeight());
                    paths[toNode].setDistance(edge->getWeight());
                    paths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }
    }

    void Graph::addFromVector(const std::vector<std::string>& vector1) {

        for (int i = 0; i < vertexCount; ++i) {
            edges[i].setWord(vector1[i]);
            for (int j = 0; j < i; ++j) {
                if (oneDifferenceCheck(vector1[j],vector1[i])){
                    addEdge(i, j);
                    addEdge(j, i);
                }
            }
        }
    }

    bool Graph::oneDifferenceCheck(std::string string1, std::string string2){
        int differences = 0;
        // Compare each character
        for (size_t i = 0; i < string1.length(); ++i) {
            if (string1[i] != string2[i]) {
                // Increment the differences count
                ++differences;
                // If more than one difference is found, return false
                if (differences > 1) {
                    return false;
                }
            }
        }
        return true;
    }

    EdgeList Graph::getEdgeList(int n) {
        return edges[n];
    }

    std::string Graph::BFSearch(std::string word1,std::string word2) {
        int startNode=-1;
        for (int i = 0; i < vertexCount; ++i) {
            if (edges[i].getWord()==word1){
                startNode=i;
                break;
            }
        }

        if (startNode==-1){
            cerr << "The word not found! word1: " << word1 << endl;
            return "null";
        }

        bool* visited;

        visited= new bool [vertexCount];
        int* prevs;
        prevs=new int [vertexCount];
        for (int i = 0; i < vertexCount; ++i) {
            prevs[i]=-1;
        }
        Edge* edge;
        int fromNode, toNode;
        Queue queue = Queue();
        queue.enqueue(new Node(startNode));
        string word3;
        string path;
        while (!queue.isEmpty()){
            fromNode = queue.dequeue()->getData();
            edge = edges[fromNode].getHead();
            word3 = edges[fromNode].getWord();

            if (word3==word2){
                for (int i=fromNode;fromNode>=0;fromNode=prevs[fromNode]) {
                    if(path==""){
                        path = edges[fromNode].getWord();
                    }
                    else{
                        path = edges[fromNode].getWord() + "->" + path;
                    }
                    if (edges[fromNode].getWord()==word1){
                        break;
                    }
                }
                 return path;
            }
            while (edge != nullptr) {
                toNode = edge->getTo();
                if (!visited[toNode]){
                    visited[toNode] = true;
                    prevs[toNode]=fromNode;
                    queue.enqueue(new Node(toNode));
                }
                edge = edge->getNext();
            }
        }
        cout<<path<<endl;
        return "null";
    }

    std::string Graph::DijkstraSearch(std::string word1, std::string word2) {
        Edge* edge;
        int source=-1;
        for (int i = 0; i < vertexCount; ++i) {
            if (edges[i].getWord()==word1){
                source=i;
                break;
            }
        }

        if (source==-1){
            cerr << "The word not found! word1: " << word1 << endl;
            return "null";
        }

        Path* shortestPaths = initializePaths(source);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(shortestPaths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            edge = edges[fromNode].getHead();

            while (edge != nullptr){
                int toNode = edge->getTo();
                int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                if (newDistance < shortestPaths[toNode].getDistance()){
                    int position = heap.search(toNode);
                    heap.update(position, newDistance);
                    shortestPaths[toNode].setDistance(newDistance);
                    shortestPaths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }

        int result;
        for (int i = 0; i < vertexCount; ++i) {
            if (edges[i].getWord()==word2){
                result=i;
                break;
            }
        }

        string path;
        path=""+word2;
        for (int i = shortestPaths[result].getPrevious();i>0 ; i=shortestPaths[i].getPrevious()) {
            path=edges[i].getWord() + "->" + path;
        }

//        cout<<path<<endl;

        return path;
    }
}