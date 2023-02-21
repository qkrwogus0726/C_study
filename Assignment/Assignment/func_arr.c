#include "func_arr.h"
#include "convert_data.h"



unsigned char zero(unsigned char CANN[], double output_array[])
{
	double data[7];

	data[0] = convert_data(CANN, 0, 2);
	data[1] = convert_data(CANN, 2, 2);
	data[2] = convert_data(CANN, 4, 2);
	data[3] = convert_data(CANN, 6, 1);
	data[4] = convert_data(CANN, 7, 1);
	data[5] = convert_data(CANN, 8, 16) * 0.1;
	data[6] = convert_data(CANN, 24, 16) * 0.1;

	for (int i = 0; i < 7; i++)
		output_array[i] = data[i];
}

unsigned char one(unsigned char CANN[], double output_array[])
{
	double data[1];
	
	data[0] = convert_data(CANN, 0, 2);

	output_array[7] = data[0];
}

unsigned char two(unsigned char CANN[], double output_array[])
{
	double data[10];
	
	data[0] = convert_data(CANN, 0, 4);
	data[1] = convert_data(CANN, 4, 4);
	data[2] = convert_data(CANN, 8, 4);
	data[3] = convert_data(CANN, 12, 2);
	data[4] = convert_data(CANN, 14, 2);
	data[5] = convert_data(CANN, 16, 8) * 0.5;
	data[6] = convert_data(CANN, 24, 8) * 0.5;
	data[7] = convert_data(CANN, 32, 16) * 0.001;
	data[8] = convert_data(CANN, 48, 12) * 0.1;
	data[9] = convert_data(CANN, 60, 4);

	for (int i = 0; i < 10; i++)
		output_array[8 + i] = data[i];
}

unsigned char three(unsigned char CANN[], double output_array[])
{
	double data[5];

	data[0] = convert_data(CANN, 0, 12) * 0.2;
	data[1] = convert_data(CANN, 12, 12) * 0.2;
	data[2] = (convert_data(CANN, 24, 16) * 0.02) - 500;
	data[3] = (convert_data(CANN, 40, 16) * 0.01) - 325;
	data[4] = convert_data(CANN, 56, 8) - 50;

	for (int i = 0; i < 5; i++)
		output_array[18 + i] = data[i];

}

unsigned char four(unsigned char CANN[], double output_array[])
{
	double data[6];

	data[0] = convert_data(CANN, 0, 8);
	data[1] = convert_data(CANN, 8, 8);
	data[2] = convert_data(CANN, 16, 8);
	data[3] = convert_data(CANN, 24, 8);
	data[4] = convert_data(CANN, 32, 8);
	data[5] = convert_data(CANN, 40, 8);

	for (int i = 0; i < 6; i++)
		output_array[23 + i] = data[i];

}

unsigned char five(unsigned char CANN[], double output_array[])
{
	long data[7];

	data[0] = convert_data(CANN, 0, 16) * 0.01;
	data[1] = convert_data(CANN, 16, 12) * 0.0015;
	data[2] = convert_data(CANN, 28, 12) * 0.0015;
	data[3] = convert_data(CANN, 40, 8);
	data[4] = convert_data(CANN, 48, 8);
	data[5] = convert_data(CANN, 56, 4);
	data[6] = convert_data(CANN, 60, 4);

	for (int i = 0; i < 7; i++)
		output_array[29 + i] = data[i];
}

unsigned char six(unsigned char CANN[], double output_array[])
{
	double data[7];

	data[0] = (convert_data(CANN, 0, 16) * 0.2) - 50;
	data[1] = (convert_data(CANN, 16, 12) * 0.2) - 50;
	data[2] = (convert_data(CANN, 28, 12) * 0.2) - 50;
	data[3] = convert_data(CANN, 40, 8);
	data[4] = convert_data(CANN, 48, 8);
	data[5] = convert_data(CANN, 56, 4);
	data[6] = convert_data(CANN, 60, 4);

	for (int i = 0; i < 7; i++)
		output_array[36 + i] = data[i];


}

unsigned char seven(unsigned char CANN[], double output_array[])
{
	double data[6];

	data[0] = convert_data(CANN, 0, 12) * 0.2;
	data[1] = convert_data(CANN, 12, 12) * 0.2;
	data[2] = convert_data(CANN, 24, 12) * 0.0015;
	data[3] = convert_data(CANN, 36, 12) * 0.0015;
	data[4] = convert_data(CANN, 48, 8) * 2;
	data[5] = convert_data(CANN, 56, 8) * 2;

	for (int i = 0; i < 6; i++)
		output_array[43 + i] = data[i];

	output_array[44] = 1818;
}

unsigned char eight(unsigned char CANN[], double output_array[])
{
	double data[6];

	data[0] = (convert_data(CANN, 0, 8) * 0.5);
	data[1] = (convert_data(CANN, 8, 8) * 0.5);
	data[2] = convert_data(CANN, 16, 8);
	data[3] = convert_data(CANN, 24, 8);
	data[4] = convert_data(CANN, 32, 8) - 50;
	data[5] = convert_data(CANN, 40, 8) - 50;

	for (int i = 0; i < 6; i++)
		output_array[49 + i] = data[i];
}

unsigned char nine(unsigned char CANN[], double output_array[])
{
	double data[6];

	data[0] = convert_data(CANN, 0, 8);
	data[1] = convert_data(CANN, 8, 8);
	data[2] = convert_data(CANN, 16, 8);
	data[3] = convert_data(CANN, 24, 8);
	data[4] = convert_data(CANN, 32, 16);
	data[5] = convert_data(CANN, 48, 16);

	for (int i = 0; i < 6; i++)
		output_array[55 + i] = data[i];
}

unsigned char ten(unsigned char CANN[], double output_array[])
{
	double data[6];

	data[0] = convert_data(CANN, 0, 8);
	data[1] = convert_data(CANN, 8, 16);
	data[2] = convert_data(CANN, 24, 8);
	data[3] = convert_data(CANN, 32, 8);
	data[4] = convert_data(CANN, 40, 8);
	data[5] = convert_data(CANN, 48, 1);

	for (int i = 0; i < 6; i++)
		output_array[61 + i] = data[i];
}

unsigned char eleven(unsigned char CANN[], double output_array[])
{
	double data[4];

	data[0] = convert_data(CANN, 0, 4);
	data[1] = convert_data(CANN, 4, 4);
	data[2] = convert_data(CANN, 8, 8);
	data[3] = convert_data(CANN, 16, 48);

	for (int i = 0; i < 4; i++)
		output_array[67 + i] = data[i];
}

unsigned char twelve(unsigned char CANN[], double output_array[])
{
	double data[7];

	data[0] = convert_data(CANN, 0, 8);
	data[1] = convert_data(CANN, 8, 12) * 0.1;
	data[2] = convert_data(CANN, 20, 12) * 0.2;
	data[3] = convert_data(CANN, 32, 12) * 0.1;
	data[4] = convert_data(CANN, 44, 4);
	data[5] = convert_data(CANN, 48, 8);
	data[6] = convert_data(CANN, 56, 8) * 0.1;

	for (int i = 0; i < 7; i++)
		output_array[71 + i] = data[i];
}

unsigned char thirteen(unsigned char CANN[], double output_array[])
{
	double data[3];

	data[0] = convert_data(CANN, 0, 20);
	data[1] = convert_data(CANN, 20, 20);
	data[2] = convert_data(CANN, 40, 20);

	for (int i = 0; i < 3; i++)
		output_array[78 + i] = data[i];
}

unsigned char fourteen(unsigned char CANN[], double output_array[])
{
	double data[64];

	for(int i = 0; i < 64; i++)
		data[i] = convert_data(CANN, i, 1);

	for (int i = 0; i < 64; i++)
		output_array[81 + i] = data[i];
}

unsigned char fifteen(unsigned char CANN[], double output_array[])
{
	double data[6];

	data[0] = convert_data(CANN, 0, 8);
	data[1] = convert_data(CANN, 8, 8);
	data[2] = convert_data(CANN, 16, 12) * 0.002;
	data[3] = convert_data(CANN, 28, 12) * 0.002;
	data[4] = convert_data(CANN, 40, 12) * 0.002;
	data[5] = convert_data(CANN, 52, 12) * 0.002;

	for (int i = 0; i < 6; i++)
		output_array[145 + i] = data[i];
}

unsigned char sixteen(unsigned char CANN[], double output_array[])
{
	double data[8];

	data[0] = convert_data(CANN, 0, 8);
	data[1] = convert_data(CANN, 8, 8) - 50;
	data[2] = convert_data(CANN, 16, 8) - 50;
	data[3] = convert_data(CANN, 24, 8) - 50;
	data[4] = convert_data(CANN, 32, 8) - 50;
	data[5] = convert_data(CANN, 40, 8) - 50;
	data[6] = convert_data(CANN, 48, 8) - 50;
	data[7] = convert_data(CANN, 56, 8) - 50;

	for (int i = 0; i < 8; i++)
		output_array[151 + i] = data[i];
}

unsigned char seventeen(unsigned char CANN[], double output_array[])
{
	double data[8];

	data[0] = convert_data(CANN, 0, 8);
	data[1] = convert_data(CANN, 8, 8) - 50;
	data[2] = convert_data(CANN, 16, 8) - 50;
	data[3] = convert_data(CANN, 24, 8) - 50;
	data[4] = convert_data(CANN, 32, 8) - 50;
	data[5] = convert_data(CANN, 40, 8) - 50;
	data[6] = convert_data(CANN, 48, 8) - 50;
	data[7] = convert_data(CANN, 56, 8) - 50;

	for (int i = 0; i < 8; i++)
		output_array[159 + i] = data[i];
}

unsigned char eighteen(unsigned char CANN[], double output_array[])
{
	double data[5];

	data[0] = convert_data(CANN, 0, 12);
	data[1] = convert_data(CANN, 12, 12);
	data[2] = convert_data(CANN, 24, 8) * 0.5;
	data[3] = convert_data(CANN, 32, 1);
	data[4] = convert_data(CANN, 33, 1);

	for (int i = 0; i < 5; i++)
		output_array[167 + i] = data[i];
}

unsigned char nineteen(unsigned char CANN[], double output_array[])
{
	double data[4];

	data[0] = convert_data(CANN, 0, 2);
	data[1] = convert_data(CANN, 2, 2);
	data[2] = convert_data(CANN, 4, 2);
	data[3] = convert_data(CANN, 6, 2);

	for (int i = 0; i < 4; i++)
		output_array[172 + i] = data[i];
}

unsigned char twenty(unsigned char CANN[], double output_array[])
{
	double data[12];

	data[0] = convert_data(CANN, 0, 8);
	data[1] = convert_data(CANN, 8, 16);
	data[2] = convert_data(CANN, 24, 16);
	data[3] = convert_data(CANN, 40, 8);
	data[4] = convert_data(CANN, 48, 8);
	data[5] = convert_data(CANN, 56, 2);

	data[6] = convert_data(CANN, 58, 1);
	data[7] = convert_data(CANN, 59, 1);
	data[8] = convert_data(CANN, 60, 1);
	data[9] = convert_data(CANN, 61, 1);
	data[10] = convert_data(CANN, 62, 1);
	data[11] = convert_data(CANN, 63, 1);

	for (int i = 0; i < 12; i++)
		output_array[176 + i] = data[i];
}

unsigned char twentyone(unsigned char CANN[], double output_array[])
{
	double data[1];

	data[0] = convert_data(&CANN, 8, 1);

	output_array[188] = data[0];
}

unsigned char twentytwo(unsigned char CANN[], double output_array[])
{
	double data[6];

	data[0] = convert_data(CANN, 0, 3);
	data[1] = convert_data(CANN, 8, 4);
	data[2] = convert_data(CANN, 12, 4);
	data[3] = convert_data(CANN, 40, 8) - 50;
	data[4] = convert_data(CANN, 48, 8);
	data[5] = convert_data(CANN, 56, 1);

	for (int i = 0; i < 6; i++)
	{
		output_array[189+i] = data[i];
	}
		

}

unsigned char twentythree(unsigned char CANN[], double output_array[])
{
	double data[1];

	data[0] = convert_data(CANN, 46, 1);

	output_array[195] = data[0];
}