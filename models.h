#include <vector>
#include <iostream>
using namespace std;

class De_Bruijn_Node {
    public:
        int left_boundary;
        int right_boundary;
        int length;
        bool is_sentinel;
        vector<int> adjacent_node_ids;
        vector<int> positions_where_node_appears_in_genome;
        De_Bruijn_Node();
        De_Bruijn_Node(int left_boundary, int right_boundary, int length, bool is_sentinel);
        
};