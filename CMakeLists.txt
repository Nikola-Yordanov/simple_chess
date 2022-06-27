cmake_minimum_required(VERSION 3.21)
project(chess_rook_king C)

set(CMAKE_C_STANDARD 99)

add_executable(chess_rook_king main.c header.h chess.c min_max.c chess_functionality.c "everstick _logic.c" hash_map.c)
