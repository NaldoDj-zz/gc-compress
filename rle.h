#ifndef RLE_H
#define RLE_H

#include <stdint.h>

uint32_t rle_compress( uint8_t* data_array, uint32_t data_size );
void rle_uncompress( uint8_t* data_array, uint32_t original_size, uint32_t compressed_size );

#endif