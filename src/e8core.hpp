/*
	e8ops.hpp
	Bob Forder
	09/20/22
*/
#ifndef E8CORE_HPP
#define E8CORE_HPP

#include <list>
#include <complex>
#include <vector>

typedef std::complex<double> arg_t;
typedef std::vector<arg_t> argstack_t;
typedef struct operator_args_t_ {
	argstack_t* a;
	arg_t z;
	arg_t t;
	arg_t s;
} operator_args_t;	


typedef void (*operation_t) (operator_args_t* args);
typedef std::vector<operation_t> program_t;

int read_nibble(FILE* f);
void prog_load(FILE* f, program_t* p);
inline void prog_run(program_t* p, operator_args_t* args);

void op_nop(operator_args_t* args);
void op_z(operator_args_t* args);
void op_t(operator_args_t* args);
void op_s(operator_args_t* args);
void op_pi(operator_args_t* args);
void op_i(operator_args_t* args);
void op_con(operator_args_t* args);
void op_arg(operator_args_t* args);
void op_abs(operator_args_t* args);
void op_add(operator_args_t* args);
void op_sub(operator_args_t* args);
void op_mul(operator_args_t* args);
void op_div(operator_args_t* args);
void op_dup(operator_args_t* args);
void op_im(operator_args_t* args);
void op_re(operator_args_t* args);
void op_sin(operator_args_t* args);
void op_cos(operator_args_t* args);
void op_asin(operator_args_t* args);
void op_acos(operator_args_t* args);
void op_nop(operator_args_t* args);
void op_exp(operator_args_t* args);
void op_ln(operator_args_t* args);
void op_pow(operator_args_t* args);
void op_sqrt(operator_args_t* args);
void op_cis(operator_args_t* args);

void op_immn8(operator_args_t* args);
void op_immn7(operator_args_t* args);
void op_immn6(operator_args_t* args);
void op_immn5(operator_args_t* args);
void op_immn4(operator_args_t* args);
void op_immn3(operator_args_t* args);
void op_immn2(operator_args_t* args);
void op_immn1(operator_args_t* args);

void op_imm0(operator_args_t* args);
void op_imm1(operator_args_t* args);
void op_imm2(operator_args_t* args);
void op_imm3(operator_args_t* args);
void op_imm4(operator_args_t* args);
void op_imm5(operator_args_t* args);
void op_imm6(operator_args_t* args);
void op_imm7(operator_args_t* args);

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