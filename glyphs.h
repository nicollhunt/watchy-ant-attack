#ifndef GLYPHS_H
#define GLYPHS_H

const unsigned char num_one [] PROGMEM = {
1, 1, 0,
0, 1, 0,
0, 1, 0,
0, 1, 0,
1, 1, 1
};

const unsigned char num_two [] PROGMEM = {
1, 1, 1,
0, 0, 1,
1, 1, 1,
1, 0, 0,
1, 1, 1
};

const unsigned char num_three [] PROGMEM = {
1, 1, 1,
0, 0, 1,
1, 1, 1,
0, 0, 1,
1, 1, 1
};

const unsigned char num_four [] PROGMEM = {
1, 0, 1,
1, 0, 1,
1, 1, 1,
0, 0, 1,
0, 0, 1
};

const unsigned char num_five [] PROGMEM = {
1, 1, 1,
1, 0, 0,
1, 1, 1,
0, 0, 1,
1, 1, 1
};

const unsigned char num_six [] PROGMEM = {
1, 1, 1,
1, 0, 0,
1, 1, 1,
1, 0, 1,
1, 1, 1
};

const unsigned char num_seven [] PROGMEM = {
1, 1, 1,
1, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1
};

const unsigned char num_eight [] PROGMEM = {
1, 1, 1,
1, 0, 1,
1, 1, 1,
1, 0, 1,
1, 1, 1
};

const unsigned char num_nine [] PROGMEM = {
1, 1, 1,
1, 0, 1,
1, 1, 1,
0, 0, 1,
0, 0, 1
};

const unsigned char num_zero [] PROGMEM = {
1, 1, 1,
1, 0, 1,
1, 0, 1,
1, 0, 1,
1, 1, 1
};

const unsigned char* glyph_numbers[10] PROGMEM = {
   	num_zero,
    num_one,
    num_two,
    num_three,
    num_four,
    num_five,
    num_six,
    num_seven,
    num_eight,
    num_nine
};

const unsigned char glyph_colon [] PROGMEM = {
0, 0, 0,
0, 1, 0,
0, 0, 0,
0, 1, 0,
0, 0, 0
};

#endif
