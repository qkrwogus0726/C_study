#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 3
#define BUFFER_SIZE 50

char** names;
char** numbers;

int capacity = INIT_CAPACITY; //배열의 크기
int n = 0;

char delim[] = " ";

void init_directory()
{
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}

int read_line(FILE* fp, char str[], int n)
{
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
	{
		if (i < n)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

void add(char* name, char* number)
{
	if (n >= capacity)
		reallocate();
	int i = n - 1;

	while (i >= 0 && strcmp(names[i], name) > 0)
	{
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i + 1] = strdup(name);
	numbers[i + 1] = strdup(numbers);
	n++;
}

void status()
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%s %s\n", names[i], numbers[i]);
	}
	printf("Total %d persons.\n", n);
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
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully.\n", name);
}

void find(char* name)
{
	int index = search(name);
	if (index == -1)
	{
		printf("No person names '%s' exists.\n", name);
	}
	else printf("%s\n", numbers[index]);
}

int search(char* name)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (strcmp(name, names[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}

void reallocate()
{
	int i;
	capacity *= 2; //반드시 2배 할 필요는 없음.
	char** tmp1 = (char**)malloc(capacity * sizeof(char*));
	char** tmp2 = (char**)malloc(capacity * sizeof(char*));

	for (i = 0; i < n; i++)
	{
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}
	free(names);
	free(numbers);

	names = tmp1;
	numbers = tmp2;
}

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
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
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

int main(void)
{
	char command_line[BUFFER_SIZE];
	char* command, * argument;
	char name_str[BUFFER_SIZE];

	while (1)
	{
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_SIZE) <= 0)
			continue;

		command = strtok(command_line, " ");

		if (strcmp(command, "read") == 0)
		{
			argument = strtok(NULL, " ");
			if (argument == NULL)
			{
				printf("Invalid arguments.\n");
				continue;
			}
			load(argument);
		}
	}

	init_directory();
	process_command();

	return 0;
}