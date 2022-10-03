#include "vdc.h"

int d;

unsigned char *bitmap_to_array(SB *);

int find_empty_blocks(unsigned char*, SB *);

int find_first_empty_block(int, SB*);

void set_bitmap(unsigned char*, int);