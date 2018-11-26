#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct linked_list_t
{
    int value;
    struct linked_list_t *next;
} linked_list_t;

int main(int argc, char const *argv[]);
linked_list_t *list_create(int n);
linked_list_t *list_add_front(int n, linked_list_t **linked_list);
void list_add_back(int n, linked_list_t *linked_list);
int list_get(linked_list_t *linked_list, int index);
void list_free(linked_list_t *linked_list);
int list_length(linked_list_t *linked_list);
linked_list_t *list_node_at(linked_list_t *linked_list, int index);
int list_sum(linked_list_t *linked_list);
bool compare(linked_list_t* linked_list_1, linked_list_t* linked_list_2);

#endif
