#pragma once
#define BUFFER_SIZE 300

int byte_rle_encode(char escape_char, char* input_buf, char* output_buf);
int byte_rle_decode(char escape_char, char* input_buf, char* output_buf);
