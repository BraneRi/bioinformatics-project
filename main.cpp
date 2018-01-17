using namespace std;
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "sais-master/sais.hh"
#include <algorithm>
#include <string>
#include <map>
#include <queue>
#include "graph_construction.h"


string parse_input_fasta_file(string filepath, int *d) {
    ifstream infile(filepath.c_str());

    if (!infile.good()) {
        cerr << "<INPUT>.fasta file does not exist at:" + filepath << endl;
        exit(1);
    }

    string line;
    string S = "";
    while (getline(infile, line)) {
        if (line[0] == '>') {
            S += "#";
            *d += 1;
        } else {
            S += line;
        }
    }

    // remove first "#"
    if (S[0] == '#') {
        S = S.substr(1);
    }
    // add "$" in the end
    S += "$";

    return S;
};


/**
 * This change is made because 0 and 1 are
 * positioned earlier in alphabet
 * */
void prepare_input_string(string parsed_input, int n, char S[]) {
    size_t length = parsed_input.copy(S, n, 0);
    S[length] = '\0';
    for (int i=0;i<n;i++) {
        if (S[i] == '$') {
            S[i] = '0';
        }

        if (S[i] == '#') {
            S[i] = '1';
        }
    }
};

/**
 * Method uses sais library SAIS (uses SA-iS algorithm)
 * to create suffix array
 * */
SAIS* generate_SA(string S) {
    const char * S_const_char = S.c_str();
    SAIS* sais = new SAIS(S_const_char);
    return sais;
};

/**
 * Method uses suffix array to create BWT by
 * formula BWT[i] = S[SA[i] - 1]
 */
string generate_BWT(string S, const int* SA) {
    string BWT = "";
    for(int i=0; i < S.length(); i++) {
        if (SA[i] == 0) {
            BWT += "$";
     } else if(S[SA[i] - 1] == '1') {
            BWT += "#";
        } else {
            BWT += S[SA[i] - 1];
        }
    }

    return BWT;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Please provide following argument: <FILE.fasta> ";
        return 1;
    }

    // d is number of sequences separated by sign '#'
    int d = 0;
    string filepath = argv[1];
    string parsed_input = parse_input_fasta_file(filepath, &d);

    int n = parsed_input.length();
    char S[n];
    prepare_input_string(parsed_input, n, S);
    SAIS* sais = generate_SA(S);
    const int* SA = sais->sa();

    string BWT = generate_BWT(S, SA);

    int LCP[n];
    compute_LCP_from_SA(SA, S, n, LCP);

    map<int, De_Bruijn_Node> G;
    queue<int> Q;

    create_compressed_graph(n, 3, LCP, BWT, G, Q, d);
	delete sais;

    string output_file = filepath + ".out";
    printGraph(G, output_file);
    return 0;
}
