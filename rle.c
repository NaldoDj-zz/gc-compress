/**
 * @file rle.c
 * @author Jesse Tham
 * @date September 30th, 2017
 * @brief Run length encoding algorithm implementation in C
 *
 * Detailed description can be found in rle.h
 *
 */

#include <stdlib.h>
#include "rle.h"

// Maximum value that can be stored in the consecutive counter
#define RLE_MAX_CONSECUTIVE_SIZE 255
// Mask that sets the MSB to denote that the value did not repeat
#define RLE_NO_REPEAT_MASK 0x80

uint32_t rle_compress( uint8_t* data_array, uint32_t data_size )
{
	// Points to uncompressed data
	uint32_t data_index = 0;
	// Points to the compressed data
	uint32_t new_index = 0;

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

		// Check if the value didn't consecutively repeat
		if( consecutive_counter == 1 )
		{
			data_array[new_index - 1] |= RLE_NO_REPEAT_MASK;
		}
		else
		{
			data_array[new_index++] = consecutive_counter;
		}
	}

	// Return the new size of the data array
	return new_index;
}

void rle_uncompress( uint8_t* data_array, uint32_t original_size, uint32_t compressed_size )
{
	uint8_t* temp_array = malloc( original_size * sizeof( uint8_t ) );
	uint32_t data_index = 0;
	uint32_t temp_index = 0;

	while( data_index < compressed_size )
	{
		// Check if the data didn't consecutively repeat
		if( data_array[data_index] & RLE_NO_REPEAT_MASK )
		{
			temp_array[temp_index++] = data_array[data_index++] ^ RLE_NO_REPEAT_MASK;
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

	// Copy data from temp array to the input array
	for( uint8_t i = 0; i < original_size; i++ )
	{
		data_array[i] = temp_array[i];
	}
	free( temp_array );
}
