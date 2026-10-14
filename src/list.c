#include <stdlib.h>

#include "list.h"

t_list*	list_new_node(void* elem) {
	t_list*	node = malloc(sizeof(t_list));
	if (!node)	exit(EXIT_FAILURE);

	node->next = NULL;
	node->prev = NULL;
	node->elem = elem;

	return node;
}

void	list_push_back(t_list **list, t_list *node) {
	if (!*list) {
		*list = node;
		node->prev = NULL;
		node->next = NULL;
		return;
	}

	t_list *tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
		
	tmp->next = node;
	node->prev = tmp;
	node->next = NULL;
}

void	list_clear(t_list* list) {
	t_list*	tmp = list;
	while (list) {
		tmp = list->next;
		free(list->elem);
		free(list);
		list = tmp;
	}
}

void	list_clear_no_free_elem(t_list* list) {
	t_list*	tmp = list;
	while (list) {
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void    list_erase(t_list** node) {
    if (!node || !*node)
        return ;

    t_list *current = *node;

    if (!current->prev) {
        if (current->next) {
            *node = current->next;
            (*node)->prev = NULL;
            free(current);
        } else {
            free(current);
            *node = NULL;
        }
    } else {
        if (current->next) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
        } else {
            current->prev->next = NULL;
            free(current);
        }
    }
}

void    list_insert(t_list* prev, t_list* node) {
    if (!prev || !node)
        return ;
    node->next = prev->next;
    node->prev = prev;
    if (prev->next)
        prev->next->prev = node;
    prev->next = node;
}

void    list_swap(t_list* node1, t_list* node2) {
    t_list *p1;
    t_list *n1;
    t_list *p2;
    t_list *n2;

    if (!node1 || !node2 || node1 == node2)
        return ;
    p1 = node1->prev;
    n1 = node1->next;
    p2 = node2->prev;
    n2 = node2->next;
    if (n1 == node2) {
        node1->next = n2;
        node1->prev = node2;
        node2->next = node1;
        node2->prev = p1;
        if (p1)	p1->next = node2;
        if (n2)	n2->prev = node1;
    } else if (n2 == node1) {
        node2->next = n1;
        node2->prev = node1;
        node1->next = node2;
        node1->prev = p2;
        if (p2)	p2->next = node1;
        if (n1)	n1->prev = node2;
    } else {
        node1->prev = p2;
        node1->next = n2;
        node2->prev = p1;
        node2->next = n1;
        if (p1)	p1->next = node2;
        if (n1)	n1->prev = node2;
        if (p2)	p2->next = node1;
        if (n2)	n2->prev = node1;
    }
}

unsigned int	list_count(t_list* list) {
	unsigned int c = 0;
	while (list) {
    c++;
    list = list->next;
	}
	return c;
}