/*
** EPITECH PROJECT, 2019
** realloc.c
** File description:
** realloc.c
*/

#include "my.h"
#include "struct.h"

extern t_block *list;

void show_alloc_mem(void)
{
    t_block *tmp_list = list;

    setbuf(stdout, NULL);
    printf("break : %p\n", sbrk(0));
    for (; tmp_list->next != NULL; tmp_list = tmp_list->next) {
        printf("%p - %p : %ld bytes\n", tmp_list + sizeof(struct s_block),
        tmp_list + sizeof(struct s_block) + tmp_list->size, tmp_list->size);
    }
    printf("%p - %p : %ld bytes\n", tmp_list + sizeof(struct s_block),
    tmp_list + sizeof(struct s_block) + tmp_list->size, tmp_list->size);
}

void concat_list(t_block *a, t_block *tmp)
{
    int nb = 0;
    t_block *ok = list;

    a->free = 0;
    if (a->next != NULL && a->next->free == 0) {
        a->size += a->next->size + sizeof(struct s_block);
        a->next = a->next->next;
    }
    if (a->next == NULL) {
        for (; ok->next != NULL; ok = ok->next, nb++);
        if (nb == 0) {
            sbrk(-(list->size));
            list = NULL;
        } else {
            sbrk(-(tmp->next->size + sizeof(struct s_block)));
            tmp->next = NULL;
        }
    }
    pthread_mutex_unlock(&MUTEX);
}

void loop_free(t_block *tmp, void *ptr)
{
    t_block *tmp_prev = tmp;
    t_block *tmp_prev2 = tmp;

    for (; tmp != NULL; tmp = tmp->next) {
        if (((size_t)tmp + sizeof(struct s_block)) > (size_t)(ptr)) {
            concat_list(tmp_prev, tmp_prev2);
            return;
        } else if (((size_t)tmp + sizeof(struct s_block)) == (size_t)(ptr)) {
            concat_list(tmp, tmp_prev);
            return;
        }
        if (tmp->next == NULL) {
            pthread_mutex_unlock(&MUTEX);
            return;
        }
        tmp_prev2 = tmp_prev;
        tmp_prev = tmp;
    }
}

void free(void *ptr)
{
    t_block *tmp = list;

    pthread_mutex_lock(&MUTEX);
    if (ptr == NULL || ((size_t)tmp + sizeof(struct s_block)) > (size_t)(ptr)) {
        pthread_mutex_unlock(&MUTEX);
        return;
    }
    loop_free(tmp, ptr);
}