/*
	e8asm.h
	Bob Forder
	09/20/2022
*/

// Opcodes

#define NOP	0x0
#define Z	0x1
#define T	0x2
#define S	0x3
#define PI	0x4
#define I	0x5
#define IMM	0x6
#define	CON	0x7
#define ARG	0x8
#define	ABS	0x9
#define	ADD	0xA
#define SUB	0xB
#define MUL	0xC
#define	DIV	0xD
#define DUP	0xE
#define	IM	0x0F
#define RE	0x1F
#define SIN	0x2F
#define COS	0x3F
#define ASIN	0x4F
#define ACOS	0x5F
#define EXP	0x6F
#define LN	0x7F
#define POW	0x8F
#define SQRT	0x9F
#define CIS	0xAF

void write_nibble(FILE* fout, unsigned char v);
void write_byte(FILE* fout, unsigned char v);
void assemble(char* b, FILE* fout);