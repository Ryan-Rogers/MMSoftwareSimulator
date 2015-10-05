#include <stdio.h>
#include <stdlib.h>

typedef unsigned char U8;

typedef struct
{
    U8    Xpos : 4; //LSB
    U8    Ypos : 4; //MSB
} _pos;

typedef union
{
    struct
    {
        U8    n :1; // North traveled   //LSB
        U8    s :1; // South traveled
        U8    e :1; // East traveled
        U8    w :1; // West traveled
        U8    nw :1; // North wall
        U8    sw :1; // South wall
        U8    ew :1; // East wall
        U8    ww :1; // West wall       //MSb
    } posBits;
    
    struct
    {
        U8    Knowledge:4; // Lo
        U8    Walls:4; // Hi
    } bulk;
    
    U8 Raw;
} _maze_data;

typedef struct
{
    _pos coord;
    unsigned int nextMoveIndex;
} _move;

int main(void)
{
    _maze_data map[16][16];
    //map[0][0].posBits.n = 1;
    
    // If nextMove has knowledge, it must be part of a loop
    _move moveList[300];
    
    map[0][0].Raw = 0xCB;
    printf("test pos.Raw: %02X\r\n", map[0][0].Raw);
    printf("test pos.Knowledge: %01X\r\n", map[0][0].bulk.Knowledge);
    printf("test pos.Walls: %01X\r\n", map[0][0].bulk.Walls);
    
    printf("Raw: %01X%01X%01X%01X%01X%01X%01X%01X\r\n", (map[0][0].Raw >> 7) & 1,
    (map[0][0].Raw >> 6) & 1,
    (map[0][0].Raw >> 5) & 1,
    (map[0][0].Raw >> 4) & 1,
    (map[0][0].Raw >> 3) & 1,
    (map[0][0].Raw >> 2) & 1,
    (map[0][0].Raw >> 1) & 1,
    (map[0][0].Raw ) & 1    );
    
    
    
    printf("test pos.n: %d\r\n", map[0][0].posBits.n);
    printf("test pos.s: %d\r\n", map[0][0].posBits.s);
    printf("test pos.e: %01X\r\n", map[0][0].posBits.e);
    printf("test pos.w: %01X\r\n", map[0][0].posBits.w);
    
    
    printf("test pos.nw: %d\r\n", map[0][0].posBits.nw);
    printf("test pos.sw: %d\r\n", map[0][0].posBits.sw);
    printf("test pos.ew: %01X\r\n", map[0][0].posBits.ew);
    printf("test pos.ww: %01X\r\n", map[0][0].posBits.ww);
    
    
}





