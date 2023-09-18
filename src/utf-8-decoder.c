#include <stdio.h>
#include <stdlib.h>

/* counts the number of continuous leading 1's in a byte and trims them. (in binary) */
size_t count_trim_lead_1s(unsigned char* byte) {
    const size_t BITMASK = 128; // a byte with the most significant bit set to 1: 10000000
    size_t count = 0;

    while (*byte & BITMASK) {
        count++;
        *byte <<= 1;
    }

    return count;
}

int main(void) {
    
    const char* FILE_NAME = "samples/basic/3-byte-char.txt";
    FILE* file = fopen(FILE_NAME, "rb");


    /* get file size */
    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file); 
    fseek(file, 0, SEEK_SET);



    unsigned int current_code_point;
    unsigned char current_byte;
    size_t leading_1s; // number of leading 1s of current_byte

    for (size_t i = 0; i < FILE_SIZE; i++) {
        current_byte = fgetc(file);
        printf("current_byte=%d\n", current_byte);        

        /* parse current byte */
        leading_1s = count_trim_lead_1s(&current_byte);
        
    }

    /* merge add n to code point */
    // after all the trimming has been done

    /* merge bytes */
    unsigned int code_point;
    code_point = (code_point << 8) | n;
    printf("%d\n", code_point);

    return 0;
}