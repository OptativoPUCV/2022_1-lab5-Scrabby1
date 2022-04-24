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
  TreeNode *aux=x;
  int flag=1;
  while(flag==1)
  {
    if(aux->left==NULL)
    {
      return aux;
    }
    aux=aux->left;
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(node->left==NULL && node->right==NULL)
  {
    if(node->parent->left==node)
    {
      node->parent->left=NULL;
    }
    else
    {
      node->parent->right=NULL;
    }
    free(node);
  }
  else
  {
    if(node->left==NULL && node->right!=NULL)
    {
      if(node->parent->left==node)
      {
        node->parent->left=node->right;
        node->right->parent=node->parent;
      }
      else
      {
        node->parent->right=node->right;
        node->right->parent=node->parent;
      }
      node->right->parent=node->parent;
      free(node);
    }
    else
    {
      if(node->left!=NULL && node->right==NULL)
      {
        if(node->parent->left==node)
        {
          node->parent->left=node->left;
          node->left->parent=node->parent;
        }
        else
        {
          node->parent->right=node->left;
          node->left->parent=node->parent;
        }
        free(node);
      }
      else
      {
        TreeNode *minimo=minimum(node->right);
        node->pair->key=minimo->pair->key;
        node->pair->value=minimo->pair->value;
        removeNode(tree,minimo);
      }
    }
  }
  
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  TreeNode * aux=tree->root;
  int flag=1;
  while(flag==1)
  {
    if(tree->lower_than(key,aux->pair->key)==1)
    {
      aux=aux->left;
    }
    else
    {
      if(is_equal(tree,key,aux->pair->key)==0)
      {
        aux=aux->right;
      }
      else
      {
        tree->current=aux;
        return aux->pair;
      }
    }
    if(aux==NULL)
    {
      return NULL;
    }
      
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
  Pair* resultado=searchTreeMap(tree,key);
  if(resultado!=NULL)
  {
    return resultado;
  }
  else
  {
    TreeNode* ubNode=tree->root;
    TreeNode* auxNode=tree->root;
    while(ubNode!=NULL)
    {
      if(tree->lower_than(key,ubNode->pair->key)==1)
      {
        auxNode=ubNode;
        ubNode=ubNode->left;
      }
      else
      {
        if(tree->lower_than(ubNode->pair->key,key)==1)
        {
          auxNode=ubNode;
          ubNode=ubNode->right;
          if(tree->lower_than(ubNode->pair->key,auxNode->pair->key)==1 && tree->lower_than(key,ubNode->pair->key)==1)
          {
            auxNode=ubNode;
          }
        }
      }
    }
    ubNode=auxNode;
    return ubNode->pair;
  }
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode*primero=minimum(tree->root);
  return primero->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  TreeNode *actual=tree->current;
  if(actual->right!=NULL)
  {
    if(actual->right->left==NULL)
    {
      actual=actual->right;
      tree->current=actual;
      return actual->pair;
    }
    else
    {
      TreeNode *next=minimum(actual->right);
      tree->current=next;
      return next->pair;
    }
  }
  else
  {
    while(tree->lower_than(actual->pair->key,tree->current->pair->key)==1 || is_equal(tree,tree->current->pair->key,actual->pair->key)==1)
      {
        if(actual->parent!=NULL)
        {
          actual=actual->parent;
        }
        else
        {
          return NULL;
        }
      }
    tree->current=actual;
    return actual->pair;

  }
  return NULL;
}
