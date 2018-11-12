#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct linked_list_t
{
    int value;
    struct linked_list_t *next;
} linked_list_t;

linked_list_t *list_create(int n);
linked_list_t *list_add_front(int n, linked_list_t **linked_list);
void list_add_back(int n    , linked_list_t *linked_list);
int list_get(linked_list_t *linked_list, int index);
void list_free(linked_list_t *linked_list);
int list_length(linked_list_t *linked_list);
linked_list_t *list_node_at(linked_list_t *linked_list, int index);
int list_sum(linked_list_t *linked_list);

linked_list_t *list_create(const int n)
{
    linked_list_t *head = (linked_list_t *)malloc(sizeof(linked_list_t));
    head->value = n;
    head->next = NULL;
    return head;
}

linked_list_t *list_add_front(const int n, linked_list_t **linked_list)
{
    linked_list_t *new_element = (linked_list_t *)malloc(sizeof(linked_list_t));
    new_element->value = n;
    new_element->next = *linked_list;
    *linked_list = new_element;
    return *linked_list;
}

void list_add_back(const int n, linked_list_t *linked_list)
{
    linked_list_t *new_element = (linked_list_t *)malloc(sizeof(linked_list_t));
    new_element->value = n;
    new_element->next = NULL;
    linked_list = list_node_at(linked_list, list_length(linked_list) - 1);
    linked_list->next = new_element;
}

int list_get(linked_list_t *linked_list, const int index)
{
    if (index > list_length(linked_list))
    {
        return 0;
    }
    else
    {
        return list_node_at(linked_list, index)->value;
    }
}

void list_free(linked_list_t *linked_list)
{
    if (linked_list == NULL)
        return;
    linked_list_t *next_list;
    for (; linked_list->next; linked_list = next_list)
    {
        next_list = linked_list->next;
        free(next_list);
    }
}

int list_length(linked_list_t *linked_list)
{
    int length = 0;
    while (linked_list != NULL)
    {
        length++;
        linked_list = linked_list->next;
    }
    return length;
}

linked_list_t *list_node_at(linked_list_t *linked_list, const int index)
{
    for (int i = 0; (i < index) && (linked_list->next != NULL); i++)
    {
        linked_list = linked_list->next;
    }
    if (linked_list == NULL)
    {
        return NULL;
    }
    else
    {
        return linked_list;
    }
}

int list_sum(linked_list_t *linked_list)
{
    int sum = 0;
    while (linked_list != NULL)
    {
        sum += linked_list->value;
        linked_list = linked_list->next;
    }
    return sum;
}

bool compare(linked_list_t* linked_list_1, linked_list_t* linked_list_2)
{
    return list_length(linked_list_1) == list_length(linked_list_2)? true : false;

}