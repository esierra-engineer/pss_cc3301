//
// Created by Erick on 2024-09-14.
//
#include <stdio.h>
#include <stdlib.h>
#include "desbalancear.h"
#define COUNT 10

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(Nodo* root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->der, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->id);

    // Process left child
    print2DUtil(root->izq, space);
}

// Wrapper over print2DUtil()
void treeprint(Nodo* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}