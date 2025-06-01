// Lib that implements all of the trie-related functions of the program.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"
#include "db.h"

// This defines our alphabet size (ALL ASCII).
#define CHILDSIZE 256

// This struct implements the trie node. Adapted from https://www.youtube.com/watch?v=3CbFFVHQrk4&t.
typedef struct trienode
{
    struct trienode *children[CHILDSIZE];
    int index;
    int is_leaf;

} TrieNode;

// This struct implements the trie, it holds the metadata of the whole trie.
typedef struct trie
{
    TrieNode *root;
} Trie;

// Initialize a trie and return its pointer.
Trie* trie_create() {
    Trie* trie = malloc(sizeof(*trie));
    trie->root = NULL;

    return trie;
}

// Initialize a node and return its pointer.
TrieNode* trie_create_node() {
    TrieNode* new_node = malloc(sizeof *new_node);

    for (int i = 0; i < CHILDSIZE; i++) {
        new_node->children[i] = NULL;
    }

    new_node->is_leaf = 0;
    return new_node;
}

// Insert a node into a trie.
void trie_insert(Trie* trie, char* string, int index) {
    TrieNode* root = trie->root;
    if (root == NULL) {
        trie->root = trie_create_node();
        root = trie->root;
    }

    TrieNode* tmp = root;
    int len = strlen(string);

    for (int i = 0; i < len; i++) {
        unsigned char idx = (unsigned char)string[i];
        if (tmp->children[idx] == NULL) {
            tmp->children[idx] = trie_create_node();
        }
        tmp = tmp->children[idx];
    }

    tmp->index = index;
    tmp->is_leaf = 1;
}

void trie_print_rec(TrieNode* node, char* prefix, int len) {
    char new_prefix[len + 2];
    memcpy(new_prefix, prefix, len);
    new_prefix[len + 1] = 0;

    // Base case
    if (node->is_leaf) {
        printf("%s\n", prefix);
    }
    
    for (int i = 0; i < CHILDSIZE; i++) {
        if (node->children[i] != NULL) {
            new_prefix[len] = i;
            trie_print_rec(node->children[i], new_prefix, len + 1);
        }
    }
}

// Prints the entire trie (no pun intended).
void trie_print(Trie* trie) {
    TrieNode* root = trie->root;
    if (root == NULL) {
        return;
    }
    
    trie_print_rec(root, NULL, 0);
}

// Check if the trie contains a string.
int trie_contains(Trie* trie, char* signed_text) {
    unsigned char *text = (unsigned char*) signed_text;
    int len =  strlen(signed_text);
    
    TrieNode* tmp = trie->root;
    
    for (int i = 0; i < len; i++) {
        if (tmp->children[text[i]] == NULL) {
            return 0;
        }
        tmp = tmp->children[text[i]];
    }
    return tmp->is_leaf;
}

void trie_search_rec(TrieNode* node, char* prefix, int len, BDPaciente* db) {
    char new_prefix[len + 2];
    memcpy(new_prefix, prefix, len);
    new_prefix[len + 1] = 0;

    // Base case
    if (node->is_leaf) {
        db_print_patient(db, (node->index) - 1);
    }
    
    for (int i = 0; i < CHILDSIZE; i++) {
        if (node->children[i] != NULL) {
            new_prefix[len] = i;
            trie_search_rec(node->children[i], new_prefix, len + 1, db);
        }
    }
}

// Print all the nodes of the trie that matches the prefix.
void trie_search(Trie* trie, char* signed_prefix, BDPaciente* db) {
    unsigned char* prefix = (unsigned char*) signed_prefix;
    int len = strlen(signed_prefix);

    TrieNode* tmp = trie->root;
    
    for (int i = 0; i < len; i++) {
        if (tmp->children[prefix[i]] == NULL) {
            printf("A busca não retornou resultados.\n");
            return;
        }
        tmp = tmp->children[prefix[i]];
    }

    trie_search_rec(tmp, NULL, 0, db);
}

void trie_destroy_rec(TrieNode* node) {
    if (node == NULL) {
        return;
    }
    
    for (int i = 0; i < CHILDSIZE; i++) {
        if (node->children[i] != NULL) {
            trie_destroy_rec(node->children[i]);
        }
    }
    
    free(node);
}

// Free the struct and all nodes.
void trie_destroy(Trie* trie) {
    TrieNode* root = trie->root;
    if (root != NULL) {
        trie_destroy_rec(root);
    }
    
    free(trie);
}
