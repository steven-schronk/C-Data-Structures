#ifndef LIB_VBTREE_H_
#define LIB_VBTREE_H_

#define MAX_HEIGHT 20

typedef struct TreeNode {
	void *pData;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

typedef struct {
	TreeNode *root;
} BinaryTree;


TreeNode newNode(int n);


TreeNode *newTreeNode(void *d);


TreeNode *buildTree(FILE * in);


void vbtree_pre_order(TreeNode *node);


void vbtree_in_order(TreeNode *node);


void vbtree_post_order(TreeNode *node);


TreeNode *vbtree_find_insert(BinaryTree bt, TreeNode d);


int vbtree_node_count(TreeNode *root);


int vbtree_leave_count(TreeNode *root);


int vbtree_height(TreeNode *root);


int vbtree_node_level(int n);


void vbtree_insert_best(TreeNode *lastNode[]);


TreeNode *vbtree_finalize_best(TreeNode *lastNode[]);

#endif /* LIB_VBTREE_H_ */
