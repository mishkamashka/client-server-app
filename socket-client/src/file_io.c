#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/linked_list.h"

bool save(linked_list_t *linked_list, const char *filename);

bool load(linked_list_t **p_linked_list, const char *filename);

linked_list_t *read_list_from_file(FILE *filename);

bool serialize(linked_list_t *linked_list, const char *filename);

bool deserialize(linked_list_t **p_linked_list, const char *filename);

bool save(linked_list_t *linked_list, const char *filename)
{
    FILE *file;
    if (access(filename, F_OK) != -1)
    {
        file = fopen(filename, "w");
    } else
    {
        if (creat(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != -1)
        {
            printf("File is created\n");
            file = fopen(filename, "w");
        } else
        {
            printf("File can not be created\n");
            return false;
        }
    }

    int length = list_length(linked_list) - 1;
    for (; length > -1; length--)
    {
        int i = list_get(linked_list, length);
        fprintf(file, "%d ", i);
    }
    fclose(file);
    return true;
}

bool load(linked_list_t **p_linked_list, const char *filename)
{
    FILE *file;
    if (access(filename, R_OK) != -1)
    {
        file = fopen(filename, "r");
    } else
    {
        return false;
    }
    if ((*p_linked_list = read_list_from_file(file)) == NULL)
    {
        printf("File is empty\n");
        return false;
    }

    fclose(file);
    return true;
}

linked_list_t *read_list_from_file(FILE *filename)
{
    char *input_value = malloc(sizeof(char));
    int input;
    linked_list_t *linked_list = NULL;

    while (fscanf(filename, "%s", input_value) != EOF)
    {
        input = atoi(input_value);
        if ((sizeof(input_value) / sizeof(char) == 8 && *input_value == '0') || !(input == 0))
        {
            if (linked_list == NULL)
            {
                linked_list = list_create(input);
            } else
            {
                linked_list = list_add_front(input, &linked_list);
            }
        }
    }
    return linked_list;
}

bool serialize(linked_list_t *linked_list, const char *filename)
{
    FILE *file;
    if (access(filename, F_OK) != -1)
    {
        file = fopen(filename, "wb");
    } else
    {
        if (creat(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != -1)
        {
            printf("File is created\n");
            file = fopen(filename, "wb");
        } else
        {
            printf("File can not be created\n");
            return false;
        }
    }

    int length = list_length(linked_list) - 1;
    for (; length > -1; length--)
    {
        int i = list_get(linked_list, length);
        fprintf(file, "%d ", i);
    }
    fclose(file);
    return true;
}

bool deserialize(linked_list_t **p_linked_list, const char *filename)
{
    FILE *file;
    if (access(filename, R_OK) != -1)
    {
        file = fopen(filename, "r");
    } else
    {
        return false;
    }
    if ((*p_linked_list = read_list_from_file(file)) == NULL)
    {
        printf("File is empty\n");
        return false;
    }
    fclose(file);
    return true;
}