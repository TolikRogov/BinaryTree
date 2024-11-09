#ifndef BINARY_TREE_DUMP
#define BINARY_TREE_DUMP

#include "BinaryTree.hpp"

#define DUMP_DIR_ 		"dump/"
#define IMG_DIR_		"img/"

#define DOT_FILE_ 		DUMP_DIR_ "graph.dot"
#define IMG_FILE_  		IMG_DIR_  "graph"
#define HTML_FILE_ 		DUMP_DIR_ "tree.html"
#define CSS_FILE_		DUMP_DIR_ "styles.css"
#define BASH_FILE_		DUMP_DIR_ "script.bash"

#define IMG_EXTENSION 	".png"

#ifdef __APPLE__
	#define OPEN	"open "
#else
	#define OPEN	"xdg-open "
#endif

struct DumpLogInfo {
	const char* file;
	const size_t line;
	const char* func;
};

BinaryTreeStatusCode BinaryTreeCssFile();
BinaryTreeStatusCode BinaryTreeCreateDumpDir();
BinaryTreeStatusCode BinaryTreeBashScript(Tree* tree, DumpLogInfo dump_info);
BinaryTreeStatusCode BinaryTreeGraphDump(Tree* tree, DumpLogInfo dump_info);
BinaryTreeStatusCode NodeGraphDump(Node_t* cur_root, FILE* dot_file);

#endif //BINARY_TREE_DUMP
