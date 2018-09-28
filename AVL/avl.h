#ifndef avl_h
#define avl_h

#include "../header.h"
#include "../binary_tree/binary_tree.h"
/*
 * @return: o valor de retorno é uma raiz de árvore alocada
 */
binary_tree *create_empty_binary_tree();

/*
 * cria uma arvore binaria e retorna a raiz da arvore
 */

binary_tree *create_binary_tree(lli item, binary_tree *left, binary_tree *right);
binary_tree *rotate_left(binary_tree *bt);
binary_tree *rotate_right(binary_tree *bt);
binary_tree *add(binary_tree *bt, lli item);
binary_tree *search(binary_tree *bt, lli item);
binary_tree *search_pai(binary_tree *bt, lli item);
binary_tree *remove_node(binary_tree *bt, lli item);
short is_empty(binary_tree *bt);
short height(binary_tree *bt);
short balance_factor(binary_tree *bt);
short is_balanced(binary_tree *bt);
void print_tree(binary_tree *bt);

#endif