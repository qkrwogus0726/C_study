#define _CRT_SECURE_NO_WARNINGS //test
#include <stdio.h>
#include <string.h>

#include "string_tools.h"
#include "library.h"

#define BUFFER_LENGTH 200

void handle_add()
{
	char buffer[BUFFER_LENGTH];											//이름, 제목 등 '입력받을' 공간
	char* artist = NULL, * title = NULL, * path = NULL;					//이름, 제목, 경로 등 '저장해놓을' 공간

	//이름, 제목, 경로 받기
	printf("    Artist : ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)					//buffer로 이름, 제목 다 받을거라 이름을 다른 곳에 저장해둬야 함.
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
		if (read_line(stdin, command_line, BUFFER_LENGTH) < 0)		//line 단위로 사용자의 입력을 받는데 0이하면 그냥 엔터만 친 것
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