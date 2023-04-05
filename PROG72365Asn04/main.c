#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 300
#define ESCAPE_CHAR '#'

int encode_rle(char* input, char* output) {
    int i = 0, j = 0;
    while (input[i] != '\0') {
        char c = input[i];
        int count = 1;
        while (c == input[i + count] && count < 255) {
            count++;
        }
        if (count > 1 || c == ESCAPE_CHAR) {
            output[j++] = ESCAPE_CHAR;
            output[j++] = (char)count;
            output[j++] = c;
            i += count;
        }
        else {
            output[j++] = c;
            i++;
        }
        if (j >= BUFFER_SIZE) {
            return -1; // buffer overflow
        }
    }
    output[j] = '\0';
    return j;
}

int decode_rle(char* input, char* output) {
    int i = 0, j = 0;
    while (input[i] != '\0') {
        if (input[i] == ESCAPE_CHAR) {
            int count = input[i + 1];
            char c = input[i + 2];
            for (int k = 0; k < count; k++) {
                output[j++] = c;
                if (j >= BUFFER_SIZE) {
                    return -1; // buffer overflow
                }
            }
            i += 3;
        }
        else {
            output[j++] = input[i++];
            if (j >= BUFFER_SIZE) {
                return -1; // buffer overflow
            }
        }
    }
    output[j] = '\0';
    return j;
}

int main() {
    char input1[] = "AAABBBCCCCDDDEEE#AAA";
    char output1[BUFFER_SIZE];
    char decoded1[BUFFER_SIZE];
    printf("Original string: %s\n", input1);
    printf("Original length: %d\n", (int)strlen(input1));
    int len1 = encode_rle(input1, output1);
    if (len1 == -1) {
        printf("Error: buffer overflow during encoding\n");
    }
    else {
        printf("Encoded string: %s\n", output1);
        printf("Encoded length: %d\n", len1);
        int len2 = decode_rle(output1, decoded1);
        if (len2 == -1) {
            printf("Error: buffer overflow during decoding\n");
        }
        else {
            printf("Decoded string: %s\n", decoded1);
            printf("Decoded length: %d\n", len2);
        }
    }
    printf("\n");
    char input2[] = "ABCDE";
    char output2[BUFFER_SIZE];
    char decoded2[BUFFER_SIZE];
    printf("Original string: %s\n", input2);
    printf("Original length: %d\n", (int)strlen(input2));
    int len3 = encode_rle(input2, output2);
    if (len3 == -1) {
        printf("Error: buffer overflow during encoding\n");
    }
    else if (len3 >= (int)strlen(input2)) {
        printf("No compression possible, output same as input\n");
        printf("Length returned: %d\n", len3);
    }
    else {
        printf("Encoded string: %s\n", output2);
        printf("Encoded length: %d\n", len3);
        int len4 = decode_rle(output2, decoded2);
        if (len4 == -1) {
            printf("Error: buffer overflow during decoding\n");
        }
        else {
            printf("Decoded string: %s\n", decoded2);
            printf("Decoded length: %d\n", len4);
        }
    }
    return 0;
}
