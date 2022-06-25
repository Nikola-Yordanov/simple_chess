#include "header.h"

uint32_t MOD(int a) { return a < 0 ? -a : a;}
int MAX(int a, int b) { return a > b ? a : b;}

weight king_rook_mate(enum color color)
{
    uint32_t white_pieces = 0, black_pieces = 0;
    struct position white_king_pos, black_king_pos;

    for(int y = 0;y < SIZE;y++)
        for(int x = 0;x < SIZE;x++)
        {
            if(board[y][x].type == empty)
                continue;

             white_pieces += board[y][x].color == white;
             black_pieces += board[y][x].color == black;

            if(board[y][x].type == king && board[y][x].color == white)
                white_king_pos = (struct position ){x, y};

            else if(board[y][x].type == king && board[y][x].color == black)
                black_king_pos = (struct position ){x, y};
        }

    int eval = 0;

    if( (color == white && white_pieces > 1 && black_pieces == 1) ||
        (color == black && black_pieces > 1 && white_pieces == 1) )
    {
        struct position enemy_king_pos = color == white ? black_king_pos : white_king_pos;

        uint32_t dst_btw_kings = MOD(white_king_pos.x - black_king_pos.x ) + MOD(white_king_pos.y - black_king_pos.y),
        enemy_king_dist_x = MAX(3 - enemy_king_pos.x, enemy_king_pos.y - 4),
        enemy_king_dist_y = MAX(3 - enemy_king_pos.y, enemy_king_pos.y - 4),
        enemy_king_dist_center = enemy_king_dist_x + enemy_king_dist_y;

        eval += 14 - dst_btw_kings + enemy_king_dist_center;

    }

    return 10 * eval;
}