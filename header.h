#define SIZE 8
enum type { empty, pawn, knight, bishop, rook, queen, king };
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