//
// Created by in021397 on 12/14/2023.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "List/Graph/Graph.h"

using namespace std;


int puzzle1(){
    vector<string> words3Letters;
    vector<string> words4Letters;
    vector<string> words5Letters;

    // Open the file
    ifstream dictionaryFile("../english-dictionary.txt");
    if (!dictionaryFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    int no_3letters=0,no_4letters=0,no_5letters=0;
    streampos initialPos = dictionaryFile.tellg();
    string line;
    while (getline(dictionaryFile, line)) {
        // Process each word in the line
        istringstream iss(line);
        string word;
        while (iss >> word) {
            // Count characters in each word and add to vectors
            //cout << "Word: " << word << ", Length: " << word.length() << endl;
            if (word.length()==3){
                words3Letters.push_back(word);
                no_3letters++;
            } else if(word.length()==4){
                words4Letters.push_back(word);
                no_4letters++;
            }
            else if(word.length()==5){
                words5Letters.push_back(word);
                no_5letters++;
            }
        }
    }
    //
    dictionaryFile.close();

    cout<<"Number of 3-letter words:" << no_3letters <<endl;
    cout<<"Number of 4-letter words:" << no_4letters <<endl;
    cout<<"Number of 5-letter words:" << no_5letters <<endl;

    // Create Graphs
    //Print words
//    cout << "3-letter words: ";
//    for (const auto& word : words3Letters) {
//        cout << word << " ";
//    }
//    cout << endl;
//
//    cout << "4-letter words: ";
//    for (const auto& word : words4Letters) {
//        cout << word << " ";
//    }
//    cout << endl;
//
//    cout << "5-letter words: ";
//    for (const auto& word : words5Letters) {
//        cout << word << " ";
//    }
//    cout << endl;


    //Save words
    ofstream words3LettersTxt("../3Letters.txt");
    for(string str:words3Letters){
        words3LettersTxt<<str<<endl;
    }
    words3LettersTxt.close();

    ofstream words4LettersTxt("../4Letters.txt");
    for(string str:words4Letters){
        words4LettersTxt<<str<<endl;
    }
    words4LettersTxt.close();

    ofstream words5LettersTxt("../5Letters.txt");
    for(string str:words5Letters){
        words5LettersTxt<<str<<endl;
    }
    words5LettersTxt.close();

    list::Graph letter_3s = list::Graph(no_3letters);
    list::Graph letter_4s = list::Graph(no_4letters);
    list::Graph letter_5s = list::Graph(no_5letters);


    letter_3s.addFromVector(words3Letters);
    letter_4s.addFromVector(words4Letters);
    letter_5s.addFromVector(words5Letters);


    int testCases=3;
    string testWords1[]={"cat","dark","stone"};
    string testWords2[]={"dog","barn","score"};
    list::Graph testGraphs[]={letter_3s,letter_4s,letter_5s};

    for (int i = 0; i < testCases; ++i) {
        string testResult, word1, word2;
        word1=testWords1[i];
        word2=testWords2[i];
        cout<<"-------------------------"<<endl;
        cout << "||Test Case: Adding Edges with One-Letter Difference ("<<word1.length()<<" letter words)" << endl;
        cout << "||Shortest Path from '"<< word1 <<"' to '"<<word2<<"' by BFS:" << endl;
        testResult=testGraphs[i].BFSearch(word1,word2);
        cout<<"||"<<testResult<<"||"<<endl;
        cout << "||Shortest Path from '"<< word1 <<"' to '"<<word2<<"' by Dijkstra:" << endl;
        testResult=testGraphs[i].DijkstraSearch(word1,word2);
        cout<<"||"<<testResult<<endl;
    }

    cout<<endl<<endl<<endl<<endl<<"Extra test cases"<<endl<<endl<<endl<<endl;
    int extraCases=3;
    string extraWords1[]={"bat","adam","hello"};
    string extraWords2[]={"mom","news","picky"};
    list::Graph extraGraphs[]={letter_3s,letter_4s,letter_5s};

    for (int i = 0; i < extraCases; ++i) {
        string testResult, word1, word2;
        word1=extraWords1[i];
        word2=extraWords2[i];
        cout<<"-------------------------"<<endl;
        cout << "||Test Case: Adding Edges with One-Letter Difference ("<<word1.length()<<" letter words)" << endl;
        cout << "||Shortest Path from '"<< word1 <<"' to '"<<word2<<"' by BFS:" << endl;
        testResult=extraGraphs[i].BFSearch(word1,word2);
        cout<<"||"<<testResult<<"||"<<endl;
        cout << "||Shortest Path from '"<< word1 <<"' to '"<<word2<<"' by Dijkstra:" << endl;
        testResult=extraGraphs[i].DijkstraSearch(word1,word2);
        cout<<"||"<<testResult<<endl;
    }

    return 0;
}

int puzzle2(){
    vector<string> words;

    // Open the file
    ifstream dictionaryFile("../english-dictionary.txt");
    if (!dictionaryFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    int no_of_words=0;
    streampos initialPos = dictionaryFile.tellg();
    string line;
    while (getline(dictionaryFile, line)) {
        // Process each word in the line
        istringstream iss(line);
        string word;
        while (iss >> word) {
            words.push_back(word);
            no_of_words++;
        }
    }
    dictionaryFile.close();
    cout<<"Words are read"<<endl;
    list::Graph words_graph = list::Graph(no_of_words);
    words_graph.addFromVector2(words);
    cout<<"Words are graphed"<<endl;

    std::filesystem::path currentPath = std::filesystem::current_path();
    std::cout << "Current Working Directory: " << currentPath << std::endl;

    // Rest of your code
    // Serialize the graph to a JSON string
    nlohmann::json serializedGraph = words_graph.toJson();
    std::string jsonString = serializedGraph.dump();
    //std::cout << "Serialized Graph:\n" << jsonString << std::endl;

    // Save the serialized graph to a file
    std::ofstream outputFile("../serialized_graph.json");
    if (outputFile.is_open()) {
        outputFile << jsonString;
        outputFile.close();
        std::cout << "Serialized Graph saved to file: serialized_graph.json" << std::endl;
    } else {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }




    int testCases=3;
    string testWords1[]={"Please ","cat","kick"};
    string testWords2[]={"adjust","score","grammar"};

    for (int i = 0; i < testCases; ++i) {
        string testResult, word1, word2;
        word1=testWords1[i];
        word2=testWords2[i];
        cout<<"-------------------------"<<endl;
        cout << "||Test Case: Adding Edges with One-Letter Difference" << endl;
        cout << "||Shortest Path from '"<< word1 <<"' to '"<<word2<<"' by BFS:" << endl;
        testResult=words_graph.BFSearch(word1,word2);
        cout<<"||"<<testResult<<"||"<<endl;
        cout << "||Shortest Path from '"<< word1 <<"' to '"<<word2<<"' by Dijkstra:" << endl;
        testResult=words_graph.DijkstraSearch(word1,word2);
        cout<<"||"<<testResult<<endl;
    }

    return 0;
}

int main(){

    puzzle2();

    return 0; // Return success code
}