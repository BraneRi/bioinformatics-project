#include "models.h"

De_Bruijn_Node::De_Bruijn_Node() {
    this->left_boundary = 0;
    this->right_boundary = 0;
    this->length = 0;
    this->is_sentinel = false;
    this->adjacent_node_ids = vector<int>();
    this->positions_where_node_appears_in_genome = vector<int>();
};

De_Bruijn_Node::De_Bruijn_Node(int left_boundary, int right_boundary, int length, bool is_sentinel) {
    this->left_boundary = left_boundary;
    this->right_boundary = right_boundary;
    this->length = length;
    this->is_sentinel = is_sentinel;
    this->adjacent_node_ids = vector<int>();
    this->positions_where_node_appears_in_genome = vector<int>();
};

/*
int main () {
  De_Bruijn_Node node = De_Bruijn_Node(2,3,5,true);
  cout << node.left_boundary << "\n";
  return 0;
}*/