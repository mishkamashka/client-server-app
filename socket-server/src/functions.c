#include <stdio.h>
#include <stdbool.h>
#include "linked-list.h"

void foreach (void (*func)(int), linked_list_t * linked_list);
linked_list_t *map(int (*func)(int), linked_list_t *linked_list);
linked_list_t *map_mut(int (*func)(int), linked_list_t *linked_list);
int foldl(int a, int (*func)(int, int), linked_list_t *linked_list);
linked_list_t *iterate(int s, int length, int (*func)(int));

void foreach (void (*func)(int), linked_list_t * linked_list)
{
    while (linked_list != NULL)
    {
        func(linked_list->value);
        linked_list = linked_list->next;
    }
}

linked_list_t *map(int (*func)(int), linked_list_t *linked_list)
{
    linked_list_t *result = NULL;
    while (linked_list != NULL)
    {
        if (result == NULL)
        {
            result = list_create(func(linked_list->value));
        }
        else
        {
            list_add_back(func(linked_list->value), result);
        }
        linked_list = linked_list->next;
    }
    return result;
}

linked_list_t *map_mut(int (*func)(int), linked_list_t *linked_list)
{
    while (linked_list != NULL)
    {
        linked_list->value = func(linked_list->value);
        linked_list = linked_list->next;
    }
    return linked_list;
}

int foldl(int a, int (*func)(int, int), linked_list_t *linked_list)
{
    while(linked_list != NULL)
    {
        a = func(linked_list->value, a);
        linked_list = linked_list->next;
    }
    return a;
}

linked_list_t *iterate(const int s, int length, int (*func)(int))
{
    linked_list_t *result = list_create(s);
    while (length > 1)
    {
        result = list_add_front(func(result->value), &result);
        length--;
    }
    return result;
}