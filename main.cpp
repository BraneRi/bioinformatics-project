using namespace std;
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "sais-master/sais.hh"
#include <algorithm>
#include <string>

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
 * Method uses sais library SAIS (uses SA-iS algorithm)
 * to create suffix array which is used to create BWT by 
 * formula BWT[i] = S[SA[i] - 1]
 */
string generate_BWT(string S) {
    replace( S.begin(), S.end(), '$', '0');
    replace( S.begin(), S.end(), '#', '1'); 

    const char * S_const_char = S.c_str();

    SAIS sais = SAIS(S_const_char);
    const int* SA = sais.sa();

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

    string S = parse_input_fasta_file(argv[1]);
    cout << "Parsed input:\n" << S << "\n\n";

    string BWT = generate_BWT(S);
    cout << "BWT: \n" << BWT << "\n";
    return 0;
}