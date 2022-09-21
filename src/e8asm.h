/*
	e8asm.h
	Bob Forder
	09/20/2022
*/
#ifndef E8ASM_H
#define E8ASM_H

#include "e8opcodes.h"

void write_nibble(FILE* fout, unsigned char v);
void write_byte(FILE* fout, unsigned char v);
void assemble(char* b, FILE* fout);

#endif