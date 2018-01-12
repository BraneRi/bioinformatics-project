using namespace std;
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "sais-master/sais.hh"
#include <algorithm>
#include <string>
#include "graph_construction.h"

string parse_input_fasta_file(string filepath) {
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
}

/**
 * Method uses sais library SAIS (uses SA-iS algorithm)
 * to create suffix array
 * */
const int* generate_SA(string S) {
    const char * S_const_char = S.c_str();
    SAIS* sais = new SAIS(S_const_char);
    const int* SA = sais->sa();
    return SA;
}

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
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Please provide following argument: <FILE.fasta> ";
        return 1;
    }

    string parsed_input = parse_input_fasta_file(argv[1]);
    int n = parsed_input.length();

    char S[n];
    prepare_input_string(parsed_input, n, S);
    const int* SA = generate_SA(S);

    string BWT = generate_BWT(S, SA);

    int LCP[n];
    compute_LCP_from_SA(SA, S, n, LCP);

/*
    list<int*> Br_and_Bl;
    De_Bruijn_Node G[];
    int Q[];
    create_bit_vectors(n, 3, LCP, BWT, G, Q, Br_and_Bl);

    int Br[] = Br_and_Bl[0];
    int Bl[] = Br_and_Bl[1];*/

    return 0;
}