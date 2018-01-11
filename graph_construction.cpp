#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include "models.h"
using namespace std;

vector<int> compute_LCP_from_BWT(string BWT) {
    /*
    n = BWT.size();
    vector<int> LCP = vector<int>();
    LCP[0] = -1;
    LCP[n] = -1;

    queue<tuple<int,int,int>> temp_queue = queue<tuple<int,int,int>>();

    tuple<int,int,int> initial_range = {1, n, 0};
    temp_queue.push(initial_range);

    while(!temp_queue.empty()) {
        tuple<int,int,int> temp_range = temp_queue.pop();
        vector<int> list = vector<int>();

    }

    return LCP;*/

    cout << "uso sam";

    return null;
}

tuple create_bit_vectors(int k, vector<int> BWT, vector<De_Bruijn_Node> G, queue<int> Q) {
    vector<int> LCP = compute_LCP_from_BWT(BWT);
};