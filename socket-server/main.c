#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include "linked-list.h"
#include "functions.h"
#include "file_io.h"

linked_list_t *read_list();
void lab3();
void print_list(linked_list_t *linked_list);
void print_list_with_newline(linked_list_t *linked_list);
int square(int number);
int cube(int number);
int get_max(int a, int b);
int get_min(int a, int b);
int get_sum(int a, int b);
int pow_of_two(int a);

int main(int argc, char const *argv[])
{
    //lab3();

     const char *filepath = "/home/mishka/Desktop/sp/sp-lab4/sources/file";
     const char *wfilepath = "/home/mishka/Desktop/sp/sp-lab4/sources/wfile";
     const char *bfilepath = "/home/mishka/Desktop/sp/sp-lab4/sources/file.bin";

     linked_list_t *linked_list = NULL;
     if (load(&linked_list, filepath) == false)
     {
         printf("Could not load list\n");
         return 0;
     }
     print_list(linked_list);
     print_list_with_newline(linked_list);
     printf("Square values:\n");
     print_list(map(square, linked_list));
     printf("Cube values:\n");
     print_list(map(cube, linked_list));

     int max = INT_MIN;
     int min = INT_MAX;
     int sum = 0;
     printf("Max value: %d\n", foldl(max, get_max, linked_list));
     printf("Min value: %d\n", foldl(min, get_min, linked_list));
     printf("Sum: %d\n", foldl(sum, get_sum, linked_list));
     printf("Modules:\n");
     map_mut(abs, linked_list);
     print_list(linked_list);

     printf("Pows of 2:\n");
     print_list(iterate(1, 10, pow_of_two));

     if (save(linked_list, wfilepath) == false)
     {
         printf("Something wrong\n");
     }
     else
     {
         printf("List is saved\n");
     }

     linked_list_t *new_linked_list = NULL;

     if (load(&new_linked_list, wfilepath) == false)
     {
         printf("Could not load list\n");
     }
     else
     {
         printf("List is loaded\n");
     }

     printf("%s", compare(linked_list, new_linked_list) ? "Lists are equal\n" : "Lists are not equal\n");

     serialize(linked_list, bfilepath);
     deserialize(&new_linked_list, bfilepath);
     printf("%s", compare(linked_list, new_linked_list) ? "Lists are equal\n" : "Lists are not equal\n");
     list_free(linked_list);
    return 0;
}

void lab3()
{
    linked_list_t *linked_list = read_list();
    int n = 0;
    printf("Elements' sum is %d\n", list_sum(linked_list));
    printf("Enter number of the element to see its value:\n");
    scanf("%d", &n);
    if (n <= list_length(linked_list))
    {
        printf("Element with number %d is %d\n", n, list_get(linked_list, n));
    }
    else
    {
        printf("Element with number %d does not exist, list's length is %d\n", n, list_length(linked_list));
    }
    list_free(linked_list);
}

linked_list_t *read_list()
{
    int input_value;
    linked_list_t *linked_list = NULL;
    printf("Enter integer numbers:\n");
    int ret;
    while ((ret = scanf("%d", &input_value)) != EOF)
    {
        if (ret == 1)
        {
            if (linked_list == NULL)
            {
                linked_list = list_create(input_value);
            }
            else
            {
                linked_list = list_add_front(input_value, &linked_list);
            }
        }
        else
        {
            printf("Discarding junk in buffer: ");
            int c;
            while ((c = getchar()) != EOF && c != '\n')
                putchar(c);
            putchar('\n');
            if (c == EOF)
                break;
        }
    }
    return linked_list;
}

void print_list(linked_list_t *linked_list)
{
    while (linked_list != NULL)
    {
        printf("%d ", linked_list->value);
        linked_list = linked_list->next;
    }
    printf("\n");
}

void print_list_with_newline(linked_list_t *linked_list)
{
    while (linked_list != NULL)
    {
        printf("%d\n", linked_list->value);
        linked_list = linked_list->next;
    }
}

int square(int number)
{
    return number*number;
}

int cube(int number)
{
    return number*number*number;
}

int get_max(int a, int b)
{
    return a > b ? a : b;
}

int get_min(int a, int b)
{
    return a < b ? a : b;
}

int get_sum(int a, int b)
{
    return a + b;
}

int pow_of_two(int a)
{
    return 2 * a;
}
