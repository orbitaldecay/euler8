#include <iostream>
#include "e8core.hpp"
#include "e8opcodes.h"

int main(int argc, char** argv)
{
	program_t p;
	argstack_t a;
	arg_t z(1, 3);
	arg_t t(2, 0);
	arg_t s(0, 0);
	FILE* f;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: e8ops cartfile\n");
		return -1;
	}
	f = fopen(argv[1], "rb");
	if (!f)
	{
		fprintf(stderr, "Unable to open \"%s\"\n", argv[1]);
		return -1;
	}
	prog_load(f, &p);
	fclose(f);

	prog_run(&p, &a, z, t, s);

	z = a.front();
	a.pop_front();
	std::cout << z;
}

void prog_load(FILE* f, program_t* p)
{
	int v, t;
	while ((v = read_nibble(f)) != -1)
	{
		if (v == 6 || v == 15)
		{
			t = read_nibble(f);
			if (t == -1) t = 0;
			v |= (t << 4);
		}
		p->push_back(TRANSLATE[v]);
	}
	return;
}

int read_nibble(FILE* f)
{
	static unsigned char buffer = 0;
	static int high_nibble = 0;
	int v = -1;
	if (!high_nibble)
	{
		if (fread(&buffer, 1, 1, f) != 0)
		{
			v = buffer & 15;
			high_nibble = 1;
		}
	}
	else
	{
		v = (buffer >> 4) & 15;
		high_nibble = 0;
	}
	return v;
}

inline void prog_run(program_t* p, argstack_t* a, arg_t z, arg_t t, arg_t s)
{	
	unsigned int i;
	for (i = 0; i < p->size(); i++)
	{
		(*p)[i](a, z, t, s);
	}
	return;
}

void op_nop(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	return;
}

void op_z(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(z);
}

void op_t(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(t);
}

void op_s(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(s);
}

void op_pi(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(3.14159265358979323846, 0));
}

void op_i(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(0, 1));
}

void op_con(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::conj(x));
}

void op_arg(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::arg(x));
}

void op_abs(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::abs(x));
}

void op_add(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t y = a->front();
	a->pop_front();
	arg_t x = a->front();
	a->pop_front();
	a->push_front(x + y);
}

void op_sub(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t y = a->front();
	a->pop_front();
	arg_t x = a->front();
	a->pop_front();
	a->push_front(x - y);
}

void op_mul(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t y = a->front();
	a->pop_front();
	arg_t x = a->front();
	a->pop_front();;
	a->push_front(x * y);
}

void op_div(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t y = a->front();
	a->pop_front();
	arg_t x = a->front();
	a->pop_front();
	a->push_front(x / y);
}

void op_dup(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(x);
	a->push_front(x);
}

void op_im(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::imag(x));
}

void op_re(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::real(x));
}

void op_sin(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::sin(x));
}

void op_cos(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::cos(x));
}

void op_asin(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::asin(x));
}

void op_acos(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::acos(x));
}

void op_exp(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::exp(x));
}

void op_ln(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::log(x));
}

void op_pow(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t y = a->front();
	a->pop_front();
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::pow(x, y));
}

void op_sqrt(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::sqrt(x));
}

void op_cis(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	arg_t i(0,1);
	arg_t x = a->front();
	a->pop_front();
	a->push_front(std::cos(x) + i * std::sin(x));
}

void op_immn8(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(-8, 0));
}

void op_immn7(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(-7, 0));
}

void op_immn6(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(-6, 0));
}

void op_immn5(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(-5, 0));
}

void op_immn4(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(-4, 0));
}

void op_immn3(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(-3, 0));
}

void op_immn2(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(-2, 0));
}

void op_immn1(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(-1, 0));
}

void op_imm0(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(0, 0));
}

void op_imm1(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(1, 0));
}

void op_imm2(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(2, 0));
}

void op_imm3(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(3, 0));
}

void op_imm4(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(4, 0));
}

void op_imm5(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(5, 0));
}

void op_imm6(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(6, 0));
}

void op_imm7(argstack_t* a, arg_t z, arg_t t, arg_t s)
{
	a->push_front(arg_t(7, 0));
}
