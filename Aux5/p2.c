//
// Created by erick on 9/6/24.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct abbTree{
    char* val;
    struct abbTree *left, *right;
} Tree;

// Inicializa la estructura
Tree *initTree(char *rootValue){
  Tree *root = malloc(sizeof(Tree));
  root->val = rootValue;
  root->left = NULL;
  root->right = NULL;
  return root;
}

// Inserta un valor, retorna root. Debe agregar valores aunque esten duplicados, debe pedir memoria para cada nuevo nodo que
Tree* insertValue(Tree *root, char* value){
  if(root == NULL){
    return initTree(value);
  }
  else {
    insertValue(root->right, value);
  }

  int cmp = strcmp(root->val, value);
    if(cmp <= 0){
      insertValue(root->right, value);
    }
    else {
      insertValue(root->left, value);
    }
    return root;
}

// Imprime los valores guardados en el arbol en orden creciente (recorrer en in orden, primero rama izquierda)
void printTree(Tree *root) {
  if (root == NULL) return;
  printTree(root -> left);
  printf("%s ", root->val);
  printTree(root->right);
}

// Retorna el valor maximo
char* maxValue(Tree *root) {
  if (root == NULL) return NULL;
  while (root->right) {
    root = root -> right;
  }
  return root->val;
}

// Retorn el valor minimo
char* minValue(Tree *root);

// Busca un valor, si lo encuentra lo retorna,de lo contrario retorna NULL
char* find(Tree *root, char* value);