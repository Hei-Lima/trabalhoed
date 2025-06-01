// Lib that implements all of the trie-related functions of the program.
#ifndef _TRIE_H
#define _TRIE_H

#include "db.h"

// This struct implements the trie, it holds the metadata of the whole trie, Adapted from https://www.youtube.com/watch?v=3CbFFVHQrk4&t.
typedef struct trie Trie;

// Initialize a trie and return its pointer.
Trie* trie_create();
// Insert a node into a trie.
void trie_insert(Trie* trie, char* string, int index);
// Prints the entire trie (no pun intended).
void trie_print(Trie* trie);
// Check if the trie contains a string.
int trie_contains(Trie* trie, char* signed_text);
// Print all node indexes of the trie that matches the prefix.
void trie_search(Trie* trie, char* signed_prefix, BDPaciente* db);
// Free the struct and all nodes.
void trie_destroy(Trie* trie);

#endif