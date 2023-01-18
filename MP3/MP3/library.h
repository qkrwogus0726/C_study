#ifndef LIBRARY_H
#define LIBRARY_H

#include <string.h>
#include <stdlib.h>

typedef struct song Song;
typedef struct snode Snode;
typedef struct artist Artist;

struct song
{
	Artist* artist;
	char* title;
	char* path;
	int index;
};

struct snode
{
	struct snode* next, * prev;
	Song* song
};

struct artist
{
	char *name;
	struct artist* next;
	Snode* head;
	Snode* tail;
};


void initialize();
void add_song(char* artist, char* title, char* path);

#endif