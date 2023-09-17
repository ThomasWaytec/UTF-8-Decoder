#include <stdio.h>
#include <stdlib.h>


int main(void) {
    
    const char* FILE_NAME = "samples/basic/test.txt";

    FILE* file = fopen(FILE_NAME, "rb");

    /* get file size */
    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file); 
    fseek(file, 0, SEEK_SET);

    unsigned char current_byte;
    for (size_t i = 0; i < FILE_SIZE; i++) {
        current_byte = fgetc(file);

        printf("current_byte %d\n", current_byte);
    }

    return 0;
}