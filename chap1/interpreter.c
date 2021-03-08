#include "util.h"
#include "slp.h"
#include "interpreter.h"


Table_ Table(string id, int value, struct table *tail) {
	Table_ t = checked_malloc(sizeof(*t));
	t->id = id;
	t->value = value;
	t->tail = tail;
	return t;
}

Table_ interpStm(A_stm s, Table_ t) {
	switch (s.kind){
		case A_compoundStm:
			Table_ t1 = interpStm(s.compound.stm1, t);
			return interpStm(stm.compound.stm2, t1);
		case A_assignStm:


	}

}

Table_ interpExp(A_exp exp, Table_ t) {

}

int lookup(Table_ t, string key) {


}

Table_ update(Table_ t, string c, int value) {

}

void interp(A_stm stm) {
	
}
