#include <stdio.h>
#include "header.h"

long long global_evaluation = 0;
int move_cnt = 0;
struct square board[8][8];
struct piece piece[3];
struct queue *played_boards;

char getPiece(struct square p)
{
    if (p.type == king && p.color == white) return 'k';
    if (p.type == king) return 'K';
    if (p.type == rook && p.color == white) return 'r';
    if (p.type == rook) return 'R';
    return ' ';
}

void print_board(struct square board[8][8])
{
    printf("  X");
    for (int x = 0; x < 8; x++)
        printf("   %d", x);

    printf("\n");
    for (int y = 0; y < 8; y++)
    {
        printf("    |");
        for (int x = 0; x < 8; x++)
            printf("---+");

        printf("\n");
        printf("%d ->|", y);
        for (int x = 0; x < 8; x++)
        {
            char a = getPiece(board[y][x]);
            printf(" %c |", a);
        }
        if (y == 8 - 1)
        {
            printf("\n"); printf("    |");
            for (int x = 0; x < 8; x++)
                printf("---+");
        }
        printf("\n");
    }
    printf("  Y  ");
    printf("\n"); printf("\n");
}

struct queue * add_element(struct queue *head, struct square new_board[8][8]);
struct queue * pop_element(struct queue *head);
void print_game(struct queue *game_positions);
enum bool find_best_move(struct move *move, int *out_eval, enum color player, int depth, int alpha, int beta);


int main()
{



    return 0;
}
