#include <stdio.h>
#include <stdlib.h>

#define BYTE 8
#define SHIFT (BYTE - 2) /* the base shift value for the code units. Allows to merge many code units into a single codde point */

typedef unsigned int CodeUnit;  /* 
                                It has to be an int (even though code units are byte-sized) in order to:
                                    - check for EOF with it while reading a file
                                    - make it easily appendable to a code point
                                */

typedef unsigned int CodePoint;

/* 
Extracts the number of code units left in a sequence
by counting the number of continuous leading 1s (in binary) in the first code unit.
(if it's the first code unit of a sequence,
the number of code units left is equal to
the number of leading 1s in the code unit sequence (minus one if the number of leading 1s are larger than 0))
*/
size_t extract_code_units_left(CodeUnit code_unit) {
    size_t code_units_left = 0;

    for (size_t i = BYTE - 1; code_unit & (1 << i); i--) {
        code_units_left++;
    }

    if (code_units_left) {code_units_left -= 1;}
    return code_units_left;
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


int main(void) {
    
    const char* FILE_NAME = "samples/basic/alice_in_wonderland.txt";
    FILE* file = fopen(FILE_NAME, "rb");


    /* get file size */
    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file); 
    fseek(file, 0, SEEK_SET);


    CodePoint current_code_point;
    size_t code_units_left; /* number of code units left in the code unit sequence */
    CodeUnit first_code_unit;
    CodeUnit noninitial_code_unit;
    while ((first_code_unit = fgetc(file)) != EOF)
    {
        /* reset code point */
        current_code_point = 0;


        /* parse first code unit */
        code_units_left = extract_code_units_left(first_code_unit);
        trim_leading_1s(&first_code_unit);
        append_to_code_point(&first_code_unit, &current_code_point, code_units_left);



        /* parse all the noninitial (meaning: not first) code units */
        while (code_units_left--)
        {
            noninitial_code_unit = fgetc(file);
            trim_leading_1s(&noninitial_code_unit);
            append_to_code_point(&noninitial_code_unit, &current_code_point, code_units_left);
    
        }

    

        printf("current_code_point=%d\n", current_code_point);
        printf("\n");


        
    }

    return 0;
}