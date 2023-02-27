#include "parser.h"

int find_index(char* id)
{
	char* can_ids[protocol_id_num] = { "18FFA0F3", "18FFB0F3", "18FFA1F3", "18FFA2F3", "18FFA3F3", "18FFA4F3", "18FFA5F3", "18FFA6F3",
							"18FFA7F3", "18FFA8F3", "18FFA9F3", "18FFAAF3", "18FFACF3", "18FFAFF3", "18FECAF3", "1820F8F4",
							"1880F8F4", "189FF8F4", "18FFC0F3", "18FEC0F3", "1810A6A0", "1811A6A0", "08F200A0", "041000A0" };

	for (int i = 0; i < protocol_id_num; i++) {
		if (strcmp(can_ids[i], id) == 0) {
			return i;
		}
	}
	return -1;
}

void tokenizer_data(Node* ptr_node)
{
	ptr_node->date = _strdup(strtok(ptr_node->expression, " "));
	ptr_node->time = _strdup(strtok(NULL, " "));
	ptr_node->latitude = _strdup(strtok(NULL, " "));
	ptr_node->longitude = _strdup(strtok(NULL, " "));
	ptr_node->velocity = _strdup(strtok(NULL, " "));
}

void tokenizer_can(char* tokenize_data, Node* ptr_node)
{
	char* tokenized_id, * tokenized_data;
	tokenized_id = strtok(tokenize_data, "x");

	tokenized_id = strtok(NULL, " ");
	ptr_node->can_id = _strdup(tokenized_id);

	tokenized_data = strtok(NULL, "\n");
	ptr_node->can_data = _strdup(tokenized_data);
}


void parser(Node* data, unsigned char* Parsed_data)
{	
	
	char a[16];
	char* token;
	
	token = strtok(data->can_data, " ");

	for (int i = 0; i < 15; i+=2)
	{
		if (token[0] >> 6 == 1)
		{
			switch (token[0] & 15) {
			case 1:
				a[i] = 10;
				break;

			case 2:
				a[i] = 11;
				break;

			case 3:
				a[i] = 12;
				break;

			case 4:
				a[i] = 13;
				break;

			case 5:
				a[i] = 14;
				break;

			case 6:
				a[i]  = 15;
				break;
			}
		}
		else {
			a[i] = token[0] & 15;
		}

		if (token[1] >> 6 == 1) {
			switch (token[1] & 15)
			{
			case 1:
				a[i+1] = 10;
				token = strtok(NULL, " ");
				break;

			case 2:
				a[i+1] = 11;
				token = strtok(NULL, " ");
				break;

			case 3:
				a[i+1] = 12;
				token = strtok(NULL, " ");
				break;

			case 4:
				a[i+1] = 13;
				token = strtok(NULL, " ");
				break;

			case 5:
				a[i+1] = 14;
				token = strtok(NULL, " ");
				break;

			case 6:
				a[i+1] = 15;
				token = strtok(NULL, " ");
				break;
			}
		}
		else
		{
			a[i+1] = token[1] & 15;
			token = strtok(NULL, " ");
		}
	}

	Parsed_data[0] = a[0] * 16 + a[1];
	Parsed_data[1] = a[2] * 16 + a[3];
	Parsed_data[2] = a[4] * 16 + a[5];
	Parsed_data[3] = a[6] * 16 + a[7];
	Parsed_data[4] = a[8] * 16 + a[9];
	Parsed_data[5] = a[10] * 16 + a[11];
	Parsed_data[6] = a[12] * 16 + a[13];
	Parsed_data[7] = a[14] * 16 + a[15];
}

