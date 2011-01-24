#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib_vbtree.h"

/*
TreeNode *buildTree(FILE *in)
{
	TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
	char str[MAX_WORD_SIZE+1];

	fscanf(in, "%s", str);
	if(strcmp(str, "@")==0) return NULL;
	strcpy(p->data.word, str);
	p->left = buildTree(in);
	p->right = buildTree(in);
	return p;
}
*/

void vbtree_pre_order(TreeNode *node)
{
	if(node != NULL)
	{
		vbtree_pre_order(node->left);
		vbtree_pre_order(node->right);
	}
}

void vbtree_in_order(TreeNode *node)
{
	if(node != NULL)
	{
		vbtree_in_order(node->left);
		vbtree_in_order(node->right);
	}
}

void vbtree_post_order(TreeNode *node)
{
	if(node != NULL) {
		vbtree_post_order(node->left);
		vbtree_post_order(node->right);
	}
}

TreeNode *newTreeNode(void *d)
{
	TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
	p->pData = d;
	p->left = p->right = NULL;
	return p;
}

/*
TreeNode *vbtree_find_insert(BinaryTree bt, TreeNode d)
{
	int cmp;
	TreeNode *curr = bt.root;

	if(bt.root == NULL) return newTreeNode(NULL);
	while((cmp = strcmp(d.word, curr->pData.word))!= 0)
	{
		if(cmp < 0)
		{
			if(curr->left == NULL) return curr->left = newTreeNode(d);
			curr = curr->left;
		} else {
			if(curr->right == NULL) return curr->right = newTreeNode(d);
			curr = curr->right;
		}
	}
	return curr;
}
*/
int vbtree_node_count(TreeNode *root)
{
	if(root == NULL) return 0;
	return 1 + vbtree_node_count(root->left) + vbtree_node_count(root->right);
}

int vbtree_leave_count(TreeNode *root)
{
	if(root == NULL) return 0;
	if(root->left == NULL && root->right == NULL) return 1;
	return vbtree_leave_count(root->left) + vbtree_leave_count(root->right);
}

int vbtree_height(TreeNode *root)
{
	int left = 0, right = 0;
	if(root == NULL) return 0;
	left = vbtree_height(root->left);
	right = vbtree_height(root->right);

	if(left > right) return 1 + left;
	else return 1 + right;
}

/*
 * FUNCTION NOT COMPLETED
void deleteNode(TreeNode T)
{
	if(T == NULL) return NULL;
	if(right(T) ++ NULL) return left(T)
*/

int vbtree_node_level(int n)
{
	int level = 0;
	while(n % 2 == 0)
	{
		level++;
		n /= 2;
	}
	return level;
}

void vbtree_insert_best(TreeNode *lastNode[])
{
	static int numNodes = 0;
	int level = vbtree_node_level(numNodes);
	TreeNode *p = newTreeNode(NULL);

	numNodes++;
	if(level > 0) p->left = lastNode[level-1];
	if(lastNode[level+1] != NULL)
		if(lastNode[level+1]->right == NULL)
			lastNode[level+1]->right = p;
	lastNode[level] = p;
}

TreeNode *vbtree_finalize_best(TreeNode *lastNode[])
{
	int m, n = MAX_HEIGHT - 1;
	TreeNode *root = lastNode[n];
	while(n > 0 && lastNode[n] == NULL) n--;
	while(n > 0)
	{
		if(lastNode[n]->right != NULL) n--;
		else {
			TreeNode *tn = lastNode[n]->left;
			m = n - 1;
			while(m >= 0 && tn == lastNode[m])
			{
				tn = tn->right;
				m--;
			}
			if(m >= 0) lastNode[n]->right = lastNode[m];
			n = m;
		}
	}
	return root;
}
