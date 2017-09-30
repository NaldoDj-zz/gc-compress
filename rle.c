#include <stdlib.h>
#include "rle.h"

#define RLE_MAX_CONSECUTIVE_SIZE 255
#define RLE_NON_CONSEC_MASK 0x80

uint32_t rle_compress( uint8_t* data_array, uint32_t data_size )
{
	uint32_t data_index = 0, new_index = 0;

	while( data_index < data_size )
	{
		uint8_t consecutive_counter = 0;
		data_array[new_index++] = data_array[data_index];
		while( data_array[data_index] == data_array[new_index - 1] &&
			data_index < RLE_MAX_CONSECUTIVE_SIZE &&
			data_index < data_size )
		{
			consecutive_counter++;
			data_index++;
		}

		if( consecutive_counter == 1 )
		{
			data_array[new_index - 1] |= RLE_NON_CONSEC_MASK;
		}
		else
		{
			data_array[new_index++] = consecutive_counter;
		}
	}


	return new_index * sizeof( uint8_t );
}

uint32_t rle_uncompress( uint8_t* data_array, uint32_t data_size )
{
	return 0;
}