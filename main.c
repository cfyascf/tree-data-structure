#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct leaf {
    int data;
    struct leaf *left;
    struct leaf *right;
    int bf;
} leaf;

typedef struct tree {
    struct leaf *root;
} tree;

tree* get_tree() {
    tree *t = malloc(sizeof(tree));
    t->root = NULL;

    return t;
}

leaf* get_leaf(int data) {
    leaf *l = malloc(sizeof(leaf));
    l->data = data;
    l->left = NULL;
    l->right = NULL;
    l->bf = 0;

    return l;
}

int get_bf(leaf *l) {
    if(l == NULL) {
        printf("Error: could not get leaf's height because leaf is NULL.");
        return -1;
    }

    return get_bf(l->left) - get_bf(l->right);
}

void recalculate_bf(tree *t, leaf *l) {
    leaf *aux = t->root;
    while(aux != l) {
        if(l->data > aux->data) {
            aux->bf = get_bf(aux);
            aux = aux->right;
        } 
        else {
            aux->bf = get_bf(aux);
            aux = aux->left;
        }
    }
}

void insert(tree *t, leaf *l) {
    if(t == NULL || l == NULL) {
        printf("Error: failed to insert because tree or leaf is NULL.");
        return;
    }

    if(t->root == NULL) {
        t->root = l;
        l->bf = 0;
        return;
    }

    leaf *aux = t->root;
    while(1) {
        if(l->data > aux->data) {
            if(aux->right == NULL) {
                aux->right = l;
                break;
            }

            aux = aux->right;
        } 
        else {
            if(aux->left == NULL) {
                aux->left = l;
                break;
            }

            aux = aux->left;
        }
    }

    recalculate_bf(t, l);
}

void main(char args[]) {
    srand(time(NULL));   

    tree *t = get_tree();

    for(int i = 0; i < 20; i++) {
        int r = rand() % 100 + 1; 
        leaf *l = get_leaf(r);
        insert(t, l);
    }

    printf("t->root = %d\n", t->root->data);
}