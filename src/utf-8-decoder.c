#include <stdio.h>
#include <stdlib.h>

#define BYTE 8

typedef unsigned int CodeUnit;
typedef unsigned int CodePoint;


/*
Counts the number of continuous leading 1s in a code unit and trims them. (in binary) 
(if it's the first code unit of a sequence,
the number of leading 1s is equal to the number of code units left in the code unit sequence.)
*/
size_t parse_code_unit(CodeUnit* byte) {
    size_t count = 0;

    for (size_t i = BYTE - 1; *byte & (1 << i); i--) {
        count++;
        *byte &= ~(1 << i); // trim leading 1s
    }
        
    return count;
}


parse_nonitial_code_units(CodePoint* code_point, size_t code_units_left, FILE* file) {

    CodeUnit current_code_unit;
    while (code_units_left--)
    {
        /* parse code unit */
        current_code_unit = fgetc(file);
        parse_code_unit(&current_code_unit);
        printf("    current_code_unit=%d\n", current_code_unit);
        printf("    code_point=%d\n", *code_point);
        *code_point = *code_point | (current_code_unit << code_units_left*BYTE);   
    }

}
 


int main(void) {
    
    const char* FILE_NAME = "samples/basic/3-byte-char.txt";
    FILE* file = fopen(FILE_NAME, "rb");


    /* get file size */
    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file); 
    fseek(file, 0, SEEK_SET);
    printf("file_size=%d\n\n", FILE_SIZE);


    CodePoint current_code_point;
    CodeUnit first_code_unit; // has to be an int to check for EOF
    size_t code_units_left; // number of code units left in the code unit sequence

    
    while ((first_code_unit = fgetc(file)) != EOF)
    {

        /* parse 1st byte of code unit sequence */
        printf("first_code_unit=%d\n", first_code_unit);
        code_units_left = parse_code_unit(&first_code_unit);

        printf("code_units_left=%d\n", code_units_left);
        printf("first_code_unit=%d\n", first_code_unit);
        current_code_point = first_code_unit << (BYTE - code_units_left);
        printf("current_code_point=%d\n", current_code_point);

        if (code_units_left) {
            code_units_left -= 1; // subtract the first code unit which was just parsed
            parse_nonitial_code_units(&current_code_point, code_units_left, file);    
        }

        printf("current_code_point=%d\n", current_code_point);
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