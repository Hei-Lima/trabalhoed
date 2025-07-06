// Lib that implements all of the doubly linked list functions for patient management.

#ifndef _LIST_H
#define _LIST_H

#include "paciente.h"

typedef struct listnode ListNode;
typedef struct list List;

// Create a list and return its pointer.
List* ll_create_list();

// Insert a patient into the list.
void ll_insert_node(List* list, Paciente* paciente);

// Remove a node from the list by id.
void ll_remove_node(List* list, int id);

// Search for a patient by id.
Paciente* ll_search_node(List* list, int id);

// Free all memory allocated for the list.
void ll_destroy_list(List* list);

// Get the size of the list.
int ll_get_size(List* list);

// Check if the list is empty.
int ll_is_empty(List* list);

// Print all patients with that prefix.
void ll_print_by_prefix(List* list, char* prefix, int search_type);

// Print a page of patients from the list.
void ll_print_page(List* list, int start, int end);

#endif