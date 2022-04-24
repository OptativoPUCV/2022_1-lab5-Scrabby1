#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap * tree=(TreeMap *)malloc(sizeof(TreeMap));
  tree->lower_than=lower_than;
  tree->root=NULL;
  tree->current=NULL;
  return tree;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode * aux=tree->root;
  TreeNode *nuevo=createTreeNode(key,value);
  int flag=1;
  while(flag==1)
  {
    if(tree->lower_than(key,aux->pair->key)==1)
    {
      if(aux->left==NULL)
      {
        aux->left=nuevo;
        nuevo->parent=aux;
        tree->current=nuevo;
      }
      aux=aux->left;
    }
    else
    {
      if(is_equal(tree,key,aux->pair->key)==0)
      {
        if(aux->right==NULL)
        {
          aux->right=nuevo;
          nuevo->parent=aux;
          tree->current=nuevo;
        }
        aux=aux->right;
      }
      else
      {
        break;
      }
    }
  }

}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
