#include <iostream>
#include <chrono>
#include "e8core_private.hpp"
#include "e8opcodes.h"

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

void prog_run(program_t* p, operator_args_t* args)
{	
	unsigned int i;
	unsigned int ps = p->size();
	for (i = 0; i < ps; i++)
	{
		(*p)[i](args);
	}
	return;
}

void op_nop(operator_args_t* args)
{
	return;
}

void op_z(operator_args_t* args)
{
	args->a->push_back(args->z);
}

void op_t(operator_args_t* args)
{
	args->a->push_back(args->t);
}

void op_s(operator_args_t* args)
{
	args->a->push_back(args->s);
}

void op_pi(operator_args_t* args)
{
	args->a->push_back(arg_t(3.14159265358979323846, 0));
}

void op_i(operator_args_t* args)
{
	args->a->push_back(arg_t(0, 1));
}

void op_con(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::conj(x));
}

void op_arg(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::arg(x));
}

void op_abs(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::abs(x));
}

void op_add(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t y = a->back();
	a->pop_back();
	arg_t x = a->back();
	a->pop_back();
	a->push_back(x + y);
}

void op_sub(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t y = a->back();
	a->pop_back();
	arg_t x = a->back();
	a->pop_back();
	a->push_back(x - y);
}

void op_mul(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t y = a->back();
	a->pop_back();
	arg_t x = a->back();
	a->pop_back();;
	a->push_back(x * y);
}

void op_div(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t y = a->back();
	a->pop_back();
	arg_t x = a->back();
	a->pop_back();
	a->push_back(x / y);
}

void op_dup(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->push_back(x);
}

void op_im(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::imag(x));
}

void op_re(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::real(x));
}

void op_sin(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::sin(x));
}

void op_cos(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::cos(x));
}

void op_asin(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::asin(x));
}

void op_acos(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::acos(x));
}

void op_exp(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::exp(x));
}

void op_ln(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::log(x));
}

void op_pow(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t y = a->back();
	a->pop_back();
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::pow(x, y));
}

void op_sqrt(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::sqrt(x));
}

void op_cis(operator_args_t* args)
{
	argstack_t* a = args->a;
	arg_t i(0,1);
	arg_t x = a->back();
	a->pop_back();
	a->push_back(std::exp(i * x));
}

void op_immn8(operator_args_t* args)
{
	args->a->push_back(arg_t(-8, 0));
}

void op_immn7(operator_args_t* args)
{
	args->a->push_back(arg_t(-7, 0));
}

void op_immn6(operator_args_t* args)
{
	args->a->push_back(arg_t(-6, 0));
}

void op_immn5(operator_args_t* args)
{
	args->a->push_back(arg_t(-5, 0));
}

void op_immn4(operator_args_t* args)
{
	args->a->push_back(arg_t(-4, 0));
}

void op_immn3(operator_args_t* args)
{
	args->a->push_back(arg_t(-3, 0));
}

void op_immn2(operator_args_t* args)
{
	args->a->push_back(arg_t(-2, 0));
}

void op_immn1(operator_args_t* args)
{
	args->a->push_back(arg_t(-1, 0));
}

void op_imm0(operator_args_t* args)
{
	args->a->push_back(arg_t(0, 0));
}

void op_imm1(operator_args_t* args)
{
	args->a->push_back(arg_t(1, 0));
}

void op_imm2(operator_args_t* args)
{
	args->a->push_back(arg_t(2, 0));
}

void op_imm3(operator_args_t* args)
{
	args->a->push_back(arg_t(3, 0));
}

void op_imm4(operator_args_t* args)
{
	args->a->push_back(arg_t(4, 0));
}

void op_imm5(operator_args_t* args)
{
	args->a->push_back(arg_t(5, 0));
}

void op_imm6(operator_args_t* args)
{
	args->a->push_back(arg_t(6, 0));
}

void op_imm7(operator_args_t* args)
{
	args->a->push_back(arg_t(7, 0));
}
