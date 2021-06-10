/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main.c
*/

#include "my.h"
#include "struct.h"
#include <stdio.h>

t_block *list;
pthread_mutex_t MUTEX;

void *return_mutex(void *ptr)
{
    pthread_mutex_unlock(&MUTEX);
    return (ptr);
}

void check_size(t_block *tmp_list, size_t size)
{
    t_block *new = (t_block*)((char *)tmp_list + sizeof(struct s_block) + size);
    const int tmp_size = tmp_list->size - size - sizeof(struct s_block);

    if (tmp_size > 0) {
        new->free = 0;
        new->size = (size_t)tmp_size;
        new->next = tmp_list->next;
        tmp_list->next = new;
    }
    tmp_list->free = 1;
    tmp_list->size = size;
}

void initalize_list(t_block *tmp_list, size_t size)
{
    tmp_list->size = size;
    tmp_list->free = 1;
    tmp_list->next = NULL;
}

void *first_alloc(size_t size)
{
    if ((list = sbrk(sizeof(struct s_block) + size)) == (void *)-1) {
            return NULL;
    }
    initalize_list(list, size);
    return ((void *)list + sizeof(struct s_block));
}

void *malloc(size_t size)
{
    t_block *tmp_list = list;

    pthread_mutex_lock(&MUTEX);
    if (list == NULL) {
        return (return_mutex(first_alloc(size)));
    }
    for (; tmp_list->next != NULL; tmp_list = tmp_list->next) {
        if (tmp_list->free == 0 && size <= tmp_list->size) {
            tmp_list->free = 1;
            check_size(tmp_list, size);
            return (return_mutex((void *)tmp_list + sizeof(struct s_block)));
        }
    }
    if ((tmp_list->next = sbrk(sizeof(struct s_block) + size)) == (void *)-1)
        return (return_mutex(NULL));
    tmp_list = tmp_list->next;
    initalize_list(tmp_list, size);
    return (return_mutex((void *)tmp_list + sizeof(struct s_block)));
}