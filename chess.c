#include "header.h"

int mod(int a) { return a < 0 ? -a : a; }

weight rook_weight(struct position pos) { return 500; }

enum bool rook_valid_move(struct move move)
{
    return (move.to.x >= 0 && move.to.x < SIZE && move.to.y >= 0 && move.to.y < SIZE &&
            (board[move.to.y][move.to.x].type == empty || board[move.to.y][move.to.x].color != board[move.from.y][move.from.x].color) &&
            (move.to.x == move.from.x || move.to.y == move.from.y));
}

enum bool rook_enum_move(struct position *pos, struct move *move)
{
    struct position d = {pos->x - move->to.x, pos->y - move->to.y};
    int a = mod(move->to.x - move->from.x + move->to.y - move->from.y) + 1;
    enum bool b = board[move->to.y][move->to.x].type != empty && board[move->to.y][move->to.x].color != board[move->from.y][move->from.x].color;

    move->to.x = pos->x;
    move->to.y = pos->y - a;
    if((!d.y && !d.x) || (d.y > 0 && !d.x))
    {
        if (!b && rook_valid_move(*move)) return true;
        b = false, a = 1;
        d.y = pos->y - move->to.y, d.x = pos->x - move->to.x;
    }

    move->to.x = pos->x + a;
    move->to.y = pos->y;
    if((d.y > 0 && !d.x) || (d.x < 0 && !d.y))
    {
        if (!b && rook_valid_move(*move)) return true;
        b = false, a = 1;
        d.y = pos->y - move->to.y, d.x = pos->x - move->to.x;
    }

    move->to.x = pos->x;
    move->to.y = pos->y + a;
    if((d.x < 0 && !d.y) || (!d.x && d.y < 0))
    {
        if (!b && rook_valid_move(*move)) return true;
        b = false, a = 1;
        d.y = pos->y - move->to.y, d.x = pos->x - move->to.x;
    }

    move->to.x = pos->x - a;
    move->to.y = pos->y;
    if( (!d.x && d.y < 0) || (!d.y && d.x > 0))
    {
        if (!b && rook_valid_move(*move)) return true;
        d.y = pos->y - move->to.y, d.x = pos->x - move->to.x;
    }
    return false;
}

weight king_weight(struct position pos) { return (weight) 1e7; }

enum bool king_valid_move(struct move move)
{
    return (mod(move.to.x - move.from.x) < 2 && mod(move.to.y - move.from.y) < 2 && move.to.x >= 0 &&move.to.x < SIZE && move.to.y >= 0 &&
            move.to.y < SIZE && (board[move.to.y][move.to.x].type == empty || board[move.to.y][move.to.x].color != board[move.from.y][move.from.x].color));
}

enum bool king_enum_move(struct position *pos, struct move* move)
{
    struct position d = {pos->x - move->to.x, pos->y - move->to.y};

    move->to.x = pos->x;
    move->to.y = pos->y - 1;
    if (!d.y && !d.x)
    {
        if (king_valid_move(*move)) return true;
        d.y = pos->y - move->to.y, d.x = pos->x - move->to.x;
    }

    move->to.x = pos->x + 1;
    move->to.y = pos->y - 1;
    if (d.y == 1 && !d.x)
    {
        if (king_valid_move(*move)) return true;
        d.y = pos->y - move->to.y, d.x = pos->x - move->to.x;
    }

    move->to.x = pos->x + 1;
    move->to.y = pos->y;
    if (d.y == 1 && d.x == -1)
    {
        if (king_valid_move(*move)) return true;
        d.y = pos->y - move->to.y, d.x = pos->x - move->to.x;
    }

    move->to.x = pos->x + 1;
    move->to.y = pos->y + 1;
    if (!d.y && d.x == -1)
    {
        if (king_valid_move(*move)) return true;
        d.y = pos->y - move->to.y, d.x = pos->x - move->to.x;
    }

    move->to.x = pos->x;
    move->to.y = pos->y + 1;
    if (d.y == -1 && d.x == -1)
    {
        if (king_valid_move(*move)) return true;
        d.y = pos->y - move->to.y, d.x = pos->x - move->to.x;
    }

    move->to.x = pos->x - 1;
    move->to.y = pos->y + 1;
    if (d.y == -1 && !d.x)
    {
        if (king_valid_move(*move)) return true;
        d.y = pos->y - move->to.y, d.x = pos->x - move->to.x;
    }

    move->to.x = pos->x - 1;
    move->to.y = pos->y;
    if (d.y == -1 && d.x == 1)
    {
        if (king_valid_move(*move)) return true;
        d.y = pos->y - move->to.y, d.x = pos->x - move->to.x;
    }

    move->to.x = pos->x - 1;
    move->to.y = pos->y - 1;
    if (!d.y && d.x == 1)
    {
        if (king_valid_move(*move)) return true;
        d.y = pos->y - move->to.y, d.x = pos->x - move->to.x;
    }

    return false;
}

weight empty_weight(struct position pos) { return 0; }

enum bool empty_valid_move(struct move move) { return false; }

enum bool empty_enum_move(struct position *pos, struct move *move) {return false;}

void empty_play_move(struct move *move, struct undo *taken,  int *undo_eval) {  }

void undo_move(struct move *move, struct undo *undo, const int *undo_eval)
{
    global_evaluation -= *undo_eval;
    struct square *from = &board[move->from.y][move->from.x], *to = &board[move->to.y][move->to.x];
    *from = *to;
    to->type = undo->taken;
    to->color = !from->color;
}

void generic_play_move(struct move *move, struct undo *undo, int *undo_eval)
{
    struct square *from = &board[move->from.y][move->from.x], *to = &board[move->to.y][move->to.x];
    undo->taken = to->type;
    *to = *from;
    from->type = empty;
    int eval = piece[undo->taken].weight(move->to);
    if (to->color == black) eval *= -1;
    *undo_eval = eval;
    global_evaluation += eval;
}

struct piece piece[] =
        {
                {empty_weight,  empty_valid_move,  empty_play_move,   empty_enum_move},
                {rook_weight,   rook_valid_move,   generic_play_move, rook_enum_move},
                {king_weight, king_valid_move, generic_play_move, king_enum_move}
        };