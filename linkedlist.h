/* C linked list implementation.              *
 * any data type acceptable.                  *
 * Functions for comparing and showing        *
 * type variables must be defined separately. *
 *                                            *
 * Skupoy Sergey. 2014                        */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

/* function pointer to compare and show functions *
 *                                                */
typedef int (*COMPARE) (void*, void*);
typedef void (*SHOW) (void*);

/* node structure */
typedef struct _node {
    void *data;
    struct _node *next;
} list_node;

/* list structure */
typedef struct _linked_list {
    list_node *head;
    list_node *tail;
} linked_list;

/* list initialization */
void initialize_list (linked_list *list) {
    list -> head = NULL;
    list -> tail = NULL;
}

/* add node to head */
void add_head (linked_list *list, void *data) {
    /* create new node and allocate memory */
    list_node *node = (list_node*) malloc (sizeof (list_node));

    /* check if memory is available */
    if (node == NULL) {
	printf ("\nNo memory available!\n");
	return;
    }

    /* add new node to head */
    node -> data = data;
    if (list -> head == NULL) {
	list -> tail = node;
	node -> next = NULL;
    }
    else {
	node -> next = list -> head;
    }
    
    list -> head = node;
}

/* add node to the end of list */
void add_tail (linked_list *list, void *data) {
    list_node *node = (list_node*) malloc (sizeof (list_node));

    /* check if memory is available */
    if (node == NULL) {
	printf ("\nNo memory available!\n");
	return;
    }

    /* add new node to the end of list */
    node -> data = data;
    node -> next = NULL;
    if (list -> head == NULL) {
	list -> head = node;
    }
    else {
	list -> tail -> next = node;
    }    
    list -> tail = node;
}

/*delete node if it contains "data" value */
void delete (linked_list *list, COMPARE compare, void *data) {
    list_node *node = list -> head;
    if (compare (node -> data, data) == 0) {
	list -> head = node -> next;
	free (node);
	printf ("\nNode deleted successfully\n");
	return;
    }
    else {
        list_node *prev = node;
        node = node -> next;
       
        while (node != NULL) {
	    /* if node is found delete it */
	    if (compare (node -> data, data) == 0) {
		prev -> next = node -> next;
		free (node);
		printf ("\nNode deleted successfully\n");
		return;
	    }
	    prev = node;
	    node = node -> next;
	}
	printf ("\nNode not found\n");
    }
}

/* show list */
void show_list (linked_list *list, SHOW show) {
    if (list -> head == NULL) {
	printf ("\nList is empty!\n");
    }
    else {
        printf ("\nLinked list:\n");
    
        list_node *current = list -> head;

        while (current != NULL) {
	    show (current -> data);
	    current = current -> next;
        }
    
        printf ("\n__end of list__\n");
    }
}

/* reverse list */
void reverse_list (linked_list *list) {
    list_node *current = list -> head;
    list_node *prev = NULL;
    list_node *next = current;

    /* reassign "next" pointer for every node */
    while (current != NULL) {
	next = current -> next;
	current -> next = prev;
	prev = current;
	current = next;
    }

    /* swap head and tail pointers */
    list_node *tmp = list -> head;
    list -> head = list -> tail;
    list -> tail = tmp;
}

#endif
