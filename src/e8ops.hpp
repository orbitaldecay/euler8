/*
	e8ops.hpp
	Bob Forder
	09/20/22
*/
#ifndef E8OPS_HPP
#define E8OPS_HPP

#include <list>
#include <complex>

typedef std::complex<double> arg_t;
typedef std::list<arg_t> argstack_t;
typedef void (*operation_t) (argstack_t*, arg_t, arg_t, arg_t);
typedef std::list<operation_t> program_t;

int read_nibble(FILE* f);
void prog_load(FILE* f, program_t* p);
void prog_run(program_t* p, argstack_t* a, arg_t z, arg_t t, arg_t s);

void op_nop(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_z(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_t(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_s(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_pi(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_i(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_con(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_arg(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_abs(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_add(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_sub(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_mul(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_div(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_dup(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_im(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_re(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_sin(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_cos(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_asin(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_acos(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_nop(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_exp(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_ln(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_pow(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_sqrt(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_cis(argstack_t* a, arg_t z, arg_t t, arg_t s);

void op_immn8(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_immn7(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_immn6(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_immn5(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_immn4(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_immn3(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_immn2(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_immn1(argstack_t* a, arg_t z, arg_t t, arg_t s);

void op_imm0(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_imm1(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_imm2(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_imm3(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_imm4(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_imm5(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_imm6(argstack_t* a, arg_t z, arg_t t, arg_t s);
void op_imm7(argstack_t* a, arg_t z, arg_t t, arg_t s);

operation_t TRANSLATE[256] = {
	op_nop,
	op_z,
	op_t,
	op_s,
	op_pi,
	op_i,
	op_imm0,
	op_con,
	op_arg,
	op_abs,
	op_add,
	op_sub,
	op_mul,
	op_div,
	op_dup,
	op_im,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_imm1,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_re,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_imm2,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_sin,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_imm3,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_cos,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_imm4,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_asin,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_imm5,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_acos,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_imm6,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_exp,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_imm7,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_ln,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_immn8,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_pow,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_immn7,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_sqrt,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_immn6,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_cis,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_immn5,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_immn4,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_immn3,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_immn2,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,

	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_immn1,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop,
	op_nop
};

#endif