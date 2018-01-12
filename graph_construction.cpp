#include "graph_construction.h"
#include<string>
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

void compute_C_array(string BWT, int C[]){

    int K[256] = {0}; // K[0] = $, K[1] = #, K[2] = A, K[3] = C, K[4] = G, K[5] = T


    for(int i = 0, size = BWT.length(); i < size; i++){
      if(BWT[i] == '$'){
        K[0]++;
      }else if(BWT[i] == '#'){
        K[1]++;
      }else{
        K[BWT[i]]++;
      }
  }

  for(int i = 0; i < 256; i++){
      C[i + 1] = C[i] + K[i];
    }

};


/**
 * Algorithm 1 from paper which creates two bit vectors Br and Bl
 * */
<<<<<<< HEAD
void create_bit_vectors(int n, int k, const int* LCP, string BWT, De_Bruijn_Node G[], int Q[], list<int*> Br_and_Bl) {
    int C[n];
    // generate C

=======
void create_bit_vectors(int n, int k, const int* LCP, string BWT, De_Bruijn_Node G[], int Q[], list<int[]> Br_and_Bl) {
    int C[256] = {0};
    compute_C_array(BWT, C);
    
>>>>>>> 55a131419f794382e5ed8e8e5a9b44aa6f039a62
    int Br[n] = {};
    int Bl[n] = {};

    int lb = 1;
    int kIndex = 0;
    int lastdiff = 0;
    bool open = false;
    int counter = 1;

    int counter_Q = 0;
    char c;

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

                    De_Bruijn_Node newNode = De_Bruijn_Node(k, lb, i - lb, false);
                    G[counter] = newNode;
                    Q[counter_Q] = counter;
                    counter_Q++;
                    counter++;
                }

                if (lastdiff > lb) {
                    for(int j=lb;j<i-1;j++) {
                        c = BWT[j];
                        if (c != '#' && c != '$') {
                            Bl[C[c]] = 1;
                        }
                    }
                }

                open = false;
            }
            lb = i;
        }

        if (BWT[i] != BWT[i-1]) {
            lastdiff = i;
        }
    }

    open = false;
    for(int i=1;i<n+1;i++) {
        if (open) {
            Bl[i] = 0;
            if (Br[i] == 1) {
                open = false;
            }
        } else if (Br[i] == 1) {
            Bl[i] = 0;
            open = true;
        }
    }
  
    Br_and_Bl.push_front(Br);
    Br_and_Bl.push_back(Bl);
};