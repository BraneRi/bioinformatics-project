#include "models.h"
using namespace std;
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <tuple>
#include <list>

void compute_LCP_from_SA(const int* SA, string S, int n, int LCP[]);
void create_bit_vectors(int n, int k, const int* LCP, string BWT, map<int, De_Bruijn_Node>& , queue<int>&, int[], int[]);
void compute_C_array(string BWT, int C[]);
void create_compressed_graph(int n, int k, const int* LCP, string BWT, map<int, De_Bruijn_Node>& G, queue<int>& Q);
