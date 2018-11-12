#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void foreach (void (*func)(int), linked_list_t * linked_list);
linked_list_t *map(int (*func)(int), linked_list_t *linked_list);
linked_list_t *map_mut(int (*func)(int), linked_list_t *linked_list);
int foldl(int a, int (*func)(int, int), linked_list_t *linked_list);
linked_list_t *iterate(int s, int length, int (*func)(int));

#endif
