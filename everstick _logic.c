#include "header.h"
#include <stdio.h>
int max( int a, int b) { return  a > b ?  a : b; }
unsigned mod_(int a) { return a < 0 ? -a : a; }

int king_rook_mate(enum color on_move)
{

    struct position white_king, black_king;
    int white_color_piece = 0, black_color_piece = 0;

    for(int y = 0;y < SIZE;y++)
    {
        for(int x = 0;x < SIZE;x++)
        {
            if(board[y][x].type == king && board[y][x].color == white)
                white_king.x = x, white_king.y = y;

             if(board[y][x].type == king && board[y][x].color == black)
                 black_king.x = x, black_king.y = y;

             if(board[y][x].type != empty)
                 board[y][x].color ? white_color_piece++ : black_color_piece++;
        }
    }

    if((on_move == black && black_color_piece == 1 && white_color_piece > 1) ||
       (on_move == white && white_color_piece == 1 && black_color_piece > 1)) {

        struct position enemy_king = on_move == white ? black_king : white_king;

        unsigned dist_btw_kings = mod_(black_king.x - white_king.x) + mod_(black_king.y - white_king.y),
                 enemy_king_center_x_dist = max(3 - enemy_king.x, enemy_king.x  - 4),
                 enemy_king_center_y_dist = max(3 - enemy_king.y, enemy_king.y  - 4),
                 enemy_king_dist_from_center = enemy_king_center_x_dist + enemy_king_center_y_dist,
                evaluation = SIZE - dist_btw_kings + enemy_king_dist_from_center;

        return evaluation;
    }

    return 0;
}