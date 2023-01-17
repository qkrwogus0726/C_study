#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 20

typedef struct List
{
	char name[BUFFER_SIZE];
	char num[BUFFER_SIZE];
}LST;

LST L[BUFFER_SIZE];
int count = 0;

void add()
{
	printf("name : ");
	scanf_s("%s", L[count].name, sizeof(L[count].name));
	printf("number : ");
	scanf_s("%s", L[count].num, sizeof(L[count].num));
	printf("%s was added successfully.", L[count].name);
	count++;
	printf("\n\n");
}

void status()
{
	for (int i = 0; i < count; i++)
	{
		printf("name : %s", L[i].name);
		printf("\n");
		printf("num : %s", L[i].num);
		printf("\n");
	}
	printf("\n");
}

void find()
{
	char findname[BUFFER_SIZE];

	printf("name : ");
	scanf_s("%s", findname, BUFFER_SIZE);
	for (int i = 0; i < count; i++) {
		if (strcmp(findname, L[i].name) == 0)
		{
			printf("name : ");
			printf("%s \n", L[i].name);
			printf("num : ");
			printf("%s", L[i].num);
			printf("\n\n");
		}
	}
}

void rm()
{
	char findname[BUFFER_SIZE];

	printf("name : ");
	scanf_s("%s", findname, BUFFER_SIZE);
	for (int i = 0; i < count; i++)
	{
		if (strcmp(findname, L[i].name) == 0)
		{
			strcpy_s(L[i].name, sizeof(L[i].name), L[i + 1].name);
			strcpy_s(L[i].num, sizeof(L[i].num), L[i + 1].num);
			count--;
			if (L[i + 1].name == NULL)
			{
				printf("Wrong input");
				continue;
			}
		}
	}
}

void save()
{
	FILE* fp;
	fopen_s(&fp, "data.txt", "w");
	if (fp == NULL)
	{
		printf("Open failed.");
		return;
	}
	for (int i = 0; i < count; i++) {
		fprintf(fp, "%s", L[i].name);
		fprintf(fp, "\n");
		fprintf(fp, "%s", L[i].num);
		fprintf(fp, "\n");
	}
	fclose(fp);
}

void read()
{
	char* buf2[BUFFER_SIZE] = &L->num;
	int n = 0;

	FILE* fp;
	fopen_s(&fp, "data.txt", "r");
	if (fp == NULL) {
		printf("Open failed.");
		return;
	}
	for (int i = 0; i < count; i++)
	{
		fscanf_s(fp, "%s\n", buf2[i], BUFFER_SIZE);
		//strcpy_s(L[n].name, sizeof(L[n].name), _strdup(buf1));
		//strcpy_s(L[n].num, sizeof(L[n].num), _strdup(buf2));
	}
	fclose(fp);
}

int main(void) //asdasd
{
	char command[BUFFER_SIZE];

	while (1)
	{
		printf("$ : ");
		scanf_s("%s", command, BUFFER_SIZE);
		printf("\n");

		if (strcmp(command, "add") == 0)
		{
			add(count);
			continue;
		}
		else if (strcmp(command, "status") == 0)
		{
			status();
			continue;
		}
		else if (strcmp(command, "find") == 0)
		{
			find();
			continue;
		}
		else if (strcmp(command, "remove") == 0)
		{
			rm();
			continue;
		}
		else if (strcmp(command, "save") == 0)
		{
			save();
			continue;
		}
		else if (strcmp(command, "read") == 0)
		{
			read();
			continue;
		}
		else if (strcmp(command, "exit") == 0)
			break;
	}
}