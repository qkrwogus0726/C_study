#include "parser.h"

void Parser(Node* data, unsigned char* CAN)
{
	char temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp11, temp12, temp13, temp14, temp15, temp16;

	char* token;
	token = (char*)malloc(sizeof(char) * MAX);
	if (token == NULL)
		return;


	token = strtok(data->CAN_DATA, " ");

	if (token[0] >> 6 == 1)
	{
		switch (token[0] & 15)
		{
		case 1:
			temp1 = 10;
			break;
		case 2:
			temp1 = 11;
			break;
		case 3:
			temp1 = 12;
			break;
		case 4:
			temp1 = 13;
			break;
		case 5:
			temp1 = 14;
			break;
		case 6:
			temp1 = 15;
			break;
		}
	}
	else
	{
		temp1 = token[0] & 15;
	}

	if (token[1] >> 6 == 1)
	{
		switch (token[1] & 15)
		{
		case 1:
			temp2 = 10;
			break;
		case 2:
			temp2 = 11;
			break;
		case 3:
			temp2 = 12;
			break;
		case 4:
			temp2 = 13;
			break;
		case 5:
			temp2 = 14;
			break;
		case 6:
			temp2 = 15;
			break;
		}
	}
	else
	{
		temp2 = token[1] & 15;
	}

	token = strtok(NULL, " ");

	if (token[0] >> 6 == 1)			//알파벳인 경우
	{
		switch (token[0] & 15)
		{
		case 1:
			temp3 = 10;
			break;
		case 2:
			temp3 = 11;
			break;
		case 3:
			temp3 = 12;
			break;
		case 4:
			temp3 = 13;
			break;
		case 5:
			temp3 = 14;
			break;
		case 6:
			temp3 = 15;
			break;
		}
	}
	else
	{
		temp3 = token[0] & 15;
	}

	if (token[1] >> 6 == 1)
	{
		switch (token[1] & 15)
		{
		case 1:
			temp4 = 10;
			break;
		case 2:
			temp4 = 11;
			break;
		case 3:
			temp4 = 12;
			break;
		case 4:
			temp4 = 13;
			break;
		case 5:
			temp4 = 14;
			break;
		case 6:
			temp4 = 15;
			break;
		}
	}
	else
	{
		temp4 = token[1] & 15;
	}

	token = strtok(NULL, " ");

	if (token[0] >> 6 == 1)
	{
		switch (token[0] & 15)
		{
		case 1:
			temp5 = 10;
			break;
		case 2:
			temp5 = 11;
			break;
		case 3:
			temp5 = 12;
			break;
		case 4:
			temp5 = 13;
			break;
		case 5:
			temp5 = 14;
			break;
		case 6:
			temp5 = 15;
			break;
		}
	}
	else
	{
		temp5 = token[0] & 15;
	}

	if (token[1] >> 6 == 1)
	{
		switch (token[1] & 15)
		{
		case 1:
			temp6 = 10;
			break;
		case 2:
			temp6 = 11;
			break;
		case 3:
			temp6 = 12;
			break;
		case 4:
			temp6 = 13;
			break;
		case 5:
			temp6 = 14;
			break;
		case 6:
			temp6 = 15;
			break;
		}
	}
	else
	{
		temp6 = token[1] & 15;
	}

	token = strtok(NULL, " ");

	if (token[0] >> 6 == 1)
	{
		switch (token[0] & 15)
		{
		case 1:
			temp7 = 10;
			break;
		case 2:
			temp7 = 11;
			break;
		case 3:
			temp7 = 12;
			break;
		case 4:
			temp7 = 13;
			break;
		case 5:
			temp7 = 14;
			break;
		case 6:
			temp7 = 15;
			break;
		}
	}
	else
	{
		temp7 = token[0] & 15;
	}

	if (token[1] >> 6 == 1)
	{
		switch (token[1] & 15)
		{
		case 1:
			temp8 = 10;
			break;
		case 2:
			temp8 = 11;
			break;
		case 3:
			temp8 = 12;
			break;
		case 4:
			temp8 = 13;
			break;
		case 5:
			temp8 = 14;
			break;
		case 6:
			temp8 = 15;
			break;
		}
	}
	else
	{
		temp8 = token[1] & 15;
	}

	token = strtok(NULL, " ");

	if (token[0] >> 6 == 1)
	{
		switch (token[0] & 15)
		{
		case 1:
			temp9 = 10;
			break;
		case 2:
			temp9 = 11;
			break;
		case 3:
			temp9 = 12;
			break;
		case 4:
			temp9 = 13;
			break;
		case 5:
			temp9 = 14;
			break;
		case 6:
			temp9 = 15;
			break;
		}
	}
	else
	{
		temp9 = token[0] & 15;
	}

	if (token[1] >> 6 == 1)
	{
		switch (token[1] & 15)
		{
		case 1:
			temp10 = 10;
			break;
		case 2:
			temp10 = 11;
			break;
		case 3:
			temp10 = 12;
			break;
		case 4:
			temp10 = 13;
			break;
		case 5:
			temp10 = 14;
			break;
		case 6:
			temp10 = 15;
			break;
		}
	}
	else
	{
		temp10 = token[1] & 15;
	}

	token = strtok(NULL, " ");

	if (token[0] >> 6 == 1)
	{
		switch (token[0] & 15)
		{
		case 1:
			temp11 = 10;
			break;
		case 2:
			temp11 = 11;
			break;
		case 3:
			temp11 = 12;
			break;
		case 4:
			temp11 = 13;
			break;
		case 5:
			temp11 = 14;
			break;
		case 6:
			temp11 = 15;
			break;
		}
	}
	else
	{
		temp11 = token[0] & 15;
	}

	if (token[1] >> 6 == 1)
	{
		switch (token[1] & 15)
		{
		case 1:
			temp12 = 10;
			break;
		case 2:
			temp12 = 11;
			break;
		case 3:
			temp12 = 12;
			break;
		case 4:
			temp12 = 13;
			break;
		case 5:
			temp12 = 14;
			break;
		case 6:
			temp12 = 15;
			break;
		}
	}
	else
	{
		temp12 = token[1] & 15;
	}

	token = strtok(NULL, " ");

	if (token[0] >> 6 == 1)
	{
		switch (token[0] & 15)
		{
		case 1:
			temp13 = 10;
			break;
		case 2:
			temp13 = 11;
			break;
		case 3:
			temp13 = 12;
			break;
		case 4:
			temp13 = 13;
			break;
		case 5:
			temp13 = 14;
			break;
		case 6:
			temp13 = 15;
			break;
		}
	}
	else
	{
		temp13 = token[0] & 15;
	}

	if (token[1] >> 6 == 1)
	{
		switch (token[1] & 15)
		{
		case 1:
			temp14 = 10;
			break;
		case 2:
			temp14 = 11;
			break;
		case 3:
			temp14 = 12;
			break;
		case 4:
			temp14 = 13;
			break;
		case 5:
			temp14 = 14;
			break;
		case 6:
			temp14 = 15;
			break;
		}
	}
	else
	{
		temp14 = token[1] & 15;
	}

	token = strtok(NULL, " ");

	if (token[0] >> 6 == 1)
	{
		switch (token[0] & 15)
		{
		case 1:
			temp15 = 10;
			break;
		case 2:
			temp15 = 11;
			break;
		case 3:
			temp15 = 12;
			break;
		case 4:
			temp15 = 13;
			break;
		case 5:
			temp15 = 14;
			break;
		case 6:
			temp15 = 15;
			break;
		}
	}
	else
	{
		temp15 = token[0] & 15;
	}

	if (token[1] >> 6 == 1)
	{
		switch (token[1] & 15)
		{
		case 1:
			temp16 = 10;
			break;
		case 2:
			temp16 = 11;
			break;
		case 3:
			temp16 = 12;
			break;
		case 4:
			temp16 = 13;
			break;
		case 5:
			temp16 = 14;
			break;
		case 6:
			temp16 = 15;
			break;
		}
	}
	else
	{
		temp16 = token[1] & 15;
	}

	CAN[0] = temp1 * 16 + temp2;
	CAN[1] = temp3 * 16 + temp4;
	CAN[2] = temp5 * 16 + temp6;
	CAN[3] = temp7 * 16 + temp8;
	CAN[4] = temp9 * 16 + temp10;
	CAN[5] = temp11 * 16 + temp12;
	CAN[6] = temp13 * 16 + temp14;
	CAN[7] = temp15 * 16 + temp16;

}

