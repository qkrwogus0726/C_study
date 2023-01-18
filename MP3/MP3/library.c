#include "library.h"
#define NUM_CHARS 256												//2^8 = 256 �� �� ����Ʈ�� ���� �� �ִ� ���� �ִ�

Artist* artist_directory[NUM_CHARS];								//��Ƽ��Ʈ ��ü�� �ּҰ� ����ǹǷ� �迭�� Ÿ�Ե� ��Ƽ��Ʈ

void initialize()													//�迭�� ���� �� NULL�� �ʱ�ȭ����� ��.
{
	for (int i = 0; i < NUM_CHARS; i++)
		artist_directory[i] = NULL;
}

Artist* find_artist(char* name)
{
	Artist* p = artist_directory[(unsigned char)name[0]];			//first artist with initial name[0]. unsigned char�� ���� ������ �ֱ� �ѵ�...
	while (p != NULL && strcmp(p->name, name) < 0)
		p = p->next;

	if (p != NULL && strcmp(p->name, name) == 0)
		return p;
	else
		return NULL;
}

void add_song(char* artist, char* title, char* path)
{
	//find if the artist already exists.

	Artist* ptr_artist = find_artist(artist);						//return NULL if not

	if (ptr_artist == NULL)
	{

	}
	else
	{

	}

}