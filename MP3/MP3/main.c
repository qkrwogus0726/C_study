#define _CRT_SECURE_NO_WARNINGS //test
#include <stdio.h>
#include <string.h>

#include "string_tools.h"
#include "library.h"

#define BUFFER_LENGTH 200

void handle_search();

void handle_add()
{
	char buffer[BUFFER_LENGTH];											//�̸�, ���� �� '�Է¹���' ����
	char* artist = NULL, * title = NULL, * path = NULL;					//�̸�, ����, ��� �� '�����س���' ����

	//�̸�, ����, ��� �ޱ�
	printf("    Artist : ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)					//buffer�� �̸�, ���� �� �����Ŷ� �̸��� �ٸ� ���� �����ص־� ��.
	{
		artist = _strdup(buffer);
	}

	printf("    Title : ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
	{
		title = _strdup(buffer);
	}

	printf("    Path : ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
	{
		path = _strdup(buffer);
	}

	add_song(artist, title, path);
}

void process_command()
{
	char command_line[BUFFER_LENGTH];
	char* command;

	while (1)
	{
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) < 0)		//line ������ ������� �Է��� �޴µ� 0�����̸� �׳� ���͸� ģ ��
			continue;
		
		command = strtok(command_line, " ");
		if (strcmp(command, "add") == 0)
		{
			handle_add();
		}
		else if (strcmp(command, "status") == 0)
		{
			status();
		}
		else if (strcmp(command, "search") == 0)
			handle_search();
			/*
		else if (strcmp(command, "remove") == 0)
			handle_remove();
		else if (strcmp(command, "play") == 0)
			handle_play();
		else if (strcmp(command, "save") == 0)
			handle_save();*/
		else if (strcmp(command, "exit") == 0)
			break;
	}
}

void handle_search()
{
	char name[BUFFER_LENGTH];
	char title[BUFFER_LENGTH];

	printf("   Artist : ");
	if (read_line(stdin, name, BUFFER_LENGTH) < 0)
	{
		printf("   Artist name required.\n");
		return;
	}

	printf("   Title : ");
	int title_len = read_line(stdin, name, BUFFER_LENGTH);
	if (title_len <= 0)
		search_song(name);
	else
		search_song(name, title);

	if (read_line(stdin, name, BUFFER_LENGTH) < 0)
	{
		printf("   Artist name required.\n");
		return;
	}
}

void handle_load()
{
	char buffer[BUFFER_LENGTH];

	printf("Data file name ? ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) <= 0)
		return;
	FILE* fp = fopen(buffer, "r");
	if (fp == NULL)
	{
		printf("No such file exists.\n");
		return;
	}
	load(fp);
	fclose(fp);

}

int main()
{
	initialize();
	handle_load();
	process_command();


}