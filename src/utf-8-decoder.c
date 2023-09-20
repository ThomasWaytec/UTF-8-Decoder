#include <stdio.h>
#include <stdlib.h>

#define BYTE 8
#define SHIFT (BYTE - 2) /* the shift value for the first code unit of a unit sequence (BYTE length - first code unit's length)*/

typedef unsigned int CodeUnit;
typedef unsigned int CodePoint; /* has to be an int to check for EOF while reading file */

/*
Counts the number of continuous leading 1s in a code unit and trims those 1s. (in binary) 
(if it's the first code unit of a sequence,
the number of leading 1s is equal to the number of code units left in the code unit sequence.)
*/
size_t parse_code_unit(CodeUnit* code_unit) {
    size_t count = 0;

    for (size_t i = BYTE - 1; *code_unit & (1 << i); i--) {
        count++;
        *code_unit &= ~(1 << i); /* trim leading 1s */
    }
        
    return count;
}

/* extracts the code point from all the noninitial (meaning: not first) code units */
void parse_nonitial_code_units(CodePoint* code_point, size_t code_units_left, FILE* file) {

    CodeUnit current_code_unit;
    while (code_units_left--)
    {
        /* parse code unit */
        current_code_unit = fgetc(file);
        printf("    current_code_unit=%d\n", current_code_unit);
        parse_code_unit(&current_code_unit);
        printf("    current_code_unit=%d\n", current_code_unit);
        printf("    code_point=%d\n", *code_point);
        //*code_point = *code_point | (current_code_unit << BYTE*code_units_left + 1);   
        *code_point = *code_point | (current_code_unit << SHIFT*code_units_left);   

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


    CodeUnit first_code_unit; 
    size_t code_units_left; /* number of code units left in the code unit sequence */
    CodePoint current_code_point;
    while ((first_code_unit = fgetc(file)) != EOF)
    {

        current_code_point = 0;
        /* parse 1st byte of code unit sequence */
        printf("first_code_unit=%d\n", first_code_unit);
        code_units_left = parse_code_unit(&first_code_unit);

        if (code_units_left) {code_units_left -= 1;} /* subtract the first code unit which was just parsed */

        /* add the parsed first code unit to the code point */
        current_code_point = current_code_point | (first_code_unit << (SHIFT*code_units_left)); 
        
        //printf("code_units_left=%d\n", code_units_left);
        printf("first_code_unit=%d\n", first_code_unit);
        //printf("current_code_point=%d\n", current_code_point);

        /* parse and add to the code point the remaining code units if there are any */
        if (code_units_left) {
            parse_nonitial_code_units(&current_code_point, code_units_left, file);    
        }
    

        printf("current_code_point=%d\n", current_code_point);
        printf("\n");


        
    }

    return 0;
}