#ifndef RLE_H
#define RLE_H

#include <stdint.h>

uint32_t rle_compress( uint8_t* data_ptr, uint32_t data_size );
uint32_t rle_uncompress( uint8_t* data_ptr, uint32_t data_size );

#endif