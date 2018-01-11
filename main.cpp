using namespace std;
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>

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
    S = S.substr(1);
    // add "$" in the end
    S += "$";

    return S;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Please provide following argument: <FILE.fasta> ";
        return 1;
    }

    string S = parse_input_fasta_file(argv[1]);

    cout << S << "\n";
    return 0;
}