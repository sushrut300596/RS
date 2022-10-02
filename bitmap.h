#include "vdc.h"

int buf_size = 1024;

int d;

int size_bitmap;

unsigned char *bitmap_to_array(SB *);

void find_empty_blocks(unsigned char*, SB *);

void set_bitmap(unsigned char*);