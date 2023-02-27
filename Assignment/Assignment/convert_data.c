#include "convert_data.h"
#include <math.h>
#include <stdlib.h>


long convert_data(unsigned char a[], int start_bit, int length)
{
	long long line = 0;
	long long shift_num = 0;
	long result = 0;
	int last_index, first_index;

	last_index = ((start_bit + (length - 1)) / 8);
	first_index = start_bit / 8;

	for (int i = last_index; i >= first_index; i--) { 
		line = line << 8;
		line += a[i];
	}

	for (int i = 0; i < length; i++) {
		shift_num += pow(2, i);
	}

	line = line >> start_bit % 8;
	result = line & shift_num;
	return result;
}