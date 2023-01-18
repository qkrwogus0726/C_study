#include "library.h"
#define NUM_CHARS 256												//2^8 = 256 → 한 바이트가 가질 수 있는 값의 최대

Artist* artist_directory[NUM_CHARS];								//아티스트 객체의 주소가 저장되므로 배열의 타입도 아티스트

void initialize()													//배열을 만든 후 NULL로 초기화해줘야 함.
{
	for (int i = 0; i < NUM_CHARS; i++)
		artist_directory[i] = NULL;
}

Artist* find_artist(char* name)
{
	Artist* p = artist_directory[(unsigned char)name[0]];			//first artist with initial name[0]. unsigned char에 대한 설명이 있긴 한데...
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