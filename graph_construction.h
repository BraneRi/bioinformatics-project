#include "models.h"
using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <list>

void compute_LCP_from_SA(const int* SA, string S, int n, int LCP[]);
void create_bit_vectors(int n, int k, const int* LCP, string BWT, De_Bruijn_Node G[], int Q[], list<int[]> Br_and_Bl);