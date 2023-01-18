#define _CRT_SECURE_NO_WARNINGS //test
#include <stdio.h>
#include <string.h>

#include "string_tools.h"
#include "library.h"

#define BUFFER_LENGTH 200

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
		if (read_line(stdin, command_line, BUFFER_LENGTH) < 0)		//line ������ ������� �Է��� �޴µ� 0���ϸ� �׳� ���͸� ģ ��
			continue;
		
		command = strtok(command_line, " ");
		if (strcmp(command, "add") == 0)
			handle_add();
		/*
		else if (strcmp(command, "search") == 0)
			handle_search();
		else if (strcmp(command, "remove") == 0)
			handle_remove();
		else if (strcmp(command, "status") == 0)
			handle_status();
		else if (strcmp(command, "play") == 0)
			handle_play();
		else if (strcmp(command, "save") == 0)
			handle_save();*/
		else if (strcmp(command, "exit") == 0)
			break;
	}
}

int main()
{
	initialize();
	process_command();


}