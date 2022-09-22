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

typedef std::complex<float> arg_t;
typedef struct argstack_t_ {
	int sp;
	arg_t stack[256];
	void push_back(arg_t x) {
		stack[++sp] = x;
	}
	arg_t back() {
		return stack[sp];
	}
	void pop_back() {
		--sp;
	}
	void clear() {
		sp = -1;
	}
} argstack_t;
typedef struct operator_args_t_ {
	argstack_t* a;
	arg_t z;
	arg_t t;
	arg_t s;
} operator_args_t;	


typedef void (*operation_t) (operator_args_t* args);
typedef std::vector<operation_t> program_t;

void prog_load(FILE* f, program_t* p);
void prog_run(program_t* p, operator_args_t* args);

#endif