#include "graph_construction.h"

/**
 * Kasai et al. algotithm for creating suffix longest common prefix array from
 * suffix array
 * */
void compute_LCP_from_SA(const int* SA, string S, int n, int LCP[]) {
    int rank[n];

    for(int i=0;i<n;i++) {
        rank[SA[i]] = i;
    }

    LCP[0] = -1;
    LCP[n] = -1;
    int h = 0;
    int k;
    for(int i=0;i<n;i++) {
        if (rank[i] != 0) {
            k = SA[rank[i] - 1];

            if (S[i + h] != '1') {
                while(S[i + h] == S[k + h]) {
                    h++;
                }
            }

            LCP[rank[i]] = h;

            if (h > 0) {
                h--;
            }
        }
    }
};

/**
 * Algorithm 1 from paper which creates two bit vectors Br and Bl
 * */
void create_bit_vectors(int n, int k, const int* LCP, string BWT, De_Bruijn_Node G[], int Q[], list<int[]> Br_and_Bl) {
    int C[n];
    // generate C

    int Br[n] = {};
    int Bl[n] = {};

    int lb = 1;
    int kIndex = 0;
    int lastdiff = 0;
    bool open = false;
    int counter = 1;

    for(int i=2;i<=n;i++) {
        C[BWT[i - 1]]++;
        if (LCP[i] >= k) {
            open = true;
            if (LCP[i] == k) {
                kIndex = i;
            }
        } else {
            if (open) {
                if (kIndex > lb) {
                    Br[lb] = 1;
                    Br[i-1] = 1;

                    // TODO: kako se točno stvara jedan čvor i koje argumente gdje prima??
                    De_Bruijn_Node newNode = De_Bruijn_Node(k, lb, i - lb, true);
                    G[counter] = newNode;
                }
            }
        }
    }
};