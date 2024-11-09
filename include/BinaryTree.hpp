#ifndef BINARY_TREE_INCLUDE
#define BINARY_TREE_INCLUDE

#include <stdlib.h>
#include <dirent.h>
#include "BinaryTree_errors.hpp"

typedef int Data_t;

#define INIT_TREE(tree) Tree tree = { .root = CreateNode(UNKNOWN_WHAT), .info = {.name = #tree, .file_name = __FILE__, .line = __LINE__} }; TREE_CTOR();

#define BINARY_TREE_GRAPH_DUMP(tree, func_name, point) {	 																\
	tree_status = BinaryTreeGraphDump(tree, {.file = __FILE__, .line = __LINE__, .func = func_name, .pointer = point});		\
	TREE_ERROR_CHECK(tree_status);																	 					   \
}

#define PRINT_TREE(root, order) {			 \
	tree_status = TreePrint(root, order);	\
	TREE_ERROR_CHECK(tree_status);			\
	printf("\n");							\
}

#define TREE_HTML_DUMP_START() {				 \
	tree_status = BinaryTreeHtmlDumpStart();	\
	TREE_ERROR_CHECK(tree_status);				\
}

#define TREE_HTML_DUMP_FINISH() {				 \
	tree_status = BinaryTreeHtmlDumpFinish();	\
	TREE_ERROR_CHECK(tree_status);				\
}

#define TREE_CTOR() {						 	 \
	tree_status = TreeCtor();					\
	TREE_ERROR_CHECK(tree_status);				\
}

#define TREE_DTOR(root) {						 \
	TREE_HTML_DUMP_FINISH();					\
	tree_status = TreeDtor(root);				\
	TREE_ERROR_CHECK(tree_status);				\
}

#ifndef PRINT_DEBUG
	#define INSERT_IN_TREE(tree, new_element_data, order) {					 		 \
		Node_t* new_node =  CreateNode(new_element_data);							\
		tree_status = InsertInTree((tree)->root, new_node);							\
		TREE_ERROR_CHECK(tree_status);												\
		BINARY_TREE_GRAPH_DUMP(tree, "INSERT_IN_TREE", new_node);					\
	}
#else
	#define INSERT_IN_TREE(root, new_element_data, order) {					 \
		Node_t* new_node =  CreateNode(new_element_data);					\
		tree_status = InsertInTree(root, new_node);							\
		TREE_ERROR_CHECK(tree_status);										\
		PRINT_TREE(root, order)												\
		BINARY_TREE_GRAPH_DUMP(tree, "INSERT_IN_TREE", new_node);			\
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

struct TreeLogInfo {
	const char* name;
	const char* file_name;
	const size_t line;
};

struct Tree {
	Node_t* root;

	TreeLogInfo info;
};

enum TreeDumpCheck {
	TREE_FIRST_RUN,
	TREE_SECOND_RUN,
	TREE_ALREADY_ON,
};

const Data_t UNKNOWN_WHAT = -666;

BinaryTreeStatusCode TreeCtor();

BinaryTreeStatusCode BinaryTreeHtmlDumpStart();
BinaryTreeStatusCode BinaryTreeHtmlDumpFinish();

BinaryTreeStatusCode TreePrint(Node_t* root, TreePrintType order);
BinaryTreeStatusCode InsertInTree(Node_t* cur_root, Node_t* new_node);
BinaryTreeStatusCode TreeDtor(Node_t* node);

Node_t* CreateNode(Data_t data);

#endif //BINARY_TREE_INCLUDE
