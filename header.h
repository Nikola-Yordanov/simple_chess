#ifndef CHESS_ROOK_KING_HEADER_H
#define CHESS_ROOK_KING_HEADER_H

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
    enum bool (*valid_move)(struct move move);
    void(*play_move)(struct move* move, struct undo* taken, int* undo_move);
    enum bool (*enum_move)(struct position* pos, struct move* move); // pos!=0 for the first move
};

typedef struct chess_board_less_memory //typicaly for a chess board are need 64 ints but this way only 14 are needed
{
    unsigned long long piece[2];// rook, 0 - queen, 1 - king
    unsigned long long color;// at first every piece is black by default
} codeBoard;

struct queue
{
    codeBoard board;
    struct queue *next;
};

///global variables
extern long long global_evaluation;
extern struct square board[8][8];
extern struct piece piece[3];
extern int move_cnt;


#endif //CHESS_ROOK_KING_HEADER_H
