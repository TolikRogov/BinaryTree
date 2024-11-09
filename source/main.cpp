#include "BinaryTree_dump.hpp"
#include "BinaryTree.hpp"

int main() {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	Data_t array[] = {5, 8, 5, 3, 4, 6, 1, 5, 6, 2, 7};
	size_t array_size = sizeof(array) / sizeof(array[0]);

	INIT_TREE(tree);

	TreePrintType order = IN_ORDER;

	for (size_t i = 0; i < array_size; i++)
		INSERT_IN_TREE(&tree, array[i], order);

	PRINT_TREE(tree.root, order);

	TREE_DTOR(tree.root);

#ifdef HTML_OPEN
	system(OPEN HTML_FILE_);
#endif
	return 0;
}
