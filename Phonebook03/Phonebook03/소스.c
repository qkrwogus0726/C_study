#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 100
#define BUFFER_SIZE 100

typedef struct person
{
	char* name;
	char* number;
	char* email;
	char* group;
}Person;

Person directory[CAPACITY];

int n = 0;

char delim[] = " ";

int read_line(FILE* fp, char str[], int n) //���ϸ�, ������ ������ ��, �迭�� ũ��
{
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF) //getchar -> fgetc
	{
		if (i < n) //�����÷ο찡 ������ �ʰ� �ϴ� i<n
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

void add(char* name, char* number, char* email, char* group)
{
	int i = n - 1;
	while (i >= 0 && strcmp(directory[i].name, name) > 0)
	{
		directory[i + 1] = directory[i];
		i--;
	}
	directory[i + 1].name = _strdup(name); //�Է� �� �� �׸��� �ϳ��� ���鹮�ڷ� �����
	directory[i + 1].number = _strdup(number);
	directory[i + 1].email = _strdup(email);
	directory[i + 1].group = _strdup(group);
	n++;
}

void handle_add(char* name) //�̸� ���� �� ��ȭ��ȣ, �̸���, �׷� �޴� �Լ�
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
		(char*)(strlen(group) > 0 ? group : empty)); // �������� �ʴ� �׸���� �ϳ��� ���鹮�� ���ڿ��� ��ü��.
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

void print_person(Person p)
{
	printf("%s: \n", p.name);
	printf("   Phone: %s\n", p.number);
	printf("   Email: %s\n", p.email);
	printf("   Group: %s\n", p.group);
}

//void reallocate()
//{
//	int i;
//	capacity *= 2; //�ݵ�� 2�� �� �ʿ�� ����.
//	char** tmp1 = (char**)malloc(capacity * sizeof(char*));
//	char** tmp2 = (char**)malloc(capacity * sizeof(char*));
//
//	for (i = 0; i < n; i++)
//	{
//		tmp1[i] = names[i];
//		tmp2[i] = numbers[i];
//	}
//	free(names);
//	free(numbers);
//
//	names = tmp1;
//	numbers = tmp2;
//}

void load(char* fileName)
{
	char buffer[BUFFER_SIZE];
	char* name, * number, * email, * group;

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
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group = strtok(NULL, "#");
		add(name, number, email, group);
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

int compose_name(char str[], int limit) //���ʿ��� ���� �����ϴ� �Լ�
{
	char* ptr;
	int length = 0;

	ptr = strtok(NULL, " "); //ù��° ��ū�� command �̴ϱ� �ι�°���� �о�;� ��.
	if (ptr == NULL)
		return 0;

	strcpy(str, ptr); //�̸��� ���� �ܾ� �� ù �ܾ str�� �ִ´�
	length += strlen(ptr); //�̸��� ���� = ù��° ��ū�� ����

	while ((ptr = strtok(NULL, " ")) != NULL) // �̸��� ���� �ܾ�� ������ �� �����ϱ� while�� ������
	{
		if (length + strlen(ptr) + 1 < limit) //length : ������ ����� �ܾ��� ���� , strlen(ptr) : ���ο� ��ū�� ����. ���� ������ �� limit���� ũ�� overflow
		{                                     //�̸��� ���̰� �ʹ� �� buffer_size�� �ʰ��ϴ� ��츦 ���� ����.
			str[length++] = ' '; // �̸��� �̸� ���̿� �� ĭ�� ������ �ʿ��ϹǷ� ���� ����
			str[length] = '\0';
			strcat(str, ptr); //strcat�� �� �ܾ \0�� �����ٴ� ���� �Ͽ� ���� �۵���.
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

	while (1)
	{
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_SIZE) <= 0) //read_line�� �ڽ��� ���� ���� ���� �����ϴµ�, �װ� 0���� ������ ����ڰ� �ƹ��͵� �Է����� �ʰ� enter �� ��
			continue;

		command = strtok(command_line, " ");

		if (strcmp(command, "read") == 0)
		{
			argument = strtok(NULL, " ");
			if (argument == NULL) // ����ڰ� ���� �̸��� �������� �ʰ� �Ѿ ��
			{
				printf("Invalid arguments.\n");
				continue;
			}
			load(argument); // �� �Է������� load
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