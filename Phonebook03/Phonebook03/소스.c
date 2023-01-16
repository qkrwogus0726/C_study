#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 100
#define INIT_CAPACITY 100
#define BUFFER_SIZE 100

typedef struct person
{
	char* name;
	char* number;
	char* email;
	char* group;
}Person;

Person **directory;
int capacity;
int n;

char delim[] = " ";

void init()
{
	directory = (Person**)malloc(INIT_CAPACITY * sizeof(Person*)); //각 배열 요소는 Person*임. 그게 INIT_CAPACITY만큼 있음.
	capacity = INIT_CAPACITY;
	n = 0;
}

int read_line(FILE* fp, char str[], int n) //파일명, 읽은거 저장할 값, 배열의 크기
{
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF) //getchar -> fgetc
	{
		if (i < n) //오버플로우가 생기지 않게 하는 i<n
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

void add(char* name, char* number, char* email, char* group)
{
	if (n >= capacity) //저장된 사람 수가 배열의 크기보다 크거나 같음. 꽉찼다는 의미
		reallocate();

	int i = n - 1;
	while (i >= 0 && strcmp(directory[i]->name, name) > 0)
	{
		directory[i + 1] = directory[i];
		i--;
	}

	directory[i + 1] = (Person*)malloc(sizeof(Person)); //새로운 사람을 넣을 공간 확보

	directory[i + 1]->name = name; //입력 안 한 항목은 하나의 공백문자로 저장됨
	directory[i + 1]->number = number;
	directory[i + 1]->email = email;
	directory[i + 1]->group = group;
	n++;
}

void handle_add(char* name) //이름 받은 후 전화번호, 이메일, 그룹 받는 함수
{
	char number[BUFFER_SIZE], email[BUFFER_SIZE], group[BUFFER_SIZE];
	char empty[] = " ";

	printf("  Phone: ");
	read_line(stdin, number, BUFFER_SIZE);
	printf("  Email: ");
	read_line(stdin, email, BUFFER_SIZE);
	printf("  Group: ");
	read_line(stdin, group, BUFFER_SIZE);

	add(name, (char*)(strlen(number) > 0 ? number : empty),
		(char*)(strlen(email) > 0 ? email : empty),
		(char*)(strlen(group) > 0 ? group : empty)); // 존재하지 않는 항목들을 하나의 공백문자 문자열로 대체함.
}

void status()
{
	int i;
	for (i = 0; i < n; i++)
	{
		print_person(directory[i]);
	}
	printf("Total %d persons.\n", n);
}

void find(char* name)
{
	int index = search(name);
	if (index == -1)
	{
		printf("No person names '%s' exists.\n", name);
	}
	else print_person(directory[index]);
}

void remove(char* name)
{
	int i = search(name);
	if (i == -1)
	{
		printf("No person named '%s' exists.\n", name);
		return;
	}
	int j = i;
	for (; j < n - 1; j++)
	{
		directory[j] = directory[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully.\n", name);
}

void release_person(Person* p)
{
	free(p->name);
	if (p->number != NULL) free(p->number);
	if (p->email != NULL) free(p->email);
	if (p->group != NULL) free(p->group);
	free(p);
}

int search(char* name)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (strcmp(name, directory[i].name) == 0)
		{
			return i;
		}
	}
	return -1;
}

void print_person(Person *p)
{
	printf("%s: \n", p->name);
	printf("   Phone: %s\n", p->number);
	printf("   Email: %s\n", p->email);
	printf("   Group: %s\n", p->group);
}

void reallocate()
{
	int i;
	capacity *= 2; //반드시 2배 할 필요는 없음.
	Person** tmp = (Person**)malloc(capacity * sizeof(Person*)); //구조체의 배열을 사용했을 때 reallocate를 하면 값이 왔다갔다 하는게 아니라
	                                                             //값의 주소들만 왔다갔다 하기 때문에 더 효율적임.
	for (i = 0; i < n; i++)
		tmp[i] = directory[i];
	free(directory);
	directory = tmp;
}

void load(char* fileName)
{
	char buffer[BUFFER_SIZE];
	char* name, * number, * email, * group;
	char* token;

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}
	while (1)
	{
		if (read_line(fp, buffer, BUFFER_SIZE) <= 0)
			break;
		name = strtok(buffer, "#");
		token = strtok(NULL, "#");

		if (strcmp(token, " ") == 0)
			number = NULL;
		else
			number = strdup(token);
		token = strtok(NULL, "#");

		if (strcmp(token, " ") == 0)
			email = NULL;
		else
			email = strdup(token);

		if (strcmp(token, " ") == 0)
			group = NULL;
		else
			group = strdup(token);
		add(strdup(name), number, email, group);
	}
	fclose(fp);
}

void save(char* filename)
{
	int i;
	FILE* fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%s#", directory[i].name);
		fprintf(fp, "%s#", directory[i].number);
		fprintf(fp, "%s#", directory[i].email);
		fprintf(fp, "%s#\n", directory[i].group);
	}
	fclose(fp);
}

void process_command(char filename)
{
	char command_line[BUFFER_SIZE];
	char* command, * argument1, * argument2;
	FILE*fp = fopen(filename, "r");

	while (1)
	{
		printf("$ ");

		if (read_line(fp, command_line, BUFFER_SIZE) <= 0)
			continue;

		command = strtok(command_line, delim);
		if (command == NULL) continue;

		if (strcmp(command, "read") == 0)
		{
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL)
			{
				printf("File name required.\n");
				continue;
			}
			load(argument1);
		}
	}
}

int compose_name(char str[], int limit) //불필요한 공백 제거하는 함수
{
	char* ptr;
	int length = 0;

	ptr = strtok(NULL, " "); //첫번째 토큰은 command 이니까 두번째부터 읽어와야 함.
	if (ptr == NULL)
		return 0;

	strcpy(str, ptr); //이름의 여러 단어 중 첫 단어를 str에 넣는다
	length += strlen(ptr); //이름의 길이 = 첫번째 토큰의 길이

	while ((ptr = strtok(NULL, " ")) != NULL) // 이름이 여러 단어로 돼있을 수 있으니까 while문 돌려서
	{
		if (length + strlen(ptr) + 1 < limit) //length : 이전에 써놓은 단어의 길이 , strlen(ptr) : 새로운 토큰의 길이. 둘을 더했을 때 limit보다 크면 overflow
		{                                     //이름의 길이가 너무 길어서 buffer_size를 초과하는 경우를 막기 위함.
			str[length++] = ' '; // 이름과 이름 사이에 한 칸의 공백이 필요하므로 공백 삽입
			str[length] = '\0';
			strcat(str, ptr); //strcat은 두 단어가 \0로 끝난다는 가정 하에 정상 작동함.
			length += strlen(ptr);
		}
	}
	return length;
}

int main(void)
{
	char command_line[BUFFER_SIZE];
	char* command, * argument;
	char name_str[BUFFER_SIZE];

	INIT_CAPACITY

	while (1)
	{
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_SIZE) <= 0) //read_line은 자신이 읽은 문자 수를 리턴하는데, 그게 0보다 작으면 사용자가 아무것도 입력하지 않고 enter 한 것
			continue;

		command = strtok(command_line, " ");

		if (strcmp(command, "read") == 0)
		{
			argument = strtok(NULL, " ");
			if (argument == NULL) // 사용자가 파일 이름을 지정하지 않고 넘어간 것
			{
				printf("Invalid arguments.\n");
				continue;
			}
			load(argument); // 잘 입력했으면 load
		}
		else if (strcmp(command, "add") == 0)
		{
			if (compose_name(name_str, BUFFER_SIZE) <= 0)
			{
				printf("Name required.\n");
				continue;
			}
			handle_add(name_str);
		}
		else if (strcmp(command, "find") == 0)
		{
			if (compose_name(name_str, BUFFER_SIZE) <= 0)
			{
				printf("Name required.\n");
				continue;
			}
			find(name_str);
		}
		else if (strcmp(command, "status") == 0)
		{
			status;
		}
		else if (strcmp(command, "delete") == 0)
		{
			if (compose_name(name_str, BUFFER_SIZE) <= 0)
			{
				printf("Invalid arguments.\n");
				continue;
			}
			remove(name_str);
		}
	}
	return 0;
}