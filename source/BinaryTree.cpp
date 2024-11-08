#include "BinaryTree.hpp"

Node_t* CreateNode(Data_t data) {

	Node_t* node = (Node_t*)calloc(1, sizeof(*node));
	if (!node)
		TREE_ERROR_CHECK(TREE_ALLOC_ERROR);

	node->data = data;

	return node;
}

BinaryTreeStatusCode TreePrint(Node_t* node) {

	if (node == NULL)
		return TREE_NO_ERROR;

	printf("(");
	if (node->left) TreePrint(node->left);
	printf("%d", node->data);
	if (node->right) TreePrint(node->right);
	printf(")");

	return TREE_NO_ERROR;
}
