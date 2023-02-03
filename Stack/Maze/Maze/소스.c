#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"
#include "pos.h"

#define MAX 100
#define PATH 0			//지나갈 수 없는 위치
#define WALL 1			//지나갈 수 있는 위치
#define VISITED 2		//이미 방문한 위치
#define BACKTRACKED 3	//방문했다가 되돌아 나온 위치

int maze[MAX][MAX];
int n;

void read_maze();
void print_maze();
bool movable(Position pos, int dir);

bool movable(Position pos, int dir)				//dir 방향으로 이동하는 게 가능한지 검사
{
	Position temp;

	if (pos.x == NULL || pos.y == NULL)
		return true;

	temp.x = pos.x + dir;
	temp.y = pos.y + dir;

	if (maze[temp.x][temp.y] == 1)
		return false;
	else
		return true;

}

int main()
{
	read_maze();

	Stack s = create();
	Position cur;					//현재 위치
	cur.x = 0;
	cur.y = 0;

	while (1)
	{
		maze[cur.x][cur.y] = VISITED;
		if (cur.x == n - 1 && cur.y == n - 1)
		{
			printf("Found the path.\n");
			break;
		}

		bool forwarded = false;										//전진 성공 or 실패
		for (int dir = 0; dir < 4; dir++)							//0 : North / 1:East / 2:South / 3:West
		{
			if (movable(cur, dir))
			{
				push(s, cur);
				cur = move_to(cur, dir);
				forwarded = true;
				break;
			}
		}
		if (!forwarded)
		{
			maze[cur.x][cur.y] = BACKTRACKED;
			if (is_empty(s))
			{
				printf("No path exists.\n");
				break;
			}
			else cur = pop(s);
		}
	}
	print_maze();
}