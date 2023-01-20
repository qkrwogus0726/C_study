#define _CRT_SECURE_NO_WARNINGS
#include "library.h"
#include "string_tools.h"
#define NUM_CHARS 256														//2^8 = 256 → 한 바이트가 가질 수 있는 값의 최대
#define BUFFER_LENGTH 200

Artist* artist_directory[NUM_CHARS];										//아티스트 객체의 주소가 저장되므로 배열의 타입도 아티스트
int num_index = 0;

void insert_node(Artist* ptr_artist, Snode* ptr_snode);
void print_artist(Artist* p);
void print_song(Song* ptr_song);
Artist* find_artist(char* name);

void initialize()															//배열을 만든 후 NULL로 초기화해줘야 함.
{
	for (int i = 0; i < NUM_CHARS; i++)
		artist_directory[i] = NULL;
}

void load(FILE* fp)
{
	char buffer[BUFFER_LENGTH];
	char* name, * title, * path;

	while (1)
	{
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)						//0이라면 데이터 파일의 끝에 도달했다는 것
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

Artist* find_artist(char* name)												//14-4강 27분
{
	Artist* p = artist_directory[(unsigned char)name[0]];					//first artist with initial name[0].
	/*
	name[0]가 가질 수 있는 값은 00000000~11111111
	이 값을 배열 index로 쓰면 정수로 인식함.
	
	첫 비트가 1인 경우, 그냥 signed int로 변환하면 첫 비트가 부호를 의미하므로 앞의 비트를 다 1로 치환한다.
	11001111 → 1111111111111111111111111001111
	그래서 먼저 Unsigned char로 바꿔야 함. 그 다음 int로 변환해야 0~255 값의 정수로 변환됨.
	*/
	while (p != NULL && strcmp(p->name, name) < 0)							
		p = p->next;

	if (p != NULL && strcmp(p->name, name) == 0)
		return p;
	else
		return NULL;
}

Artist* create_artist_instance(char* name)									//artist 생성 함수
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
	
	if (p == NULL && q == NULL)												//유일한 노드인 경우
	{
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else if (q == NULL)														//맨 앞에 삽입하는 경우
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

void insert_node(Artist* ptr_artist, Snode* ptr_snode)						//ptr_artist의 이중연결리스트에 snode 삽입하는 함수
{
	Snode* p = ptr_artist->head;											//node 전체 트레버스할 때는 p를 만들어서 head로 만들어놔야 함.
	while (p != NULL && strcmp(p->song->title, ptr_snode->song->title)<0)	//ordered 되어있는 배열 안에서 찾는 것임. s1이 크면 양수, s2가 크면 음수 리턴
		p = p->next;														//(p가 가리키는 title) < (삽입하려는 snode의 title) 일 때 p = p->next 
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

void status()																//프로그램의 모든 데이터 출력
{
	for (int i = 0; i < NUM_CHARS; i++)
	{
		Artist* p = artist_directory[i];								//artist_directory[i]가 거느리고 있는 단방향 연결리스트의 head node의 주소(첫번째 노드의 주소)
		while (p != NULL)
		{
			print_artist(p);
			p = p->next;
		}
	}
}

void print_artist(Artist* p)												//특정 artist의 주소 p 를 받는다
{
	printf("%s\n", p->name);												//artist 이름 출력
	Snode* ptr_snode = p->head;												//ptr_snode는 해당 artist의 첫번째 snode
	while (ptr_snode != NULL)
	{
		print_song(ptr_snode->song);										//Song 출력하는 함수 호출
		ptr_snode = ptr_snode->next;										//이중연결리스트 순회
	}
}

void print_song(Song* ptr_song)												//Song 인자들 모두 출력
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
	
	Snode* ptr_snode = ptr_artist->head;									//ptr_artist->head 가 첫번째 Snode의 주소임.
	while (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0)	//ptr_snode의 title이 찾고자하는 title보다 작은 경우 ptr_snode = ptr_snode
		ptr_snode = ptr_snode;										//->next 해야하는거 아닌지?
	
	if (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) == 0)
		print_song(ptr_snode->song);
	else
	{
		printf("No such song exists.\n");
		return;
	}

}

//void search_song(char* artist)
//{
//
//}

void add_song(char* artist, char* title, char* path)
{
	//find if the artist already exists.

	Artist* ptr_artist = find_artist(artist);								//artist를 찾는데, 만약에 없으면 add_artist로 추가함
	if (ptr_artist == NULL)
	{
		ptr_artist = add_artist(artist);
	}

	Song* ptr_song = create_song_instance(ptr_artist, title, path);			//artist가 존재한다면 song 객체 생성
	Snode* ptr_snode = (Snode*)malloc(sizeof(Snode));						//song은 Snode 객체에 달려있으니 snode부터 생성 후 그 안에 song 대입
	ptr_snode->song = ptr_song;
	ptr_snode->next = NULL;
	ptr_snode->prev = NULL;

	insert_node(ptr_artist, ptr_snode);										//snode를 ptr_artist에 대입
}