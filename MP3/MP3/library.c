#define _CRT_SECURE_NO_WARNINGS
#include "library.h"
#include "string_tools.h"
#include <Windows.h>

#define NUM_CHARS 256														//2^8 = 256 �� �� ����Ʈ�� ���� �� �ִ� ���� �ִ�
#define BUFFER_LENGTH 200
#define SIZE_INDEX_TABLE 100

Artist* artist_directory[NUM_CHARS];										//��Ƽ��Ʈ ��ü�� �ּҰ� ����ǹǷ� �迭�� Ÿ�Ե� ��Ƽ��Ʈ
int num_index = 0;
Snode* index_directory[SIZE_INDEX_TABLE];

void insert_node(Artist* ptr_artist, Snode* ptr_snode);
void print_artist(Artist* p);
void print_song(Song* ptr_song);
Artist* find_artist(char* name);
Snode* find_snode(Artist* ptr_artist, char* title);
void insert_to_index_directory(Song* ptr_song);
void save_artist(Artist* p, FILE* fp);
void save_song(Song* ptr_song, FILE* fp);
void destroy_song(Song* ptr_song);
void remover(int index);
void remove_snode(Artist* ptr_artist, Snode* ptr_snode);

void initialize()															//�迭�� ���� �� NULL�� �ʱ�ȭ����� ��.
{
	for (int i = 0; i < NUM_CHARS; i++)
		artist_directory[i] = NULL;
	for (int i = 0; i < SIZE_INDEX_TABLE; i++)
		index_directory[i] = NULL;
}

void insert_to_index_directory(Song* ptr_song)
{
	Snode* ptr_snode = (Snode*)malloc(sizeof(Snode));
	ptr_snode->song = ptr_song;
	ptr_snode->next = NULL;
	ptr_snode->prev = NULL;

	int index = ptr_song->index% SIZE_INDEX_TABLE;							//insert the snode into the single linked list at index_table[index]
	
	Snode* p = index_directory[index];
	Snode* q = NULL;
	while (p != NULL && strcmp(p->song->title, ptr_song->title) < 0)
	{
		q = p;
		p = p->next;
	}
	if (q == NULL)															//add first
	{
		ptr_snode->next = p;												//���� head node�� p�̱� ����
		index_directory[index] = ptr_snode;
	}
	else
	{
		ptr_snode->next = p;												//add after q
		q->next = ptr_snode;
	}
}

void load(FILE* fp)
{
	char buffer[BUFFER_LENGTH];
	char* name, * title, * path;

	while (1)
	{
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)						//0�̶�� ������ ������ ���� �����ߴٴ� ��
			break;

		name = strtok(buffer, "#");
		if (strcmp(name, " ") == 0)
			name = NULL;
		else
			name = _strdup(name);

		title = strtok(NULL, "#");
		if (strcmp(title, " ") == 0)
			title = NULL;
		else
			title = _strdup(title);

		path = strtok(NULL, "#");
		if (strcmp(path, " ") == 0)
			path = NULL;
		else
			path = _strdup(path);

		add_song(name, title, path);
	}
}

Artist* find_artist(char* name)												//14-4�� 27��
{
	Artist* p = artist_directory[(unsigned char)name[0]];					//first artist with initial name[0].
	/*
	name[0]�� ���� �� �ִ� ���� 00000000~11111111
	�� ���� �迭 index�� ���� ������ �ν���.
	
	ù ��Ʈ�� 1�� ���, �׳� signed int�� ��ȯ�ϸ� ù ��Ʈ�� ��ȣ�� �ǹ��ϹǷ� ���� ��Ʈ�� �� 1�� ġȯ�Ѵ�.
	11001111 �� 1111111111111111111111111001111
	�׷��� ���� Unsigned char�� �ٲ�� ��. �� ���� int�� ��ȯ�ؾ� 0~255 ���� ������ ��ȯ��.
	*/
	while (p != NULL && strcmp(p->name, name) < 0)							
		p = p->next;

	if (p != NULL && strcmp(p->name, name) == 0)
		return p;
	else
		return NULL;
}

Artist* create_artist_instance(char* name)									//artist ���� �Լ�
{
	Artist* ptr_artist = (Artist*)malloc(sizeof(Artist));
	ptr_artist->name = name;
	ptr_artist->head = NULL;
	ptr_artist->tail = NULL;
	ptr_artist->next = NULL;
	return ptr_artist;
}


Artist* add_artist(char* name)
{
	Artist* ptr_artist = create_artist_instance(name);
	
	Artist* p = artist_directory[(unsigned char)name[0]];
	Artist* q = NULL;

	while (p != NULL && strcmp(p->name, name) < 0)
	{
		q = p;
		p = p->next;
	}
	
	if (p == NULL && q == NULL)												//������ ����� ���
	{
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else if (q == NULL)														//�� �տ� �����ϴ� ���
	{
		ptr_artist->next = artist_directory[(unsigned char)name[0]];
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else																	//add_after(q)
	{
		ptr_artist->next = p;
		q->next = ptr_artist;
	}
	return ptr_artist;
}

Song* create_song_instance(Artist* ptr_artist, char* title, char* path)
{
	Song* ptr_song = (Song*)malloc(sizeof(Song));
	ptr_song->artist = ptr_artist;
	ptr_song->title = title;
	ptr_song->path = path;
	ptr_song->index = num_index;
	num_index++;

	return ptr_song;
}

void insert_node(Artist* ptr_artist, Snode* ptr_snode)						//ptr_artist�� ���߿��Ḯ��Ʈ�� snode �����ϴ� �Լ�
{
	Snode* p = ptr_artist->head;											//node ��ü Ʈ�������� ���� p�� ���� head�� �������� ��.
	while (p != NULL && strcmp(p->song->title, ptr_snode->song->title)<0)	//ordered �Ǿ��ִ� �迭 �ȿ��� ã�� ����. s1�� ũ�� ���, s2�� ũ�� ���� ����
		p = p->next;														//(p�� ����Ű�� title) < (�����Ϸ��� snode�� title) �� �� p = p->next 
																			//before p
	if (ptr_artist->head == NULL)											//case 1. empty 36:34
	{
		ptr_artist->head = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else if (p == ptr_artist->head)											//case 2. at the front
	{
		ptr_snode->next = ptr_artist->head;
		ptr_artist->head->prev = ptr_snode;
		ptr_artist->head = ptr_snode;
	}
	else if (p == NULL)														//case 3. at the end
	{
		ptr_snode->prev = ptr_artist->tail;
		ptr_artist->tail->next = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else																	//case 4. in the middle. (= before p)
	{
		ptr_snode->next = p;
		ptr_snode->prev = p->prev;
		p->prev->next = ptr_snode;
		p->prev = ptr_snode;
	}

}

void status()																//���α׷��� ��� ������ ���
{
	for (int i = 0; i < NUM_CHARS; i++)
	{
		Artist* p = artist_directory[i];								//artist_directory[i]�� �Ŵ����� �ִ� �ܹ��� ���Ḯ��Ʈ�� head node�� �ּ�(ù��° ����� �ּ�)
		while (p != NULL)
		{
			print_artist(p);
			p = p->next;
		}
	}
}

void print_artist(Artist* p)												//Ư�� artist�� �ּ� p �� �޴´�
{
	printf("%s\n", p->name);												//artist �̸� ���
	Snode* ptr_snode = p->head;												//ptr_snode�� �ش� artist�� ù��° snode
	while (ptr_snode != NULL)
	{
		print_song(ptr_snode->song);										//Song ����ϴ� �Լ� ȣ��
		ptr_snode = ptr_snode->next;										//���߿��Ḯ��Ʈ ��ȸ
	}
}

void print_song(Song* ptr_song)												//Song ���ڵ� ��� ���
{
	printf("   %d : %s, %s\n", ptr_song->index, ptr_song->title, ptr_song->path);
}

void search_song(char* artist, char* title)
{
	Artist* ptr_artist = find_artist(artist);
	if (ptr_artist == NULL)
	{
		printf("No such artist exists.\n");
		return;
	}

	Snode* ptr_snode = find_snode(ptr_artist, title);

	if (ptr_snode != NULL)
	{
		printf("Found: \n");
		print_song(ptr_snode->song);
	}
	else 
	{
		printf("No such song exists.\n");
		return;
	}

}

Snode* find_snode(Artist* ptr_artist, char* title)
{
	Snode* ptr_snode = ptr_artist->head;
	while (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0)
		ptr_snode = ptr_snode;

	if (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) == 0)
		return ptr_snode;
	else
		return NULL;
}

void search_song_one(char* artist)
{
	Artist* ptr_artist = find_artist(artist);
	if (ptr_artist == NULL)
	{
		printf("No such artist exists.\n");
		return;
	}
	printf("Found: \n");
	print_artist(ptr_artist);
}

void add_song(char* artist, char* title, char* path)
{
	//find if the artist already exists.

	Artist* ptr_artist = find_artist(artist);								//artist�� ã�µ�, ���࿡ ������ add_artist�� �߰���
	if (ptr_artist == NULL)
	{
		ptr_artist = add_artist(artist);
	}

	Song* ptr_song = create_song_instance(ptr_artist, title, path);			//artist�� �����Ѵٸ� song ��ü ����
	Snode* ptr_snode = (Snode*)malloc(sizeof(Snode));						//song�� Snode ��ü�� �޷������� snode���� ���� �� �� �ȿ� song ����
	ptr_snode->song = ptr_song;
	ptr_snode->next = NULL;
	ptr_snode->prev = NULL;

	insert_node(ptr_artist, ptr_snode);										//snode�� ptr_artist�� ����
	insert_to_index_directory(ptr_song);
}

Snode* find_song(int index)
{
	Snode* ptr_snode = index_directory[index % SIZE_INDEX_TABLE];
	while (ptr_snode != NULL && ptr_snode->song->index != index)
		ptr_snode = ptr_snode->next;

	return ptr_snode;
}

void play(int index)
{
	Snode* ptr_snode = find_song(index);
	if (ptr_snode == NULL)
	{
		printf("No such song exists.\n");
		return;
	}
	printf("Found the song: %s\n", ptr_snode->song->title);
	printf("\n");

	ShellExecute(GetDesktopWindow(), "open", ptr_snode->song->path, NULL, NULL, SW_SHOW);
}

void save(FILE* fp)
{
	for (int i = 0; i < NUM_CHARS; i++)
	{
		Artist* p = artist_directory[i];
		while (p != NULL)
		{
			save_artist(p, fp);
			p = p->next;
		}
	}
}

void save_artist(Artist* p, FILE* fp)
{
	Snode* ptr_snode = p->head;												//ptr_snode�� �ش� artist�� ù��° snode
	while (ptr_snode != NULL)
	{
		save_song(ptr_snode->song, fp);										//Song ����ϴ� �Լ� ȣ��
		ptr_snode = ptr_snode->next;										//���߿��Ḯ��Ʈ ��ȸ
	}
}

void save_song(Song* ptr_song, FILE* fp)
{
	if (ptr_song->artist != NULL)
		fprintf(fp, "%s#", ptr_song->artist->name);
	else
		fprintf(fp, " #");

	fprintf(fp, "%s#", ptr_song->artist->name);
	if (ptr_song->title != NULL)
	{
		fprintf(fp, "%s#", ptr_song->title);
	}
	else
		fprintf(fp, " #\n");

	if (ptr_song->path != NULL)
		fprintf(fp, "%s#\n", ptr_song->path);
	else
		fprintf(fp, " #\n");
}

void remover(int index)
{
	Snode* q = NULL;
	Snode* ptr_snode = index_directory[index % SIZE_INDEX_TABLE];
	while (ptr_snode != NULL && ptr_snode->song->index != index)
		q = ptr_snode;
		ptr_snode = ptr_snode->next;

	if (ptr_snode == NULL)													//empty list �̰ų�, �뷡�� �������� �ʴ� ���
	{
		printf("No such song exists.\n");
		return;
	}

	Song* ptr_song = ptr_snode->song;

	if (q == NULL)															//ù��° ��带 �����ϴ� ���
	{
		index_directory[index % SIZE_INDEX_TABLE] = ptr_snode->next;

	}
	else																	//q ���� ��带 �����ϴ� ���
	{
		q->next = ptr_snode->next;

	}
	free(ptr_snode);

	Artist* ptr_artist = ptr_song->artist;

	Snode* p = find_snode(ptr_artist, ptr_song->title);
	if (p == NULL)
	{
		printf("No found snode - something wrong.\n");
		return;
	}
	remove_snode(ptr_artist, p);
	destroy_song(ptr_song);
}

void destroy_song(Song* ptr_song)
{
	if (ptr_song->title != NULL)
		free(ptr_song->title);
	if (ptr_song->path != NULL)
		free(ptr_song->path);
	free(ptr_song);

}

void remove_snode(Artist* ptr_artist, Snode* ptr_snode)
{
	Snode* first = ptr_artist->head;
	Snode* last = ptr_artist->tail;

	if (first == ptr_snode && last == ptr_snode)							//������ ��带 �����ϴ� ���
	{

	}
	else if (first == ptr_snode)											//ù��° ��� ����
	{

	}
	else if (last == ptr_snode)												//������ ��� ����
	{

	}
	else																	//�߰��� ��� ����
	{

	}
	free(ptr_snode);
}