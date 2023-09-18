#include <stdio.h>
#include <stdlib.h>

/* counts the number of continuous leading 1s in a byte and trims them. (in binary) */
size_t count_trim_lead_1s(unsigned char* byte) {
    size_t count = 0;

    for (size_t i = 7; *byte & (1 << i); i--) {
        count++;
        *byte &= ~(1 << i); // trim leading 1
    }
        
    return count;
}

/* counts the number of continuous leading 0s in a byte (in binary) */
size_t count_lead_0s(unsigned char byte) {
    size_t count = 0;

    for (size_t i = 7; !(byte & (1 << i)); i--) {
        count++;
    }
        
    return count;
}

int main(void) {
    
    const char* FILE_NAME = "samples/basic/2-byte-char.txt";
    FILE* file = fopen(FILE_NAME, "rb");


    /* get file size */
    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file); 
    fseek(file, 0, SEEK_SET);

    printf("file_size=%d\n\n", FILE_SIZE);

    unsigned int current_code_point;
    unsigned char current_byte;
    size_t no_of_leading_1s; // number of leading 1s in current_byte

    for (size_t i = 0; i < FILE_SIZE; i++) {
        current_byte = fgetc(file);
        printf("current_byte=%d\n", current_byte);

        /* parse current byte */
        no_of_leading_1s = count_trim_lead_1s(&current_byte);
        /* add to current code point */
        current_code_point = current_code_point << 8 | current_byte;
        printf("current_byte=%d\n", current_byte);


        /*
        for (size_t i = 0; i < no_of_leading_1s - 1; i++)
        {
            current_byte = fgetc(file); 
            count_trim_lead_1s(&current_byte); // trim leading 1s
            current_code_point = (current_code_point << 8) | current_byte;
            printf("current_byte=%d\n", current_byte);
              
        }
        */        
        printf("code_point=%d\n", current_code_point);
       
        
    }

    /* merge add n to code point */
    // after all the trimming has been done

    /* merge bytes */
    //unsigned int code_point;
    //code_point = (code_point << 8) | n;
    //printf("%d\n", code_point);

    return 0;
}