#include "BinaryTree.hpp"

BinaryTreeStatusCode TreeDtor(Node_t* node) {

	if (node->left) TreeDtor(node->left);
	if (node->right) TreeDtor(node->right);

	if (node) {
		free(node);
		node = NULL;
	}

	return TREE_NO_ERROR;
}

Node_t* CreateNode(Data_t data) {

	Node_t* node = (Node_t*)calloc(1, sizeof(*node));
	node->data = data;

	return node;
}

BinaryTreeStatusCode InsertInTree(Node_t* cur_root, Node_t* new_node) {

	if (cur_root->data   == UNKNOWN_WHAT && \
		cur_root->left   == NULL && \
		cur_root->right  == NULL && \
		cur_root->parent == NULL) {

		*cur_root = *new_node;
		return TREE_NO_ERROR;
	}

	Node_t** cur_branch = NULL;
	if (new_node->data < cur_root->data)
		cur_branch = &cur_root->left;
	else
		cur_branch = &cur_root->right;

	if (!*cur_branch) {
		*cur_branch = new_node;
		new_node->parent = cur_root;
		return TREE_NO_ERROR;
	}

	InsertInTree(*cur_branch, new_node);

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode TreePrint(Node_t* node, TreePrintType order) {

	if (node == NULL)
		return TREE_NO_ERROR;

#ifdef PRINT_DEBUG
	printf("(");
#endif

#ifndef PRINT_DEBUG
	#define NODE_PRINT " "
#else
	#define NODE_PRINT
#endif

	if (order == PRE_ORDER)
		printf("%d" NODE_PRINT, node->data);

	if (node->left) TreePrint(node->left, order);

	if (order == IN_ORDER)
		printf("%d" NODE_PRINT, node->data);

	if (node->right) TreePrint(node->right, order);

	if (order == POST_ORDER)
		printf("%d" NODE_PRINT, node->data);

#undef NODE_PRINT

#ifdef PRINT_DEBUG
	printf(")");
#endif

	return TREE_NO_ERROR;
}
