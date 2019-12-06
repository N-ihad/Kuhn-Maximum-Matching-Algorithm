//
//  kihm_algorithm.cpp
//  Kuhn_algorithm
//
//  Created by Nihad on 11/17/2019.
//  Copyright © 2019 Nihad.Corp. All rights reserved.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <random>
#include <chrono>

using namespace std;
typedef std::chrono::high_resolution_clock Clock;
vector<vector<int>> bipartiteGraph;
vector<int> match;
int n1, n2;
vector<char> usedVertices;

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& bipartiteGraph) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(bipartiteGraph));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

void print2DArray(vector<vector<int>> array2D){
    int l = 1;
    for(auto i = array2D.begin(); i != array2D.end(); ++i){
        cout << l++ << " - {";
        for(auto j = i->begin(); j!=i->end(); ++j){
            cout << *j+1;
            if(j==(i->end()-1)) continue;
            cout << ", ";
        }
        cout<< "}" << endl;
    }
    cout<<endl;
}

bool kuhnAlgorithm(int x) {
    if (usedVertices[x])  return false;
    usedVertices[x] = true;
    for (size_t i=0; i<bipartiteGraph[x].size(); ++i) {
        int to = bipartiteGraph[x][i];
        if (match[to] == -1 || kuhnAlgorithm (match[to])) {
            match[to] = x;
            return true;
        }
    }
    return false;
}

vector<vector<int>> generateBipartiteGraph(int n1, int n2) {
    auto resultBipartiteGraph = vector<vector<int>>(n1, vector<int>(n2));
    for(int i=0; i<n1; ++i) {
        vector<int> row;
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<std::mt19937::result_type> dist6(0,n2-1);
        int numberOfEdges = dist6(rng);
        auto secondSetMatchedVertices = vector<int>(n2);
        iota(secondSetMatchedVertices.begin(), secondSetMatchedVertices.end(), 0);
        for(int z=0; z<numberOfEdges; ++z){
            int randElement = *select_randomly(secondSetMatchedVertices.begin(), secondSetMatchedVertices.end());
            row.push_back(randElement);
            secondSetMatchedVertices.erase(remove(secondSetMatchedVertices.begin(), secondSetMatchedVertices.end(), randElement), secondSetMatchedVertices.end());
        }
        resultBipartiteGraph[i] = row;
    }
    return resultBipartiteGraph;
}

int main() {
    n1 = 5; // Number of vertices of the FIRST set of a bipartite graph
    n2 = n1; // // Number of vertices of the SECOND set of a bipartite graph
    bipartiteGraph = generateBipartiteGraph(n1, n2); // Generating "random" bipartite graph with connected edges
    
    
    // Kuhn algorithm
    match.assign(n2, -1);
    for (int x=0; x<n1; ++x) {
        usedVertices.assign(n1, false);
        kuhnAlgorithm(x);
    }
    
    
    print2DArray(bipartiteGraph); // Printing the inital bipartite graph
    
    // Printing the resulting maximum matching
    cout << "Maximum matching: " << endl;
    for (int i=0; i<n2; ++i)
        if (match[i] != -1)
            cout << match[i]+1 << " - " << i+1 << endl;
    cout<<endl;
    
    return 0;
}

