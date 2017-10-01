/**
 * @file rle.h
 * @author Jesse Tham
 * @date September 30th, 2017
 * @brief Header for the run-length encoding API
 *
 * rle_compress will compress the given data array using run-length encoding.
 * rle_uncompress will decompress an array compressed by rle_compress.
 *
 * Run-length encoding (RLE) is a lossless data compression algorithm that takes advantage
 * of consecutive repeating data. The algorithm counts how many times the data repeats and then
 * stores it as a pair where the first value is the data itself and the second is how many times
 * it was repeated. Ex: 'aaaabbbccccc' turns into 'a4b3c5'.
 *
 * This version of the compression algorithm sets the most significant bit of a data byte to
 * denote if the data byte did not repeat. This prevents it from taking more space
 * than it did when uncompressed. Ex: The data stream 'aaabcc' turns into 'a3bc2' (where 'b' has its MSB
 * set) instead of 'a3b1c2'. This means that the compression algorithm can only work on unsigned, 7-bit
 * values. This version also automatically chunks data into bytes and therefore cannot detect
 * repeating values that are smaller or larger than 8 bits.
 *
 */

#ifndef RLE_H
#define RLE_H

#include <stdint.h>

/**
 * @brief Compress the input data array using RLE
 * @param data_array Pointer to a data array containing a set of bytes to compress
 * @param data_size The size of the data array that is being passed in
 * @return new_size The size of the compressed data array
 *
 * Implements the RLE algorithm
 */
uint32_t rle_compress( uint8_t* data_array, uint32_t data_size );

/**
 * @brief Uncompresses data compressed by rle_compress
 * @param data_array Pointer to a data array containing a set of bytes to decompress
 * @param original_size The size of the data array before it was compressed
 * @param compressed_size The size of the compressed data array
 *
 * Decompresses data compressed by rle_compress
 */
void rle_uncompress( uint8_t* data_array, uint32_t original_size, uint32_t compressed_size );

#endif