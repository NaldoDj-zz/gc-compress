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

void rle_uncompress( uint8_t* data_array, uint32_t original_size, uint32_t compressed_size )
{
	uint8_t* temp_array = calloc( original_size, sizeof( uint8_t ) );
	uint32_t data_index = 0, temp_index = 0;

	while( data_index < compressed_size )
	{
		if( data_array[data_index] & RLE_NON_CONSEC_MASK )
		{
			temp_array[temp_index++] = data_array[data_index++] ^ RLE_NON_CONSEC_MASK;
		}
		else
		{
			uint8_t value = data_array[data_index++];
			uint8_t consecutive_counter = data_array[data_index++];

			for( uint8_t i = 0; i < consecutive_counter; i++ )
			{
				temp_array[temp_index++] = value;
			}
		}
	}

	for( uint8_t i = 0; i < original_size; i++ )
	{
		data_array[i] = temp_array[i];
	}
}
