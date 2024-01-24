//
// Created by in021397 on 12/14/2023.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "List/Graph/Graph.h"

using namespace std;

int main(){


    vector<string> words3Letters;
    vector<string> words4Letters;
    vector<string> words5Letters;


    // Open the file
    ifstream dictionaryFile("../turkish-dictionary.txt");
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

    list::Graph letter_3s = list::Graph(no_3letters);
    list::Graph letter_4s = list::Graph(no_4letters);
    list::Graph letter_5s = list::Graph(no_5letters);


    letter_3s.addFromVector(words3Letters);
    letter_4s.addFromVector(words4Letters);
    letter_5s.addFromVector(words5Letters);

    cout<<endl<<endl<<endl<<endl<<"Extra test cases"<<endl<<endl<<endl<<endl;
    int extraCases=3;
    string extraWords1[]={"fas","adil","bursa"};
    string extraWords2[]={"oje","tane","zorlu"};
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

    return 0; // Return success code
}