#include "BankTypes.h"

TreeNode *insert_edge(TreeNode*, char*, char*, int);
void modify_edge(TreeNode*, char*, char*, int, int);
void delete_all_edges(TreeNode*, char*, char*);
void delete_edge(TreeNode*, char*, char*, int);
void cycles_find(TreeNode*, TreeNode*);
void find_cycles(TreeNode*, TreeNode*, int);
void traceflow(TreeNode*, TreeNode*,TreeNode*, int);
void receiving_edges(TreeNode*);
TreeNode *search(TreeNode*, char*);
TreeNode *insert(TreeNode*, char*);
TreeNode *del(TreeNode*, TreeNode*);
void print_all_edges(TreeNode*);
void preorder(TreeNode*);
