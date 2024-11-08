#include "BinaryTree.hpp"

int main() {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	Data_t array[] = {5, 8, 5, 3, 4, 6, 1, 5, 6, 2, 7};
	size_t array_size = sizeof(array) / sizeof(array[0]);

	INIT_TREE(root);

	TreePrintType order = IN_ORDER;

	for (size_t i = 0; i < array_size; i++)
		INSERT_IN_TREE(root, array[i], order);

	PRINT_TREE(root, order);

	TreeDtor(root);

	return 0;
}
