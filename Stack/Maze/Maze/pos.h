#ifndef POS_H
#define POS_H
#pragma once

typedef struct pos
{
	int x, y;
}Position;

int offset[4][2] = { {-1, 0}, {0,1}, {1,0}, {0, -1} };

Position move_to(Position pos, int dir);

#endif POS_H