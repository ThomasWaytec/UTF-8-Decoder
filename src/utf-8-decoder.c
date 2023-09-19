#include <stdio.h>
#include <stdlib.h>

typedef unsigned int CodePoint;

/*
Counts the number of continuous leading 1s in a byte and trims them. (in binary) 
The number of leading 1s is equal to the number of code units left in the code unit sequence. (if it's the first code unit of a sequence).
*/
size_t parse_code_unit(unsigned char* byte) {
    size_t count = 0;

    for (size_t i = 7; *byte & (1 << i); i--) {
        count++;
        *byte &= ~(1 << i); // trim leading 1
    }
        
    return count;
}

/* counts the number of continuous leading 0s in a byte (in binary) */
size_t count_lead_0s(unsigned char byte) {
    if (!byte) {return 8;}
    size_t count = 0;

    for (size_t i = 7; !(byte & (1 << i)); i--) {
        count++;
    }
        
    return count;
}


parse_nonitial_code_units(FILE* file, CodePoint* code_point, size_t code_units_left) {

    unsigned char current_code_unit;
    while (code_units_left--)
    {
        /* parse code unit */
        current_code_unit = fgetc(file);
        parse_code_unit(&current_code_unit);

        *code_point = current_code_unit << code_units_left;   
    }

    
}



int main(void) {
    
    const char* FILE_NAME = "samples/basic/2-byte-char.txt";
    FILE* file = fopen(FILE_NAME, "rb");


    /* get file size */
    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file); 
    fseek(file, 0, SEEK_SET);
    printf("file_size=%d\n\n", FILE_SIZE);


    CodePoint current_code_point;
    int first_code_unit; // has to be an int to check for EOF
    size_t code_units_left; // number of code units left in the code unit sequence

    
    while ((first_code_unit = fgetc(file)) != EOF)
    {

        /* parse 1st byte of code unit sequence */
        printf("first_code_unit=%d\n", first_code_unit);
        first_code_unit = (unsigned char)first_code_unit;
        code_units_left = parse_code_unit(&first_code_unit);

        //if (code_units_left) {code_units_left -= 1;} /* substract the 1st code unit itself which was just parsed */
        printf("code_units_left=%d\n", code_units_left);
        printf("first_code_unit=%d\n", first_code_unit);
        current_code_point = first_code_unit << code_units_left;
        printf("\n");

        
    }

    /* merge add n to code point */
    // after all the trimming has been done

    /* merge bytes */
    //unsigned int code_point;
    //code_point = (code_point << 8) | n;
    //printf("%d\n", code_point);

    return 0;
}