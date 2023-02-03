#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"
#include "pos.h"

#define MAX 100
#define PATH 0			//������ �� ���� ��ġ
#define WALL 1			//������ �� �ִ� ��ġ
#define VISITED 2		//�̹� �湮�� ��ġ
#define BACKTRACKED 3	//�湮�ߴٰ� �ǵ��� ���� ��ġ

int maze[MAX][MAX];
int n;

void read_maze();
void print_maze();
bool movable(Position pos, int dir);

bool movable(Position pos, int dir)				//dir �������� �̵��ϴ� �� �������� �˻�
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
	Position cur;					//���� ��ġ
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

		bool forwarded = false;										//���� ���� or ����
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