#include "BinaryTree_dump.hpp"
#include "Colors"

long AMOUNT_OF_LAST_SYMBOLS = 0;

BinaryTreeStatusCode BinaryTreeHtmlDumpStart() {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	tree_status = BinaryTreeCreateDumpDir();
	TREE_ERROR_CHECK(tree_status);

	FILE* html_file = fopen(HTML_FILE_, "w");
	if (!html_file)
		TREE_ERROR_CHECK(TREE_FILE_OPEN_ERROR);

	tree_status = BinaryTreeCssFile();
	TREE_ERROR_CHECK(tree_status);

#define HTML_PRINTF(...) fprintf(html_file, __VA_ARGS__);

	HTML_PRINTF("<!DOCTYPE HTML PUBLIC>\n");
	HTML_PRINTF("<html lang=\"ru\">\n");

	HTML_PRINTF("\t<head>\n");
	HTML_PRINTF("\t\t<title>Binary Tree Dump</title>\n");
	HTML_PRINTF("\t\t<meta charset=\"utf-8\" />\n");
	HTML_PRINTF("\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"styles.css\" />\n");
	HTML_PRINTF("\t</head>\n");

	HTML_PRINTF("\t<body><tt><pre>\n");
	HTML_PRINTF("\t\t\t\t\t\t\t\t\t\t\t<a class='head'>MEGA DUMP</a><br>\n");

	HTML_PRINTF("\t<div class='dump'>\n");
	HTML_PRINTF("\tColors meanings: \n");
	HTML_PRINTF("\t\t<div class='circle' style='background-color: %.7s; border-color: %.7s;'>left subtree node</div>", color.left_node + 1, color.left_node_border + 1);
	HTML_PRINTF("\t\t<span style='color: %.7s'>&#11153; left subtree edge</span>\n", color.left_edge + 1);
	HTML_PRINTF("\t\t<div class='circle' style='background-color: %.7s; border-color: %.7s;'>right subtree node</div>", color.right_node + 1, color.right_node_border + 1);
	HTML_PRINTF("\t\t<span style='color: %.7s'>&#11153; right subtree edge</span>\n", color.right_edge + 1);
	HTML_PRINTF("\t\t<div class='circle' style='background-color: %.7s; border-color: %.7s;'>root node</div>\n", color.root_node+ 1, color.root_node_border + 1);
	HTML_PRINTF("\t\t<div class='circle' style='background-color: %.7s; border-color: %.7s;'>new node</div>", color.new_node+ 1, color.new_node_border + 1);
	HTML_PRINTF("\t</div>\n\n");

#undef HTML_PRINTF

	if (fclose(html_file))
		TREE_ERROR_CHECK(TREE_FILE_CLOSE_ERROR);

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode BinaryTreeCssFile() {

	FILE* css_file = fopen(CSS_FILE_, "w");
	if (!css_file)
		TREE_ERROR_CHECK(TREE_FILE_OPEN_ERROR);

#define CSS_PRINTF(...) fprintf(css_file, __VA_ARGS__);

	CSS_PRINTF("body {\n"\
			   "\tbackground-color: %.7s;\n"\
			   "}\n", color.html_background + 1);

	CSS_PRINTF("h1 {\n"\
			   "\ttext-align: center;\n"\
			   "}\n");

	CSS_PRINTF("b {\n"\
			   "\ttext-decoration: underline;\n"\
			   "}\n");

	CSS_PRINTF(".circle {\n"\
		"\tdisplay: inline-block;\n"\
		"\tborder-radius: 50%%;\n"\
		"\tborder: 1px solid;\n"\
		"\tpadding: 10px;\n"\
		"}\n");

	CSS_PRINTF(".head {\n"\
			   "\tfont-size: 2em;\n"\
    		   "\tfont-weight: bold;\n"\
			   "}\n");

	CSS_PRINTF(".addr {\n"\
			   "\tcolor: %.7s;\n"\
			   "}\n", color.address + 1);

	CSS_PRINTF(".path {\n"\
			   "\tcolor: %.7s;\n"\
			   "}\n", color.path + 1);

	CSS_PRINTF(".line {\n"\
			   "\tcolor: %.7s;\n"\
			   "}\n", color.line + 1);

	CSS_PRINTF(".name {\n"\
			   "\tcolor: %.7s;\n"\
			   "}\n", color.name + 1);

	CSS_PRINTF(".dump {\n"\
			   "\tbackground-color: %.7s;\n"\
			   "\tborder: 1px solid %.7s;\n"\
			   "\tborder-radius: 20px;\n"\
			   "\tpadding: 25px 0px;\n"\
			   "\tmargin: 20px 0px;\n"\
			   "\twidth: 90%%;"\
			   "\tdisplay: inline-block;\n"\
			   "}\n", color.dump_background + 1, color.dump_border + 1);

	CSS_PRINTF(".num {\n"\
			   "\tcolor: %.7s;\n"\
			   "}\n", color.number + 1);

	CSS_PRINTF(".func {\n"\
			   "\tcolor: %.7s;"\
			   "}\n", color.function + 1);

	CSS_PRINTF(".img {\n"\
			   "\twidth: 90%%;\n"\
			   "\theight: 70%%;\n"\
			   "\tobject-fit: contain;\n"\
			   "}\n");

#undef CSS_PRINTF

	if (fclose(css_file))
		TREE_ERROR_CHECK(TREE_FILE_CLOSE_ERROR);

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode BinaryTreeCreateDumpDir() {

	DIR* dump_dir = opendir(DUMP_DIR_);
	if (dump_dir) {
		if (closedir(dump_dir))
			TREE_ERROR_CHECK(TREE_DIR_CLOSE_ERROR);
		system("rm -rf " DUMP_DIR_);
	}
	system("mkdir " DUMP_DIR_);

	DIR* img_dir = opendir(DUMP_DIR_ IMG_DIR_);
	if (!img_dir)
		system("mkdir " DUMP_DIR_ IMG_DIR_);
	else {
		if (closedir(img_dir))
			TREE_ERROR_CHECK(TREE_DIR_CLOSE_ERROR);
	}

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode BinaryTreeHtmlDumpFinish() {

	FILE* html_file = fopen(HTML_FILE_, "a");
	if (!html_file)
		TREE_ERROR_CHECK(TREE_FILE_OPEN_ERROR);

	AMOUNT_OF_LAST_SYMBOLS = 0;

#define HTML_PRINTF(...) AMOUNT_OF_LAST_SYMBOLS += fprintf(html_file, __VA_ARGS__);

	HTML_PRINTF("\t</pre></tt></body>\n");
	HTML_PRINTF("</html>\n");

#undef HTML_PRINTF

	if (fclose(html_file))
		TREE_ERROR_CHECK(TREE_FILE_CLOSE_ERROR);

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode BinaryTreeBashScript(Tree* tree, DumpLogInfo dump_info) {

	static size_t script_num = 1;
	static struct PrevLogInfo {
		const char* file_name;
		size_t line;
		const char* var_name;
	} prev_info;

	FILE* bash_script = fopen(BASH_FILE_, "w");
	if (!bash_script)
		TREE_ERROR_CHECK(TREE_FILE_OPEN_ERROR);

#define BASH_PRINTF(...) fprintf(bash_script, __VA_ARGS__);

	BASH_PRINTF("#!/bin/bash\n");

	BASH_PRINTF("script_num=%zu;\\\n", script_num);
	BASH_PRINTF("dot " DOT_FILE_ " -Tpng -o " DUMP_DIR_ IMG_FILE_ "$script_num" IMG_EXTENSION ";\n");

#undef BASH_PRINTF

	if (fclose(bash_script))
		TREE_ERROR_CHECK(TREE_FILE_CLOSE_ERROR);

	system("chmod +x " BASH_FILE_ "; ./" BASH_FILE_);

	FILE* html_file = fopen(HTML_FILE_, "r+");
	if (!html_file)
		TREE_ERROR_CHECK(TREE_FILE_OPEN_ERROR);

	fseek(html_file, 0, SEEK_END);

#define HTML_PRINTF(...) fprintf(html_file, __VA_ARGS__);

	if (AMOUNT_OF_LAST_SYMBOLS)
		fseek(html_file, -AMOUNT_OF_LAST_SYMBOLS, SEEK_END);

	if (StrCmp(prev_info.file_name, tree->info.file_name) != 0 || prev_info.line != tree->info.line || StrCmp(prev_info.var_name, tree->info.name) != 0)
		HTML_PRINTF("\t\t\t\t\t\t<b>Binary Tree[%p] born at \"%s\": %zu, name '%s'</b>\n", \
					tree, (prev_info.file_name = tree->info.file_name), (prev_info.line = (size_t)tree->info.line), (prev_info.var_name = tree->info.name));

	HTML_PRINTF("\t<div class='dump'>\n");
	HTML_PRINTF("\tDUMP #%zu: function %s was called from %s: %zu\n", script_num, dump_info.func, dump_info.file, dump_info.line);
	HTML_PRINTF("\t<img src='%s%zu%s' class='img'></div>\n\n", IMG_FILE_, script_num++, IMG_EXTENSION);

#undef HTML_PRINTF

	if (fclose(html_file))
		TREE_ERROR_CHECK(TREE_FILE_CLOSE_ERROR);

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode BinaryTreeGraphDump(Tree* tree, DumpLogInfo dump_info) {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	FILE* dot_file = fopen(DOT_FILE_, "w");
	if (!dot_file)
		TREE_ERROR_CHECK(TREE_FILE_OPEN_ERROR);

#define DOT_PRINTF(...) fprintf(dot_file, __VA_ARGS__);

	DOT_PRINTF("digraph {\n");

	DOT_PRINTF("\tfontname = \"UbuntuMono\";\n");
	DOT_PRINTF("\tbgcolor = %s;\n\n", color.dot_background);

	NodeGraphDump(tree->root, dot_file, dump_info);

	DOT_PRINTF("}\n");

#undef DOT_PRINTF

	if (fclose(dot_file))
		TREE_ERROR_CHECK(TREE_FILE_CLOSE_ERROR);

	tree_status = BinaryTreeBashScript(tree, dump_info);
	TREE_ERROR_CHECK(tree_status);

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode NodeGraphDump(Node_t* cur_root, FILE* dot_file, DumpLogInfo dump_info) {

#define DOT_PRINTF(...) fprintf(dot_file, __VA_ARGS__);

	DOT_PRINTF("\tnode%p [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = %s;"
				"label = \" { %d\\n%p | { <left> Left\\n%d\\n%p | Parent\\n%d\\n%p | <right> Right\\n%d\\n%p } } \";  ];\n",
				cur_root, (cur_root->parent ? color.left_node : color.root_node), (cur_root->parent ? color.left_node_border : color.root_node_border), color.node_font,
				cur_root->data, cur_root,
				(cur_root->left ? cur_root->left->data : UNKNOWN_WHAT), cur_root->left,
				(cur_root->parent ? cur_root->parent->data : UNKNOWN_WHAT), cur_root->parent,
				(cur_root->right ? cur_root->right->data : UNKNOWN_WHAT), cur_root->right);

	if (cur_root->left) {
		DOT_PRINTF("\tnode%p:<left> -> node%p [ style = \"bold\"; color = %s ];\n", cur_root, cur_root->left, color.left_edge);
		NodeGraphDump(cur_root->left, dot_file, dump_info);
	}
	if (cur_root->right) {
		DOT_PRINTF("\tnode%p:<right> -> node%p [ style = \"bold\"; color = %s ];\n", cur_root, cur_root->right, color.right_edge);
		NodeGraphDump(cur_root->right, dot_file, dump_info);
		DOT_PRINTF("\tnode%p [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = %s;"
				"label = \" { %d\\n%p | { <left> Left\\n%d\\n%p | Parent\\n%d\\n%p | <right> Right\\n%d\\n%p } } \";  ];\n",
				cur_root->right, color.right_node, color.right_node_border, color.node_font,
				cur_root->right->data, cur_root->right,
				(cur_root->right->left ? cur_root->right->left->data : UNKNOWN_WHAT), cur_root->right->left,
				(cur_root->right->parent ? cur_root->right->parent->data : UNKNOWN_WHAT), cur_root->right->parent,
				(cur_root->right->right ? cur_root->right->right->data : UNKNOWN_WHAT), cur_root->right->right);
	}

	if (cur_root->right == dump_info.pointer) {
		DOT_PRINTF("\tnode%p [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = %s;"
				"label = \" { %d\\n%p | { <left> Left\\n%d\\n%p | Parent\\n%d\\n%p | <right> Right\\n%d\\n%p } } \";  ];\n",
				cur_root->right, color.new_node, color.new_node_border, color.node_font,
				cur_root->right->data, cur_root->right,
				(cur_root->right->left ? cur_root->right->left->data : UNKNOWN_WHAT), cur_root->right->left,
				(cur_root->right->parent ? cur_root->right->parent->data : UNKNOWN_WHAT), cur_root->right->parent,
				(cur_root->right->right ? cur_root->right->right->data : UNKNOWN_WHAT), cur_root->right->right);
	}
	if (cur_root->left == dump_info.pointer) {
		DOT_PRINTF("\tnode%p [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = %s;"
				"label = \" { %d\\n%p | { <left> Left\\n%d\\n%p | Parent\\n%d\\n%p | <right> Right\\n%d\\n%p } } \";  ];\n",
				cur_root->left, color.new_node, color.new_node_border, color.node_font,
				cur_root->left->data, cur_root->left,
				(cur_root->left->left ? cur_root->left->left->data : UNKNOWN_WHAT), cur_root->left->left,
				(cur_root->left->parent ? cur_root->left->parent->data : UNKNOWN_WHAT), cur_root->left->parent,
				(cur_root->left->right ? cur_root->left->right->data : UNKNOWN_WHAT), cur_root->left->right);
	}

#undef DOT_PRINTF

	return TREE_NO_ERROR;
}
