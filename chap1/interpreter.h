#ifndef __INETRPRETER_H
#define __INETRPRETER_H

#include "slp.h"

typedef struct table *Table_;
struct table {
	string id;
	int value;
	Table_ tail;
};

struct IntAndTable {
	int i;
	Table_ t;
};


void interp(A_stm stm);

#endif
