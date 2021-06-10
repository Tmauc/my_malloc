/*
** EPITECH PROJECT, 2019
** struct.h
** File description:
** struct.h
*/

#ifndef STRUCT_H_
# define STRUCT_H_

#include "my.h"

typedef struct s_block t_block;
struct s_block
{
    size_t size;
    int free;
    t_block *next;
};

extern t_block *b;
extern pthread_mutex_t MUTEX;

#endif /* STURCT_H */
