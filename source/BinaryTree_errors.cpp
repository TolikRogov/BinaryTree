#include "BinaryTree_errors.hpp"

const char* BinaryTreeErrorsMessenger(BinaryTreeStatusCode status) {
	switch(status) {
		case TREE_NO_ERROR:										return "TREE ERROR - NO ERROR";
		case TREE_ALLOC_ERROR:									return "TREE ERROR - MEMORY ALLOCATION ERROR";
		case TREE_INVALID_TYPE:									return "TREE ERROR - INVALID TYPE OF INPUT ELEMENT";

		default: 												return "UNDEFINED ERROR";
	}
}
