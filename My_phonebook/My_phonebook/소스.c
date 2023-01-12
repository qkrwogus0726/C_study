#include <stdio.h>
#include <string.h>

#define max 20

typedef struct List
{
	char* name;
	char* num;
	char* email;
	char* group;
	char* tes;
}LST;

LST L[max];

void add(char* name, char* number, char* email, char* group)
{
	int i = 1;
	while (i >= 0 && strcmp(L[i].name, name) > 0)
	{
		L[i + 1] = L[i];
	}
}

int main(void)
{
	char command[max];
	char findname[max];
	int count = 0;

	while (1)
	{
		printf("$ : ");
		scanf_s("%s", command, sizeof(command));
		printf("\n");

		if (strcmp(command, "add") == 0)
		{
			printf("name : ");
			scanf_s("%s", L[count].name, sizeof(L[count].name));
			printf("number : ");
			scanf_s("%s", L[count].num, sizeof(L[count].num));
			printf("%s was added successfully.", L[count].name);
			count++;
			printf("\n\n");
		}
		else if (strcmp(command, "status") == 0)
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
		else if (strcmp(command, "find") == 0)
		{
			printf("name : ");
			scanf_s("%s", findname, sizeof(findname));
			for (int i = 0; i < count; i++) {
				if (strcmp(findname, L[i].name) == 0)
				{
					printf("name : ");
					printf("%s", L[i].name);
					printf("num : ");
					printf("%s", L[i].num);
					printf("\n\n");
				}
			}
		}
		else if (strcmp(command, "remove") == 0)
		{
			printf("name : ");
			scanf_s("%s", findname, sizeof(findname));
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
		else if (strcmp(command, "save") == 0)
		{
			FILE* fp;
			fopen_s(&fp, "data.txt", "w");
			if (fp == NULL)
			{
				printf("Open failed.");
				return;
			}
			for (int i = 0; i < count; i++) {
				fprintf(fp, "%s %s", L[i].name, L[i].num);
			}
			fclose(fp);
		}
		else if (strcmp(command, "read") == 0)
		{
			char buf1[max];
			char buf2[max];
			int n = 0;

			FILE* fp;
			fopen_s(&fp, "data.txt", "r");
			if (fp == NULL) {
				printf("Open failed.");
				return;
			}
			while ((fscanf_s(fp, "%s", buf1, sizeof(buf1)) != EOF))
			{
				fscanf_s(fp, "%s", buf2, sizeof(buf2));
				strcpy_s(L[n].name, sizeof(L[n].name), _strdup(buf1));
				strcpy_s(L[n].num, sizeof(L[n].num), _strdup(buf2));
				n++;
			}
		}
		else if (strcmp(command, "exit") == 0) break;
	}
}