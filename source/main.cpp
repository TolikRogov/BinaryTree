#include "BinaryTree.hpp"

int main() {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	Node_t node1 = {.data = 20};
	Node_t node2 = {.data = 10};
	Node_t node3 = {.data = 30};
	node1.left = &node2;
	node1.right = &node3;

	tree_status = TreePrint(&node1);
	TREE_ERROR_CHECK(tree_status);
	printf("\n");

	return 0;
}
