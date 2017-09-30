#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rle.h"

#define INPUT_BUFFER_SIZE 6

int main( void )
{
	uint8_t data_arr[] = { 0x03, 0x74, 0x04, 0x04, 0x04, 0x35, 0x35, 0x64,
		0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x56, 0x45, 0x56, 0x56, 0x56, 0x09, 0x09, 0x09 };
	uint32_t data_size = 24;

	const uint32_t compressed_size = rle_compress( data_arr, data_size );

	printf( "Uncompressed size: %d\n", data_size );
	printf( "Compressed size: %d\n", compressed_size );

	printf( "Compressed data:\n" );
	for( uint32_t i = 0; i < compressed_size; i++ )
	{
		printf( "%d\n", data_arr[i] );
	}

	rle_uncompress( data_arr, data_size, compressed_size );

	printf( "Restored data:\n" );
	for( uint32_t i = 0; i < data_size; i++ )
	{
		printf( "%d\n", data_arr[i] );
	}

	return 0;
}
