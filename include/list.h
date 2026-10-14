#pragma once

typedef struct s_list	t_list;

typedef struct	s_list {
	t_list*	prev;
	t_list* next;
	void*	elem;
}	t_list;

//	list.c
t_list*			list_new_node(void* elem);
void			list_push_back(t_list **list, t_list *node);
void			list_clear(t_list* list);
void			list_clear_no_free_elem(t_list* list);
void    		list_erase(t_list** node);
void    		list_insert(t_list* prev, t_list* node);
void    		list_swap(t_list* node1, t_list* node2);
unsigned int	list_count(t_list* list);