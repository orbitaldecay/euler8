/*
	e8asm.c
	Bob Forder
	09/20/22
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "e8asm.h"

int main(int argc, char **argv) {
	FILE* f;
	FILE* g;
	char* b;
	long fs;

	/* If two arguments weren't provided, then print usage message and exit */
	if (argc != 3) {
		printf("Usage: e8asm inputfile outputfile\n");
		return -1;
	}

	/* Open first argument as filename for reading */
	f = fopen(argv[1], "rb");
	if (!f) {
		fprintf(stderr, "Failed to open file \"%s\" for input\n", argv[1]);
		return -1;
	}

	/* Open second argument as filename for writing */
	g = fopen(argv[2], "wb");
	if (!g) {
		fprintf(stderr, "Failed to open file \"%s\" for output\n", argv[2]);
		fclose(f);
		return -1;
	}

	/* Load input file to memory buffer and close file */
	if (fseek(f, 0, SEEK_END) != 0) {
		fprintf(stderr, "Error seeking end of file\n");
		fclose(f);
		fclose(g);
		return -1;
	}
	fs = ftell(f);
	if (fseek(f, 0, SEEK_SET) != 0) {
		fprintf(stderr, "Error seeking begining of file\n");
		fclose(f);
		fclose(g);
		return -1;
	}
	b = calloc(fs + 1, 1);
	if (!b) {
		fprintf(stderr, "Error allocating memory\n");
		fclose(f);
		fclose(g);
		return -1;
	}
	if (fread(b, fs, 1, f) != 1)
	{
		fprintf(stderr, "Error reading\n");
		free(b);
		fclose(f);
		fclose(g);
		return -1;
	}
	fclose(f);

	/* Run assembler loop */
	assemble(b, g);

	/* Flush the buffer if we're not byte aligned */
	write_nibble(g, 0);

	/* Cleanup and exit */
	free(b);
	fclose(g);
	return 0;
}

void write_nibble(FILE* fout, unsigned char v) {
	static unsigned char buffer = 0;
	static int high_nibble = 0;
	if (high_nibble) {
		buffer = buffer | ((v & 15) << 4);
		fwrite(&buffer, 1, 1, fout);
		buffer = 0;
		high_nibble = 0;
	} else {
		buffer = v & 15;
		high_nibble = 1;
	}
	return;
}

void write_byte(FILE* fout, unsigned char v) {
	write_nibble(fout, v & 15);
	write_nibble(fout, (v >> 4) & 15);
}

void assemble(char* b, FILE* fout) {
	char* token = strtok(b, " \t\n\v\f\r");
	char* t;
	int v;
	while (token) {
		if (strcmp(token, "nop") == 0) {
			write_nibble(fout, NOP);
		} else if (strcmp(token, "z") == 0) {
			write_nibble(fout, Z);
		} else if (strcmp(token, "t") == 0) {
			write_nibble(fout, T);
		} else if (strcmp(token, "s") == 0) {
			write_nibble(fout, S);
		} else if (strcmp(token, "pi") == 0) {
			write_nibble(fout, PI);
		} else if (strcmp(token, "i") == 0) {
			write_nibble(fout, I);
		} else if (strcmp(token, "con") == 0) {
			write_nibble(fout, CON);
		} else if (strcmp(token, "arg") == 0) {
			write_nibble(fout, ARG);
		} else if (strcmp(token, "abs") == 0) {
			write_nibble(fout, ABS);
		} else if (strcmp(token, "add") == 0) {
			write_nibble(fout, ADD);
		} else if (strcmp(token, "sub") == 0) {
			write_nibble(fout, SUB);
		} else if (strcmp(token, "mul") == 0) {
			write_nibble(fout, MUL);
		} else if (strcmp(token, "div") == 0) {
			write_nibble(fout, DIV);
		} else if (strcmp(token, "dup") == 0) {
			write_nibble(fout, DUP);
		} else if (strcmp(token, "im") == 0) {
			write_byte(fout, IM);
		} else if (strcmp(token, "re") == 0) {
			write_byte(fout, RE);
		} else if (strcmp(token, "sin") == 0) {
			write_byte(fout, SIN);
		} else if (strcmp(token, "cos") == 0) {
			write_byte(fout, COS);
		} else if (strcmp(token, "asin") == 0) {
			write_byte(fout, ASIN);
		} else if (strcmp(token, "acos") == 0) {
			write_byte(fout, ACOS);
		} else if (strcmp(token, "exp") == 0) {
			write_byte(fout, EXP);
		} else if (strcmp(token, "ln") == 0) {
			write_byte(fout, LN);
		} else if (strcmp(token, "pow") == 0) {
			write_byte(fout, POW);
		} else if (strcmp(token, "sqrt") == 0) {
			write_byte(fout, SQRT);
		} else if (strcmp(token, "cis") == 0) {
			write_byte(fout, CIS);
		} else {
			v = strtol(token, &t, 10);
			if (t - token == strlen(token)) {
				write_nibble(fout, IMM);
				write_nibble(fout, v);
			} else {
				fprintf(stderr, "WARNING: Invalid token \"%s\"\n", token);
			}
		}
		token = strtok(NULL, " \t\n\v\f\r");
	}
}