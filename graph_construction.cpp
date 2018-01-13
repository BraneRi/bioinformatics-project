#include "graph_construction.h"
#include <string>
#include <map>
#include <queue>
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
void create_bit_vectors(int n, int k, const int* LCP, string BWT, map<int, De_Bruijn_Node>& G, queue<int>& Q, int Br[], int Bl[]) {
    int C[256] = {0};
    compute_C_array(BWT, C);

    int lb = 0;
    int kIndex = 0;
    int lastdiff = 0;

    bool open = false;
    int counter = 1;

    char c;

    for(int i=1; i<=n; i++) {
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
                    Q.push(counter);

                    counter++;
                }

                if (lastdiff > lb) {
                    for(int j=lb;j<=i-1;j++) {
                        c = BWT[j];
                        if (c != '#' && c != '$') {
                            Bl[C[c] - 1] = 1;
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
    for(int i=0; i<=n ;i++) {
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
};

/**
 * Algorithm 2 from paper which finishes generation of De Brujin graph
 * */
void create_compressed_graph(int n, int k, const int* LCP, string BWT, map<int, De_Bruijn_Node>& G, queue<int>& Q, int Br[], int Bl[]) {
    int Br[n] = {0};
    int Bl[n] = {0};
    create_bit_vectors(n, 3, LCP, BWT, G, Q, Br, Bl);

    int rightMax = rank1(Br, n) / 2;
    int leftMax = rank1(Bl, n);

    int id;
    int lb, rb;
    list list;
    for(int s=1;s<=d; s++) {
        id = rightMax + leftMax + s;
        G[id] = De_Bruijn_Node(1, s, 1, s);
        Q.push(id);
        Bl[s] = 0;
    }

    bool extendable;
    int ones;
    int newId;
    while (!Q.empty()) {
        // pop je void ??
        id = Q.pop();
        do {
            extendable = false;
            lb = G[i].size - 1;
            rb = lb + G[id].size -1;
            list = getIntervals(lb,rb);

            for(int i=0;i<list.size();i++) {
                c_i_j_list_element = list[i];
                ones = rank1(Br, i);
                if (ones % 2 == 0 && Br[i] = 0) {
                    if (c_i_j_list_element != '$' && c_i_j_list_element != '#') {
                        if (list.size() == 1) {
                            extendable = true;
                            G[id].length++;
                            G[id].left_boundary = i;
                        } else {
                            newId = rightMax;
                            G[newId] = De_Bruijn_Node(k, i, j-i+1, i) + rank1(Bl, i-1) + 1;
                            Q.push(newId);
                        }
                    }
                }
            }
        } while(!extendable);
    }
}
