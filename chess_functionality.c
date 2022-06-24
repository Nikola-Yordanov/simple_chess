#include "header.h"
#include <malloc.h>
#include<stdio.h>
#include<math.h>

struct chess_board_less_memory* code_board(const struct square (*board)[8])
{
    codeBoard  *empty_board = malloc(sizeof *empty_board);
    if(!empty_board) return NULL;

    for (int i = 0; i < 2; empty_board->piece[i++] = 0);
    empty_board->color = 0;

    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++)
        {
            unsigned long long n = pow(2, y * 8 + x);
            if (board[y][x].type)
            {
                empty_board->piece[board[y][x].type - 1] += n;// board[y][x].type - 1 because we don't need arr for empty
                empty_board->color += board[y][x].color * n;
            }
        }

    return empty_board;
}

struct square ** decode_board(struct chess_board_less_memory board)
{
    struct square (*empty_board)[SIZE] = malloc(sizeof (struct square[SIZE][SIZE]));

    for(int y = 0;y < SIZE;y++)
        for(int x = 0;x < SIZE;x ++)
            empty_board[y][x].type = empty;

    for (int i = 0; i < 2; i++)
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
    return empty_board;
}

void print_board(const struct square  (*board)[8]);


void * get_copy_board_pointer(const struct square  (*board)[8])
{
    struct square (*empty_board)[SIZE] = malloc(sizeof (struct square[SIZE][SIZE]));
    if(!empty_board)  return NULL;

    for(int y = 0;y < SIZE;y++)
        for(int x = 0;x < SIZE;x++)
            empty_board[y][x] = board[y][x];

    return code_board(empty_board);
}

void *get_copy_move_pointer(struct move move)
{
    struct move *ptr_move = malloc(sizeof *ptr_move);
    if(!ptr_move) return NULL;

    *ptr_move = move;

    return ptr_move;
}

void add_to_queue(struct node ** head, void *p, enum item_type t)
{
    struct item *new_item = malloc(sizeof *new_item);

    if(!new_item || !p) return;

    struct square (*y)[8] = p;

    new_item->type = t;
    if(t == CHESS_BOARD) new_item->code_board = p;
    if(t == MOVE) new_item->move = p;

    struct node * new_node = malloc(sizeof *new_node);
    if(!new_node) return;

    new_node->next = NULL;
    new_node->item = new_item;

    if(!(*head))
    {
        *head = new_node;
        return;
    }

    struct node *iterator = *head;
    for(;iterator->next; iterator = iterator->next);
    iterator->next = new_node;
}

void pop_from_queue(struct node ** head)
{
    if(!(*head)) return;

    struct node *next = (*head)->next;
    free(*head);
    *head = next;
}

void clear_queue(struct node ** head)
{
    for(;*head;*head = (*head)->next)
        pop_from_queue(head);
}


void print_game(struct node *head)
{
    for(struct node *iterator = head;iterator;iterator = iterator->next)
    {
        codeBoard *curr_board = iterator->item->code_board;
        struct square **new_board = decode_board(*curr_board);
        print_board(new_board);
    }
}

void print_moves(struct node *head)
{
    for(struct node *iterator = head;iterator;iterator = iterator->next)
    {
        struct move * move = iterator->item->move;
        printf("from (%d, %d) ------> to(%d, %d)\n", move->from.x, move->from.y, move->to.x, move->to.y);
    }
}

void print_end_game_state()
{
    if(global_evaluation >= 1e6)
        printf("White won!!!\n");

    if(global_evaluation <= -1e6)
        printf("White won!!!\n");

    printf("Game moves = %d\n\n\n", move_cnt);
}