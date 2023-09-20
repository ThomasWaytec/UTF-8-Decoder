#include <stdio.h>
#include <stdlib.h>

#define BYTE 8
#define SHIFT (BYTE - 2) /* the base shift value for the code units. Allows to merge many code units into a single codde point */

typedef unsigned int CodeUnit;
typedef unsigned int CodePoint; /* has to be an int to check for EOF while reading file */

/* 
Counts the number of continuous leading 1s in a code unit (in binary) 
(if it's the first code unit of a sequence,
the number of leading 1s is equal to the number of code units left in the code unit sequence.)
*/
size_t count_leading_1s(CodeUnit code_unit) {
    size_t count = 0;

    for (size_t i = BYTE - 1; code_unit & (1 << i); i--) {
        count++;
    }
        
    return count;
}

/*
Trims the number of continuous leading 1s in a code unit (in binary) 
*/
size_t trim_leading_1s(CodeUnit* code_unit) {

    for (size_t i = BYTE - 1; *code_unit & (1 << i); i--) {
        *code_unit &= ~(1 << i); /* trim leading 1s */
    }
}

/* 
Appends a code unit to a code point
*/
void append_to_code_point(CodeUnit* code_unit, CodePoint* code_point, size_t code_units_left) {

    *code_point = *code_point | (*code_unit << SHIFT*code_units_left);
}

/* extracts the code point from all the noninitial (meaning: not first) code units */
void parse_nonitial_code_units(CodePoint* code_point, size_t code_units_left, FILE* file) {

    CodeUnit current_code_unit;
    while (code_units_left--)
    {
        /* parse code unit */
        current_code_unit = fgetc(file);
        trim_leading_1s(&current_code_unit);
        append_to_code_point(&current_code_unit, code_point, code_units_left);
        //*code_point = *code_point | (current_code_unit << SHIFT*code_units_left);   

    }

}
 


int main(void) {
    
    const char* FILE_NAME = "samples/basic/mixed-all.txt";
    FILE* file = fopen(FILE_NAME, "rb");


    /* get file size */
    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file); 
    fseek(file, 0, SEEK_SET);
    printf("file_size=%d\n\n", FILE_SIZE);


    CodePoint current_code_point;
    size_t code_units_left; /* number of code units left in the code unit sequence */
    CodeUnit first_code_unit; 
    while ((first_code_unit = fgetc(file)) != EOF)
    {
        /* reset code point */
        current_code_point = 0;

        /* parse first code unit */
        code_units_left = count_leading_1s(first_code_unit);
        trim_leading_1s(&first_code_unit);

        if (code_units_left) {code_units_left -= 1;} /* subtract the first code unit which was just parsed */

        /* add the parsed first code unit to the code point */
        append_to_code_point(&first_code_unit, &current_code_point, code_units_left);
        //current_code_point = current_code_point | (first_code_unit << SHIFT*code_units_left); 
        
        /* parse and add to the code point the remaining code units if there are any */
        if (code_units_left) {
            parse_nonitial_code_units(&current_code_point, code_units_left, file);    
        }
    

        printf("current_code_point=%d\n", current_code_point);
        printf("\n");


        
    }

    return 0;
}