#include "BinaryTree_errors.hpp"

const char* BinaryTreeErrorsMessenger(BinaryTreeStatusCode status) {
	switch(status) {
		case TREE_NO_ERROR:										return "TREE ERROR - NO ERROR";
		case TREE_ALLOC_ERROR:									return "TREE ERROR - MEMORY ALLOCATION ERROR";
		case TREE_INVALID_TYPE:									return "TREE ERROR - INVALID TYPE OF INPUT ELEMENT";

		case TREE_FILE_OPEN_ERROR:								return "TREE ERROR - FILE WAS NOT OPENED";
		case TREE_FILE_CLOSE_ERROR:								return "TREE ERROR - FILE WAS NOT CLOSED";
		case TREE_DIR_CLOSE_ERROR:								return "TREE ERROR - DIRECTORY WAS NOT CLOSED";

		default: 												return "UNDEFINED ERROR";
	}
}

int StrCmp(const char* str1, const char* str2) {

	if (!str1 || !str2)
		return -1;

	size_t i = 0;
	for (; *(str1 + i) != '\0' && *(str2 + i) != '\0'; i++) {
		if (*(str1 + i) != *(str2 + i))
			break;
	}
	return (*(str1 + i) - *(str2 + i));
}
