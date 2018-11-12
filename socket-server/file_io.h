#ifndef FILE_IO_H
#define FILE_IO_H

bool save(linked_list_t *linked_list, const char *filename);
bool load(linked_list_t **p_linked_list, const char* filename);
bool serialize(linked_list_t* linked_list, const char* filename);
bool deserialize(linked_list_t** p_linked_list, const char* filename);

#endif