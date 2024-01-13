#include "linkedlist.h"

/*
This functions allocates space for a new node,
and sets the next last node to null.

function: creat_new_node
param: value, current pos when added to body
returns: node_t
*/

node_t *create_new_node(Position value)
{
    /*allocate memory for new node*/
    node_t *result = malloc(sizeof(node_t));

    result->value = value;
    result->next = NULL;
    return result;
}

/*
This functions finds the last pos in body 
of the snake, and adds a new node for body piece.

function: insertNodeAtEnd
param: head, ptr to body of snake
       pos, current pos when added to body
*/

void insertNodeAtEnd(node_t *head)
{
    node_t *temp;
    Position newPos;

    if(head == NULL)
        return;

    temp = head;

    /*this goes through the linked list till it reaches the last element*/
    while(temp->next != NULL)
    {
        temp = temp->next;
        newPos = temp->value;
    }
    temp->next = create_new_node(newPos);
}

/*
This functions shifts all the elements inside
linked list to the right. Starting at the second element

function: shift
param: body, ptr to body of snake
*/

void shift(node_t *body)
{
    if(body == NULL || body->next == NULL)
    {
        return;
    }

    node_t *temp = body;
    Position shiftedPos[1000];
    int i = 0;

    while(temp != NULL)
    {
        shiftedPos[i++] = temp->value;
        temp = temp->next;
    }

    printf("\n");

    /*temp starts at the second pos in body. We dont want to update the head. Just the body*/
    temp = body->next;
    i = 0;

    while(temp != NULL)
    {
        temp->value = shiftedPos[i++];
        temp = temp->next;
    }
}

void printlist(node_t *head)
{
    node_t *temp = head;
    while(temp != NULL)
    {
        printf("[%d, %d]->", temp->value.x, temp->value.y);
        temp = temp->next;
    }

    printf("NULL\n");
}

void testBody()
{
    node_t *head = NULL;
    node_t *temp;

    head = create_new_node((Position){0,0});

    for(int i = 1; i < 10; i++)
    {
        if(head == NULL)
            return;

        temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = create_new_node((Position){i,i});
    }

    for(int i = 0; i < 10; i++)
    {
        shift(head);
        head->value = (Position){i,i};
        printlist(head);
    }
}