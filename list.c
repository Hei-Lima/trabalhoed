#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "paciente.h"


typedef struct listnode
{
	int id; 
	
	// Every node store its patient.
	Paciente* paciente;
	
// Two pointers for the doubly linked list.
    struct listnode* next;
    struct listnode* prev; 
    
} ListNode;

typedef struct list
{
	// First element of the list.
	ListNode* head;

	// Last element of the list.
	ListNode* tail;
} List;

// Create a list and return its pointer.
List* ll_create_list() {
    List* list = (List*)malloc(sizeof(List));
    
	// Initialize all list fields to avoid unexpected behavior.
    list->head = NULL;
    list->tail = NULL;
    
    return list;
}

// Check if the list is empty.
int ll_is_empty(List* list){
	if (list->tail == NULL) {
		return 1;
	}

	return 0;

}

// Get the size of the list.
int ll_get_size(List* list){
    int size = 0;

    if (ll_is_empty(list)) {
        return size;
    }

    ListNode* node = list->head;

    while (node != NULL) {
        size++;
        node = node->next;
    }

    return size;
}

Paciente* ll_search_node(List* list, int id) {
    ListNode* node = list->head;
    
    while (node != NULL) {
        if (node->id == id) {
            return node->paciente;
        }
        node = node->next;
    }
    
    return NULL;
}

ListNode* ll_create_node() {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    
    node->next = NULL;
    node->prev = NULL;
    node->paciente = NULL;
    node->id = 0;

    return node;
}

void ll_insert_node(List* list, Paciente* paciente) {
    ListNode* node = ll_create_node();

    node->id = pc_get_id(paciente);
    node->paciente = paciente;
    node->next = NULL;
    node->prev = list->tail;

    // If the list is empty, then the ListNode will be the head of the list.
    if (ll_is_empty(list)) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    // The node will be the tail of the list.
    list->tail = node;
}

void ll_destroy_node(ListNode* node) {
    pc_destroy_paciente(node->paciente);
    free(node);
}

void ll_destroy_list(List* list) {
    ll_destroy_list_rec(list->head);
    free(list);
}

void ll_destroy_list_rec(ListNode* node) {
    // Base case
    if (node == NULL) {
        return;
    }

    // Recursive case
    ListNode* next = node->next;
    ll_destroy_node(node);
    ll_destroy_list_rec(next);
}

void ll_print_by_prefix(List* list, char* prefix, int search_type) {
    if (list == NULL || prefix == NULL) {
        return;
    }
    
    ll_print_by_prefix_rec(list->head, prefix, search_type);
}

void ll_print_by_prefix_rec(ListNode* node, char* prefix, int search_type) {
    // Base case
    if (node == NULL) {
        return;
    }
    
    int match = 0;
    
    if (search_type == 1) {
        // Search by name (case insensitive)
        char* nome = pc_get_nome(node->paciente);
        match = (strncasecmp(nome, prefix, strlen(prefix)) == 0);
    } else if (search_type == 2) {
        // Search by CPF
        char* cpf = pc_get_cpf(node->paciente);
        match = (strncmp(cpf, prefix, strlen(prefix)) == 0);
    }
    
    if (match) {
        pc_print_paciente(node->paciente);
    }
    
    // Recursive case
    ll_print_by_prefix_rec(node->next, prefix, search_type);
}

void ll_print_page(List* list, int start, int end) {
    int current = 0;
    ListNode* node = list->head;
    
    while (node != NULL && current < end) {
        if (current >= start) {
            pc_print_paciente(node->paciente);
        }
        node = node->next;
        current++;
    }
}
