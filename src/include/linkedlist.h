#include <stdio.h>
#include "position.h"
#include <stdlib.h>

#ifndef NODE_H
#define NODE_H

typedef struct Node
{
    Position value;
    struct Node *next;
}node_t;

node_t *create_new_node(Position);
void insertNodeAtEnd(node_t *);
void shift(node_t *);

void printlist(node_t *);
void testBody();

#endif