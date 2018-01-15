#include "models.h"

De_Bruijn_Node::De_Bruijn_Node() {
  this->len = 0;
  this->lb = 0;
  this->size = 0;
  this->suffix_lb = 0;
};

De_Bruijn_Node::De_Bruijn_Node(int len, int lb, int size, int suffix_lb) {
    this->len = len;
    this->lb = lb;
    this->size = size;
    this->suffix_lb = suffix_lb;
};
