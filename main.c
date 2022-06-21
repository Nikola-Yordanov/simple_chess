#include <malloc.h>

#define SIZE 8
enum type { empty, rook, king };
enum color { black, white };
enum bool{ false, true };

struct square
{
    enum type type;
    enum color color;
};

struct position
{
    int x, y;
};

struct move
{
    struct position from, to;
};

typedef unsigned weight;

struct undo
{
    enum type taken;
    int has_been_moved;
};

struct piece
{
    weight(*weight)(struct position pos);
    enum bool (*valid_move)(struct move move);              /// undo_eval better name
    void(*play_move)(struct move* move, struct undo* taken, int* undo_move, enum bool is_human);
    enum bool (*enum_move)(struct position* pos, struct move* move); // pos!=0 for the first move
};

#include<stdio.h>
#include<math.h>

typedef struct chess_board_less_memory //typicaly for a chess board are need 64 ints but this way only 14 are needed
{
    unsigned long long piece[2];//, 0 - pawn, 1 - knight, 2 - bishop, 3 - rook, 4 - queen, 5 - king
    unsigned long long color;// at first every piece is black by default
} codeBoard;

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


void fill_board(struct square(*board)[8])
{
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++)
            board[y][x].type = empty;

    board[0][4].type = board[7][4].type = king;
    board[0][4].color = black;
    board[7][4].color = white;
    board[0][0].type = board[0][7].type = board[7][0].type = board[7][7].type = rook;
    board[0][0].color = board[0][7].color = black;
    board[7][0].color = board[7][7].color = white;
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

void add_to_codeBoard(codeBoard coded, codeBoard* arr, int curr_index)
{
    arr[curr_index] = coded;
}

void add_curr_board_to_coded(struct square board[8][8], codeBoard* arr, int curr_index)
{
    codeBoard new_board;
    code_board(&new_board, board);
    add_to_codeBoard(new_board, arr, curr_index);

}

void print_codes(codeBoard* arr, int size)
{
    struct square printer[8][8];
    for (int i = 0; i < size; i++)
    {
        decode_board(printer, arr[i]);
        print_board(printer);
    }
}

int main()
{
    struct square board[8][8];
    fill_board(board);
    // print_board(board);
    struct chess_board_less_memory new_board;
    code_board(&new_board, board);
    //struct square old_new_board[8][8];
    //decode_board(old_new_board, new_board);
    //print_board(old_new_board);

    codeBoard all_boards[100]; int curr_index = 0;
    add_to_codeBoard(new_board, all_boards, curr_index++);

    print_codes(all_boards, curr_index);

    return 0;

}