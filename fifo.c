#include "fifo.h"

/* Create a new  fifo buffer */
fifo_t* create_fifo(){
    fifo_t* fifo = (fifo_t*) malloc(sizeof(fifo_t));
    fifo->first = NULL;

    return fifo;
}

/* Put a new node into the fifo buffer */
void put_fifo(fifo_t* fifo, int pres, int h){
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->stat.presence = pres;
    new_node->stat.height = h;

    if(fifo->first == NULL) fifo->first = new_node;
    else{
        node_t* temp = fifo->first;

        while(temp->next != NULL) temp = temp->next;

        temp->next = new_node;
    }

    return;
}

/* Read the first node's status of the fifo buffer */
stat_t read_fifo(fifo_t* fifo){
    if(fifo->first == NULL){
        stat_t temp;
        temp.presence = -1;
        temp.height = -1;
        return temp;
    };

    return fifo->first->stat;
}

/* Decrease the parameter "height" of all nodes of the fifo buffer */
int dec_height_fifo(fifo_t* fifo){
    if(fifo->first == NULL) return 0;

    node_t* temp = fifo->first;

    while(temp != NULL){
        if((temp->stat.height) > 0) (temp->stat.height)--;
        temp = temp->next;
    }

    return 1;
}

/* Delete the first node of the fifo buffer */
int delete_first_fifo(fifo_t* fifo){
    if(fifo->first == NULL) return 0;

    node_t* to_be_del = fifo->first;

    fifo->first = fifo->first->next;

    free(to_be_del);

    return 1;
}

/* Delete the entire fifo buffer */
void delete_fifo(fifo_t* fifo){
    node_t* temp = fifo->first;
    node_t* to_be_del;

    while(temp != NULL){
        to_be_del = temp;
        temp = temp->next;
        free(to_be_del);
    }

    free(fifo);
}
