#include "header.h"
#include <malloc.h>
#include<math.h>

struct queue *played_boards = NULL;

void code_board(struct chess_board_less_memory* empty_board, struct square board[8][8])     // random seed
{
    for (int i = 0; i < 2; empty_board->piece[i++] = 0);
    empty_board->color = 0;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            unsigned long long n = pow(2, y * 8 + x);
            if (board[y][x].type)
            {
                empty_board->piece[board[y][x].type - 1] += n;// board[y][x].type - 1 because we don't need arr for empty
                empty_board->color += board[y][x].color * n;
            }
        }
    }
}


void decode_board(struct square(*empty_board)[8], struct chess_board_less_memory board)
{
    for (int i = 0; i < 2; i++)
    {
        for (int y = 7; y >= 0; y--)
            for (int x = 7; x >= 0; x--)
            {
                unsigned long long n = pow(2, y * 8 + x);
                if (n <= board.piece[i])
                {
                    empty_board[y][x].type = i + 1;
                    board.piece[i] -= n;
                }
            }
    }

    for (int y = 7; y >= 0; y--)
        for (int x = 7; x >= 0; x--)
        {
            unsigned long long n = pow(2, y * 8 + x);
            if (n <= board.color)
            {
                empty_board[y][x].color = white;
                board.color -= n;
            }
        }
}

struct queue * add_element(struct queue *head, codeBoard new_board)
{
    struct queue *new_element = malloc(sizeof *new_element); /// create the new element
    if(!new_element) return NULL; /// check if the malloc is successful if not return NULL

    new_element->next = NULL; ///making the next null because the the address is somewhere we can t touch
    new_element->board = new_board;
    if(!head) return new_element; ///if the first element doesnt exist than initialize it and return it

    struct queue *start = head; ///else loop through the queue and add the new element to the end
    for(;head->next;head = head->next);
    head->next = new_element;

    return start; /// return the start of the queue
}

struct queue * pop_element(struct queue *head)
{
    if(head == NULL) return NULL; /// check if the first element is NULL

    struct queue * new_head = head->next; ///making the new head the next element in the queue

    free(head);/// free the memory of the old head

    return new_head;/// return the address of the new head
}


