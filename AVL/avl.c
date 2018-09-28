#include "avl.h"

binary_tree *create_empty_binary_tree() {
	return NULL;
}

short is_empty(binary_tree *bt) {
	return bt == NULL;
}

short max(int a, int b) {
	return (a > b) ? a : b;
}

short height(binary_tree *bt) {
	if (bt == NULL) {
		return -1;
	} else {
		return 1 + max(height(bt->left), height(bt->right));
	}
}

short balance_factor(binary_tree *bt) {
	if (bt == NULL) {
		return 0;
	} else if ((bt->left != NULL) && (bt->right != NULL)) {
		return (bt->left->height - bt->right->height);
	} else if ((bt->left != NULL) && (bt->right == NULL)) {
		return (1 + bt->left->height);
	} else {
		return (-bt->right->height - 1);
	}
}

binary_tree* rotate_left(binary_tree *bt)
{
	binary_tree *sb_tree = NULL;
	if (bt != NULL && bt->right != NULL) {
		sb_tree = bt->right;
		bt->right = sb_tree->left;
		sb_tree->left = bt;
	}
	sb_tree->height = height(sb_tree);
	bt->height = height(bt);
	return sb_tree;
}

binary_tree* rotate_right(binary_tree *bt)
{
	binary_tree *sb_tree = NULL;
	if (bt != NULL && bt->left != NULL) {
		sb_tree = bt->left;
		bt->left = sb_tree->right;
		sb_tree->right = bt;
	}
	sb_tree->height = height(sb_tree);
	bt->height = height(bt);
	return sb_tree;
}

binary_tree *add(binary_tree *bt, lli item) {
	if (bt == NULL) {
		return create_binary_tree(item, NULL, NULL);
	} else if (bt->item > item) {
		bt->left = add(bt->left, item);
	} else {
		bt->right = add(bt->right, item);
	}

	bt->height = height(bt);
	binary_tree *child;

	if (balance_factor(bt) == 2 || balance_factor(bt) == -2) {
		if (balance_factor(bt) == 2) {
			child = bt->left;
			if (balance_factor(child) == -1) {
				bt->left = rotate_left(child);
			}
			bt = rotate_right(bt);
		} else if (balance_factor(bt) == -2) {
			child = bt->right;
			if (balance_factor(child) == 1) {
				bt->right = rotate_right(child);
			}
			bt = rotate_left(bt);
		}
	}

	return bt;
}

short is_balanced(binary_tree *bt) {
	short bf = height(bt->left) - height(bt->right);
	return ((-1 <= bf) && (bf <= 1));
}

binary_tree *search(binary_tree *bt, lli item)
{
	binary_tree *new_bt = bt;

	if ((new_bt == NULL) || (new_bt->item == item)) {
		return new_bt;
	} else if (new_bt->item > item) {
		search(new_bt->left, item);
	} else {
		search(new_bt->right, item);
	}
}

binary_tree *search_pai(binary_tree *bt, lli item)
{
	binary_tree *new_bt = bt;

	if (new_bt == NULL || (new_bt->item == item)) {
		
		return new_bt;
	}
	
	if (new_bt->left != NULL && new_bt->left->item == item)
	{
		return new_bt;
	}

	else if (new_bt->right != NULL && new_bt->right->item == item)
	{
		return new_bt;
	}

	else if (new_bt->item > item) {
		search_pai(new_bt->left, item);
	} 

	else {
		search_pai(new_bt->right, item);
	}
}

binary_tree *remove_node(binary_tree *bt, lli item) 
{
	if (bt == NULL)
	{
		printf("Arvore vazia\n");
		return bt;
	}

	binary_tree *root = bt;
	binary_tree *node = search(bt, item);
	binary_tree *bt_pai = search_pai(bt, item);
	
	if (node == NULL)
	{
		printf("Item nao consta na arvore\n");
		return bt;
	}

	else if (bt->item == item && bt->left == NULL && bt->right == NULL) {
		free(bt);
		return NULL;
	}

	else if (bt->item == item) { // eliminar a raiz quando tiver filhos
		binary_tree *pai_aux = bt;
		binary_tree *aux = bt;

		if (aux->left != NULL) {
			aux = aux->left;
			while (aux->right != NULL) {
				pai_aux = aux;
				aux = aux->right;
			} if (aux == bt->left) {
				aux->right = bt->right;
			} else {
				pai_aux->right = aux->left;
				aux->right = bt->right;
				aux->left = bt->left;
			}
		}

		else if (aux->left == NULL) {
			aux = aux->right;
			while (aux->left != NULL) {
				pai_aux = aux;
				aux = aux->left;
			} if (aux == bt->right) {
				aux->left = bt->left;
			} else {
				pai_aux->left = aux->right;
				aux->left = bt->left;
				aux->right = bt->right;
			}
		}

		bt->left = NULL;
		bt->right = NULL;
		free(bt);
		bt = aux;
		return bt;
	}

	else if (node->left == NULL && node->right == NULL) { // eliminar folha
		if ((bt_pai->right != NULL) && (bt_pai->right->item == item)) {
			free(bt_pai->right);
			bt_pai->right = NULL;
		}

		else if ((bt_pai->left != NULL) && (bt_pai->left->item == item)) {
			free(bt_pai->left);
			bt_pai->left = NULL;
		}
	}

	else if (node->left == NULL && node->right != NULL) { // eliminar um node com uma subtree a direita 	
		if (node->item > bt_pai->item) {
			bt_pai->right = node->right;
			node->right = NULL;
			free(node);
		}

		else {
			bt_pai->left = node->right;
			node->right = NULL;
			free(node);
		}
	}

	else if (node->left != NULL && node->right == NULL) { // eliminar um node com uma subtree a esquerda
		if (node->item > bt_pai->item) {
			bt_pai->right = node->left;
			node->left = NULL;
			free(node);
		} else {
			bt_pai->left = node->left;
			node->left = NULL;
			free(node);
		}
	}

	else if (node->left != NULL && node->right != NULL) {// eliminar um node que tem duas subarvores
		binary_tree *aux_pai = node;

		if (node->item < root->item) { // Verifica se o node a ser removido está a esquerda da raiz
			binary_tree *aux = node->right;

			while(aux->left != NULL) { // Busca o node mais a esquerda da subtree a direita
				aux_pai = aux;
				aux = aux->left;
			}

			if(aux_pai != node) {
				aux_pai->left = aux->right;
			}

			if(bt_pai->left == node) {
				bt_pai->left = aux;
			}

			else if(bt_pai->right == node) {
				bt_pai->right = aux;
			}

			aux->left = node->left;

			if(node->right != aux) {
				aux->right = node->right;
			}

			node->left = NULL;
			free(node);
		}

		else if (node->item > root->item)//Verifica se o node a ser removido está a direita da raiz
		{
			binary_tree *aux = node->left;

			while(aux->right != NULL)//Busca o node mais a esquerda da subtree a direita
			{
				aux_pai = aux;
				aux = aux->right;
			}

			if(aux_pai != node)
			{
				aux_pai->right = aux->left;
			}

			if(bt_pai->right == node)
			{	
				bt_pai->right = aux;
			}

			else if(bt_pai->left == node)
			{
				bt_pai->left = aux;
			}

			aux->right = node->right;

			if(node->left != aux)
			{
				aux->left = node->left;
			}

			node->right = NULL;
			free(node);
		}
	}

	binary_tree *child;

	if (balance_factor(bt) == 2 || balance_factor(bt) == -2) {
		if (balance_factor(bt) == 2) {
			child = bt->left;
			if (balance_factor(child) == -1) {
				bt->left = rotate_left(child);
			}
			bt = rotate_right(bt);
		} else if (balance_factor(bt) == -2) {
			child = bt->right;
			if (balance_factor(child) == 1) {
				bt->right = rotate_right(child);
			}
			bt = rotate_left(bt);
		}
	}

	return bt;
}

void print_tree(binary_tree *bt) // (print, visit, visit)
{
	if (!is_empty(bt))
	{
		printf(" ( ");
		printf("%lld ", bt->item);  

		if (bt->left == NULL) {
			printf(" () ");
		} else {
			print_tree(bt->left);
		} if (bt->right == NULL) {
			printf(" () ");
		} else {
			print_tree(bt->right);
		}
		printf(") ");
	}
}

int main() {
	int i;
	binary_tree *bt = create_empty_binary_tree();

	bt = add(bt, 7);
	bt = add(bt, 2);
	bt = add(bt, 1);
	bt = add(bt, 4);

	bt = add(bt, 3);
	bt = add(bt, 3);
	bt = add(bt, 8);
	bt = add(bt, 5);
	bt = add(bt, 6);


	print_tree(bt);
	printf("\n");
	printf("\n");

	bt = remove_node(bt, 4);
	print_tree(bt);
	printf("\n");
	// bt = remove_node(bt, 5);
	// print_tree(bt);
	// printf("\n");
	// bt = remove_node(bt, 3);
	// print_tree(bt);
	// printf("\n");
	// bt = remove_node(bt, 2);
	// print_tree(bt);
	// printf("\n");
	// bt = remove_node(bt, 4);
	// print_tree(bt);
	// printf("\n");
	// bt = remove_node(bt, 3);
	// print_tree(bt);
	// printf("\n");
	// bt = remove_node(bt, 7);
	// print_tree(bt);
	// printf("\n");
	// bt = remove_node(bt, 8);
	// print_tree(bt);
	// printf("\n");
	// bt = remove_node(bt, 9);
	// print_tree(bt);
	// printf("\n");
	// bt = remove_node(bt, 3);
	// print_tree(bt);
	// printf("\n");
	// bt = remove_node(bt, 2);
	// print_tree(bt);
	// printf("\n");
	// bt = remove_node(bt, 4);
	// print_tree(bt);
	// printf("\n");
}