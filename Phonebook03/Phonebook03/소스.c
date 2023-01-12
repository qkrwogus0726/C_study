#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define INIT_CAPACITY 3
#define BUFFER_SIZE 50

char** names;
char** nums;

int capacity = INIT_CAPACITY;
int n = 0;

char delim[] = " ";

void init_directory()
{
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	nums = (char**)malloc(INIT_CAPACITY * sizeof(char*));
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

void process_command()
{
	char command_line[BUFFER_SIZE];
	char* command, * argument1, * argument2;

	while (1)
	{
		if (read_line(command_line, BUFFER_SIZE) <= 0)
			continue;
	}
}

int main(void)
{
	char str[] = "now # is the time # to start preparing ### for the exam#";
	char delim[] = " ";
	char* token;

	token = strtok(str, delim);

	while (token != NULL)
	{
		printf("next token is : %s : %d\n", token, strlen(token));
		token = strtok(NULL, delim);
	}
	return 0;
}