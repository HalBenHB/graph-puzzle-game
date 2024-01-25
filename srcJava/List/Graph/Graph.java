package List.Graph;

import java.util.Vector;

import javax.xml.transform.Source;

import Array.Heap.HeapNode;
import Array.Heap.MinHeap;
import General.AbstractGraph;
import General.Path;
import List.Queue;
import List.Node;

public class Graph extends AbstractGraph {

    private EdgeList[] edgeLists;

    public Graph(int vertexCount) {
        super(vertexCount);
        edgeLists = new EdgeList[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            edgeLists[i] = new EdgeList();
        }
    }

    public void addEdge(int from, int to) {
        Edge edge = new Edge(from, to, 1);
        edgeLists[from].insert(edge);

    }

    public void addEdge(int from, int to, int weight) {
        Edge edge = new Edge(from, to, weight);
        edgeLists[from].insert(edge);
    };

    protected Edge[] edgeList() {
        Edge[] list;
        int edgeCount = 0;
        for (int i = 0; i < vertexCount; i++) {
            Edge edge = edges[i].getHead();
            while (edge != null) {
                edgeCount++;
                edge = edge.getNext();
            }
        }
        list = new Edge[edgeCount];
        int index = 0;
        for (int i = 0; i < vertexCount; i++) {
            Edge edge = edges[i].getHead();
            while (edge != null) {
                list[index] = new Edge(edge.getFrom(), edge.getTo(), edge.getWeight());
                index++;
                edge = edge.getNext();
            }
        }
        return list;

    }

    protected void depthFirstSearch(boolean[] visited, int fromNode) {
        Edge edge;
        int toNode;
        edge = edgeLists[fromNode].getHead();
        while (edge != null) {
            toNode = edge.getTo();
            if (!visited[toNode]) {
                visited[toNode] = true;
                depthFirstSearch(visited, toNode);
            }
            edge = edge.getNext();
        }
    }

    protected void breadthFirstSearch(boolean[] visited, int startNode) {
        Edge edge;
        int fromNode, toNode;
        Queue queue = new Queue();
        queue.enqueue(new Node(startNode));
        while (!queue.isEmpty()) {
            fromNode = queue.dequeue().getData();
            edge = edgeLists[fromNode].getHead();
            while (edge != null) {
                toNode = edge.getTo();
                if (!visited[toNode]) {
                    visited[toNode] = true;
                    queue.enqueue(new Node(toNode));
                }
                edge = edge.getNext();
            }
        }
    }

    public void addFromVector(Vector<String> vector) {

        for (int i = 0; i < vertexCount; i++) {
            edgeLists[i].setWord(vector.get(i));
            for (int j = 0; j < i; j++) {
                if (oneDifferenceCheck(vector.get(i), vector.get(j))) {
                    addEdge(i, j);
                    addEdge(j, i);
                }
            }
        }
    }

    private Boolean oneDifferenceCheck(String string1, String string2) {

        int length_difference = Math.abs(string1.length() - string2.length());

        if (length_difference > 1) {
            return false;
        } else if (length_difference == 1) {
            int diffCount = 0;
            // Iterate through the characters of both strings
            for (int i = 0, j = 0; i < string1.length() && j < string2.length(); ++i, ++j) {
                if (string1.charAt(i) != string2.charAt(j)) {
                    // Increment the difference count
                    ++diffCount;

                    // If there is more than one difference, return false
                    if (diffCount > 1) {
                        return false;
                    }

                    // If the lengths are different, adjust the index for the longer string
                    if (string1.length() > string2.length()) {
                        --j;
                    } else if (string1.length() < string2.length()) {
                        --i;
                    }
                }
            }
            return true;
        } else {
            int diffCount = 0;
            // Compare each character
            for (int i = 0; i < string1.length(); ++i) {
                if (string1.charAt(i) != string2.charAt(i)) {
                    // Increment the differences count
                    ++diffCount;
                    // If more than one difference is found, return false
                    if (diffCount > 1) {
                        return false;
                    }
                }
            }
            return true;
        }
    }

    public String BFSearch(String word1, String word2) {

        int startNode = -1;
        for (int i = 0; i < vertexCount; i++) {
            if (edgeLists[i].getWord().equals(word1)) {
                startNode = i;
                break;
            }
        }

        if (startNode == -1) {
            System.err.println("The word not found! word1: " + word1);
            return null;
        }

        Boolean[] visited = new Boolean[vertexCount];
        for (int i = 0; i < vertexCount; ++i) {
            visited[i] = false;
        }
        int[] prevs = new int[vertexCount];
        for (int i = 0; i < vertexCount; ++i) {
            prevs[i] = -1;
        }
        Edge edge;
        int fromNode, toNode;
        Queue queue = new Queue();
        queue.enqueue(new Node(startNode));
        String word3;
        String path = "";

        while (!queue.isEmpty()) {
            fromNode = queue.dequeue().getData();
            edge = edgeLists[fromNode].getHead();
            word3 = edgeLists[fromNode].getWord();

            if (word3.equals(word2)) {
                for (int i = fromNode; fromNode >= 0; fromNode = prevs[fromNode]) {
                    if (path == "") {
                        path = edgeLists[fromNode].getWord();
                    } else {
                        path = edgeLists[fromNode].getWord() + "->" + path;
                    }
                    if (edgeLists[fromNode].getWord().equals(word1)) {
                        break;
                    }
                }
                return path;
            }
            while (edge != null) {
                toNode = edge.getTo();
                if (!visited[toNode]) {
                    visited[toNode] = true;
                    prevs[toNode] = fromNode;
                    queue.enqueue(new Node(toNode));
                }
                edge = edge.getNext();
            }
        }
        System.out.println("path");
        return null;
    }

    public String DijkstraSearch(String word1, String word2) {
        Edge edge;
        int source = -1;

        for (int i = 0; i < vertexCount; i++) {
            if (edgeLists[i].getWord().equals(word1)) {
                source = i;
                break;
            }
        }

        if (source == -1) {
            System.err.println("The word not found! word1: " + word1);
            return null;
        }
        Path[] shortestPaths = initializePaths(source);

        MinHeap heap = new MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++) {
            heap.insert(new HeapNode(shortestPaths[i].getDistance(), i));
        }
        while (!heap.isEmpty()) {
            HeapNode node = heap.delete();
            int fromNode = node.getName();
            edge = edgeLists[fromNode].getHead();

            while (edge != null) {
                int toNode = edge.getTo();
                int newDistance = shortestPaths[fromNode].getDistance() + edge.getWeight();
                if (newDistance < shortestPaths[toNode].getDistance()) {
                    int position = heap.search(toNode);
                    System.out.println(toNode + " - " + position);
                    heap.update(position, newDistance);
                    shortestPaths[toNode].setDistance(newDistance);
                    shortestPaths[toNode].setPrevious(fromNode);
                }
                edge = edge.getNext();
            }
        }

        int result = -1;
        for (int i = 0; i < vertexCount; i++) {
            if (edgeLists[i].getWord().equals(word2)) {
                result = i;
                break;
            }
        }

        String path;
        path = "" + word2;
        for (int i = shortestPaths[result].getPrevious(); i > 0; i = shortestPaths[i].getPrevious()) {
            path = edgeLists[i].getWord() + "->" + path;
        }

        return path;

    }
}
