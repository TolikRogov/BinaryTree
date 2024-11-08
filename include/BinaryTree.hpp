#ifndef BINARY_TREE_INCLUDE
#define BINARY_TREE_INCLUDE

#include <stdio.h>
#include "BinaryTree_errors.hpp"

typedef int Data_t;

struct Node_t {
	Data_t data;
	Node_t* left;
	Node_t* right;
	Node_t* parent;
};

BinaryTreeStatusCode TreePrint(Node_t* node);

#endif //BINARY_TREE_INCLUDE
