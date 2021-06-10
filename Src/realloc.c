/*
** EPITECH PROJECT, 2019
** realloc.c
** File description:
** realloc.c
*/

#include "my.h"
#include "struct.h"

extern t_block *list;

void free_re(t_block *tmp)
{
    tmp->free = 0;
}

void copy_data(t_block *tmp, void *ptr, void *dest)
{
    memcpy(dest, ptr, tmp->size);
    free_re(tmp);
}

void *check_data(void *ptr, size_t size, t_block *tmp, void *dest)
{
    if (size <= tmp->size)
        return (ptr);
    copy_data(tmp, ptr, dest);
    return (dest);
}

void *realloc(void *ptr, size_t size)
{
    void *dest = malloc(size);
    t_block *tmp = list;
    t_block *tmp_prev = tmp;

    if (size == 0)
        return (ptr);
    if (ptr == NULL || ((size_t)tmp + sizeof(struct s_block)) > (size_t)(ptr))
        return (dest);
    for (; tmp != NULL; tmp = tmp->next) {
        if (((size_t)tmp + sizeof(struct s_block)) > (size_t)(ptr))
            return (check_data(ptr, size, tmp_prev, dest));
        else if (((size_t)tmp + sizeof(struct s_block)) == (size_t)(ptr))
            return (check_data(ptr, size, tmp, dest));
        tmp_prev = tmp;
    }
    return (dest);
}