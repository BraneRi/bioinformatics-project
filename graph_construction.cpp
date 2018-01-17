#include "graph_construction.h"
#include <sdsl/wavelet_trees.hpp>
#include <string>
#include <map>
#include <queue>
#include <iostream>
#include <fstream>
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
void create_bit_vectors(int n, int k, const int* LCP, string BWT, map<int, De_Bruijn_Node>& G, queue<int>& Q, int Br[], int Bl[], int C[]) {
    compute_C_array(BWT, C);

    int lb = 1;
    int kIndex = 0;
    int lastdiff = 0;

    bool open = false;
    int counter = 0;

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

                    G[counter] = De_Bruijn_Node(k, lb, i - lb, lb);
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

int *create_rank_vector(int B_vector[], int n){
     int *rank = (int*)malloc((n+1)*sizeof(int));
     rank[0] = 0;

     for(int i = 1; i <= n; i++){
       rank[i] = B_vector[i - 1] + rank[i - 1];
     }

     return rank;
}

void create_wt(sdsl::wt_blcd<>& wt, int i, int j, char* bwt, int n) {

	std::string tmp(n, 'a');
	for (int k = 1; k <= n + 1; k++) {
		tmp[k-1] = bwt[k];
	}

	sdsl::construct_im(wt, tmp, 1);
}

void printGraph(map<int, De_Bruijn_Node>& G, string output_file) {
    ofstream output;
    output.open(output_file);
    if (!output.is_open()) {
        cerr << "NE mogu otvorit";
    }
    for (auto it = G.begin(); it != G.end(); ++it) {
        output << it->second.len << " ";
        output << it->second.lb << " ";
        output << it->second.size << " ";
        output << it->second.suffix_lb << "\n";
    }
    output << std::endl;
    output.close();
    cout << "Output saved in " << output_file << "\n";
};

/*
void printGraph(map<int, De_Bruijn_Node>& G) {
    for (auto it = G.begin(); it != G.end(); ++it) {
        cout << "  id:  " << it->first;
        cout << "  len: "<< it->second.len;
        cout << "  lb: " << it->second.lb;
        cout << "  size: " << it->second.size;
        cout << "  suff_lb: " << it->second.suffix_lb << "\n";
    }

    cout << "\n";
};
*/

/**
 * Algorithm 2 from paper which finishes generation of De Brujin graph
 * */
void create_compressed_graph(int n, int k, const int* LCP, string BWT, map<int, De_Bruijn_Node>& G, queue<int>& Q, int d) {
    int *Br = new int[n + 1]();
    int *Bl = new int[n + 1]();

    int C[256] = {0};
    create_bit_vectors(n, k, LCP, BWT, G, Q, Br, Bl, C);

    int *Br_rank = create_rank_vector(Br, n);
    int *Bl_rank = create_rank_vector(Bl, n);

    // total number of ones between 4 bits -> Br_rank[4]
    int rightMax = Br_rank[n] / 2;
    int leftMax = Bl_rank[n];
    int id;

    for(int s=0;s<d; s++) {
        id = rightMax + leftMax + s;
        G[id] = De_Bruijn_Node(1, s, 1, s);
        Q.push(id);
        Bl[s] = 0;
    }



    sdsl::wt_blcd<> wt;
    char *bwt = new char[BWT.length() + 1];

    for(int i = 1; i < BWT.length() + 1; i++){
      bwt[i] = BWT[i-1];
    }


	create_wt(wt, 0, 5, bwt, n);


	vector<uint8_t> chars(wt.sigma);
	vector<uint64_t> rank_c_i(wt.sigma);
	vector<uint64_t> rank_c_j(wt.sigma);
    uint64_t size;

    bool extendable;
    int ones;
    int newId;
    int lb, rb;
    int c,i,j;
    while (!Q.empty()) {
        id = Q.front();
        Q.pop();

        lb = G[id].lb;
        rb = lb + G[id].size - 1;
        do {
            extendable = false;
            sdsl::interval_symbols(wt,lb,rb+1,size,chars,rank_c_i,rank_c_j);

            for(int interval=0;interval<size;interval++) {
                c = chars[interval];

                i = C[c - 1] + rank_c_i[interval];
                j = C[c - 1] + rank_c_j[interval] - 1;
                ones = Br_rank[i+1];

                if (ones % 2 == 0 && Br[i] == 0) {
                    if (c != '$' && c != '#') {
                        if (size == 1) {
                            extendable = true;
                            G[id].len++;
                            G[id].lb = i;
                            lb = i;
                            rb = j;
                        } else {
                            G[id].lb = lb;
                            newId = rightMax + Bl_rank[i];
                            G[newId] = De_Bruijn_Node(k, i, j-i+1, i);
                            Q.push(newId);
                        }
                    }
                }
            }
        } while(extendable);


    }

    delete bwt;
    delete Br;
    delete Bl;
    delete Br_rank;
    delete Bl_rank;
}
