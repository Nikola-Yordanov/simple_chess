#include<stdio.h>
#include "header.h"
#include <time.h>
#include <stdlib.h>

long long global_evaluation = 0;
int move_cnt = 0;
struct square board[8][8];

struct queue *played_boards;


void fill_board()
{
    for(int i = 0;i < SIZE;i++)
        for(int j = 0;j < SIZE;j++)
            board[i][j].type = empty;

    board[1][1].type = king;
    board[1][2].type = rook;

    board[5][5].type = king;
    board[6][6].type = rook;
    board[5][5].color = white;
    board[6][6].color = white;
}


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

void move_piece(enum color color)
{
    struct position from, to;

    back:;
    printf("Enter cords of the piece you want to move:\n");
    scanf("%d", &from.x);
    scanf("%d", &from.y);

    if (board[from.y][from.x].type == empty || board[from.y][from.x].color != color)
    {
        printf("Wrong cords!\n");
        goto back;
    }

    struct move move = {from, from};
    if(!piece[board[from.y][from.x].type].enum_move(&from, &move))
    {
        printf("This piece has no possible moves!\n");
        goto back;
    }

    back1:;
    printf("Enter where you want to move the piece:\n");
    scanf("%d", &to.x);
    scanf("%d", &to.y);

    move.from = from;
    move.to = to;
    if(!piece[board[from.y][from.x].type].valid_move(move))
    {
        printf("This move is not valid!\n");
        goto back1;
    }

    struct undo taken;
    int undo_move;
    piece[board[from.y][from.x].type].play_move(&move, &taken, &undo_move);
    board[from.y][from.x].type = empty;
}


int timeout ( int seconds )
{
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}
    return  1;
}

struct queue * add_element(struct queue *head, struct square new_board[8][8]);
struct queue * clear_queue(struct queue * queue);
void print_game(struct queue *game_positions);
enum bool find_best_move(struct move *move, int *out_eval, enum color player, int depth, int alpha, int beta);

int main()
{
    struct move move;
    struct undo undo;
    int eval = 0, depth, mode, alpha = -1e8, beta = 1e8, turn;
    system("cls");
    printf("                                                      CHESS               \n\n"
           "Information:\n"
           "The figures that you will be playing with will always be small letters.\n\n"
           "List of figures are:\n"
           "k - King\n"
           "r - Rook\n"
           "Press Any Key To Continue...");
    printf("Please choose your level:\n"
           "0  - New to Chess\n"
           "2 - Beginner\n"
           "4 - Intermediate\n"
           "6 - Grandmaster / Advanced\n\n\n");
    Enter:;
    printf("Enter: ");

    scanf("%d", &depth);

    turn1:;
    printf("Please choose piece color\n"
           "0 - Black\n"
           "1 - White\n");

    scanf("%d", &turn);

    if (turn != 0 && turn != 1)
    {
        printf("Invalid color, please choose again!\n");
        goto turn1;
    }


    fill_board();
    while (true)
    {
        played_boards = add_element(played_boards, board);
        if (global_evaluation >= 1e6)
        {
            printf("White wins!!!\n");
            break;
        }

        if (global_evaluation <= -1e6)
        {
            printf("Black wins!!!\n");
            break;
        }

        printf(turn ? "White\n" : "Black\n");
        print_board(board);

        if (turn)
            move_piece(turn);

        else
        {
            int undo_eval;
            find_best_move(&move, &eval, turn, depth, alpha, beta);
            piece[board[move.from.y][move.from.x].type].play_move(&move, &undo, &undo_eval);
            printf("%d, %d , %d, %d", move.from.x, move.from.y, move.to.x, move.to.y);
        }
        printf("depth = %d\n", depth);
        move_cnt++;
        turn = !turn;

    }

    print_game(played_boards);
    played_boards = clear_queue(played_boards);

    return 0;
}
