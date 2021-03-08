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



Table_ interpStm(A_stm s, Table_ t);

Table_ interpExp(A_exp exp, Table_ t);

Table_ update(Table_ t, string c, int value);

void interp(A_stm stm);


#endif
