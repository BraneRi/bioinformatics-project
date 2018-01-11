#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include "models.h"
using namespace std;

vector<int> compute_LCP_from_BWT(string BWT);
tuple<vector<int>, vector<int>> create_bit_vectors(int k, string BWT, vector<De_Bruijn_Node> G, queue<int> Q);
