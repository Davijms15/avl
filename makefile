AVL = AVL/avl.c AVL/avl.h
BT = binary_tree/binary_tree.c binary_tree/binary_tree.h

compile_avl:
	gcc $(AVL) $(BT) -o avl -lm

clear_avl:
	rm avl