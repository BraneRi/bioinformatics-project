#include <vector>
#include <iostream>
using namespace std;

class De_Bruijn_Node {
    public:
        int len;
        int lb;
        int size;
        int suffix_lb;
        De_Bruijn_Node();
        De_Bruijn_Node(int len, int lb, int size, int suffix_lb);

};
