#ifndef BINARY_TREE_INCLUDE
#define BINARY_TREE_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree_errors.hpp"

typedef int Data_t;

#define INIT_TREE(root) Node_t* root = CreateNode(-666);

#define PRINT_TREE(root, order) {			 \
	tree_status = TreePrint(root, order);	\
	TREE_ERROR_CHECK(tree_status);			\
	printf("\n");							\
}

#ifndef PRINT_DEBUG
	#define INSERT_IN_TREE(root, new_element_data, order) {					 \
		tree_status = InsertInTree(root, CreateNode(new_element_data));		\
		TREE_ERROR_CHECK(tree_status);										\
	}
#else
	#define INSERT_IN_TREE(root, new_element_data, order) {					 \
		tree_status = InsertInTree(root, CreateNode(new_element_data));		\
		TREE_ERROR_CHECK(tree_status);										\
		PRINT_TREE(root, order)												\
	}
#endif

enum TreePrintType {
	PRE_ORDER,
	POST_ORDER,
	IN_ORDER,
};

struct Node_t {
	Data_t data;
	Node_t* left;
	Node_t* right;
	Node_t* parent;
};

const Data_t UNKNOWN_WHAT = -666;

BinaryTreeStatusCode TreePrint(Node_t* root, TreePrintType order);
BinaryTreeStatusCode InsertInTree(Node_t* cur_root, Node_t* new_node);
BinaryTreeStatusCode TreeDtor(Node_t* node);

Node_t* CreateNode(Data_t data);

#endif //BINARY_TREE_INCLUDE
