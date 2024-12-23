#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    char* data;        
    struct node* prev;
    struct node* yes;    
    struct node* no;       
} node_t;


node_t* create_node(const char* data) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (!new_node) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    new_node->data = strdup(data);
    new_node->prev = NULL;
    new_node->yes = NULL;
    new_node->no = NULL;
    return new_node;
}

void print_tree(const node_t* node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    printf("%s\n", node->data);

    print_tree(node->yes, depth + 1);
    print_tree(node->no, depth + 1);
}

void free_tree(node_t* node) {
    if (!node) return;

    free_tree(node->yes);
    free_tree(node->no);
    free(node->data);
    free(node);
}

int add_new_node(node_t* root, const char* data, const char* dest, bool yes) {
    if (!root || !data || !dest) 
        return -1;

    if (strcmp(root->data, dest) == 0) {
        printf("YES!");
        node_t* new_node = create_node(data);

        if (!new_node)
            return -1;

        if (yes) {
            root->yes = new_node;
        } else {
            root->no = new_node;
        }
        return 0;
    }

    add_new_node(root->yes, data, dest, yes);
    add_new_node(root->no, data, dest, yes);
    return 0;
}

int main(void) {

    return 0;
}
