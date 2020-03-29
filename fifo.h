#ifndef FIFO_H
#define FIFO_H

#include <stdio.h>
#include <stdlib.h>

/* Status struct */
typedef struct {
    int presence;
    int height;
} stat_t;

/* Node struct */
typedef struct _node{
    stat_t stat;
    struct _node* next;
} node_t;

/* Fifo buffer struct */
typedef struct {
    node_t* first;
} fifo_t;

fifo_t* create_fifo(); /* Create a new  fifo buffer */
void put_fifo(fifo_t* fifo, int pres, int h); /* Put a new node into the fifo buffer */
stat_t read_fifo(fifo_t* fifo); /* Read the first node's status of the fifo buffer */
int dec_height_fifo(fifo_t* fifo); /* Decrease the parameter "height" of all nodes of the fifo buffer */
int delete_first_fifo(fifo_t* fifo); /* Delete the first node of the fifo buffer */
void delete_fifo(fifo_t* fifo); /* Delete the entire fifo buffer */

#endif
