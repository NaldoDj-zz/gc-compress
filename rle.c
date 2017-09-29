#include <stdlib.h>
#include "rle.h"

#define RLE_MAX_CONSECUTIVE_SIZE 255

uint32_t rle_compress( uint8_t* data_array, uint32_t data_size )
{
	uint8_t* temp_array = calloc( data_size, sizeof( uint8_t ) );
	if( temp_array == NULL )
	{
		return 0;
	}

	uint32_t data_index = 0, temp_index = 0;

	while( data_index < data_size )
	{
		uint8_t consecutive_counter = 0;
		temp_array[temp_index++] = data_array[data_index];
		while( data_array[data_index] == temp_array[temp_index - 1] &&
			data_index < RLE_MAX_CONSECUTIVE_SIZE &&
			data_index < data_size )
		{
			consecutive_counter++;
			data_index++;
		}
		temp_array[temp_index++] = consecutive_counter;
	}

	for( uint8_t i = 0; i < data_size; i++ )
	{
		data_array[i] = temp_array[i];
	}
	free( temp_array );

	return temp_index * sizeof( uint8_t );
}

uint32_t rle_uncompress( uint8_t* data_array, uint32_t data_size )
{
	return 0;
}