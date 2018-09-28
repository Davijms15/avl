#ifndef ubt_h
#define ubt_h

#include "../header.h"
#include "../node/node.h"

NODE *create_tree(lli value, NODE *left, NODE *right);
int search(NODE *root);
int remove(NODE *root);
void print_tree(NODE *root);
NODE *insert(NODE *root, int item);
int is_empty(NODE *root);

#endif