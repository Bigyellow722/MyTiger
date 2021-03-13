#include "interpreter.h"
#include <stdio.h>
#define RECURSION 1
Table_ interpStm(A_stm s, Table_ t);
struct IntAndTable interpExp(A_exp exp, Table_ t);
struct IntAndTable interpExpList(A_expList explist, Table_ t);

Table_ table_update(string id, int value, struct table *tail) {
    Table_ t = checked_malloc(sizeof(*t));
    t->id = id;
    t->value = value;
    t->tail = tail;
    return t;
}


/* find the node whose id match the key at the first time
 * and return the value of the node
 */
int lookup(Table_ t, string key) {
    while (t != NULL) {
	if (t->id == key) {
	    return t->value;
	}
	t = t->tail;
    }
    return 0;
}


struct IntAndTable interpExp(A_exp exp, Table_ t) {
    struct IntAndTable it1;
    struct IntAndTable it2, it3;
    it1.i = 0;
    it1.t = NULL;
    switch (exp->kind) {
    case A_idExp:
	{
	    it1.i = lookup(t, exp->u.id);
	    it1.t = t;
	    break;
	}
    case A_numExp:
	{
	    it1.i = exp->u.num;
	    it1.t = t;
	    break;
	}
    case A_opExp:
	{
	    it2 = interpExp(exp->u.op.left, t);
	    it3 = interpExp(exp->u.op.right, it2.t);
	    switch (exp->u.op.oper) {
	    case A_plus:
		{
		    it1.i = it2.i + it3.i;
		    break;
		}
	    case A_minus:
		{
		    it1.i = it2.i - it3.i;
		    break;
		}
	    case A_times:
		{
		    it1.i = it2.i * it3.i;
		    break;
		}
	    case A_div:
		{
		    it1.i = it2.i / it3.i;
		    break;
		}
	    }
	    it1.t = it2.t;
	    break;
	}
    case A_eseqExp:
	{
	    Table_ t6 = interpStm(exp->u.eseq.stm, t);
	    it1 = interpExp(exp->u.eseq.exp, t6);
	    break;
	}
    default:
	break;
    }
    return it1;
}

#ifdef RECURSION
struct IntAndTable interpExpList(A_expList explist, Table_ t)
{
    struct IntAndTable it1;
    switch (explist->kind) {
    case A_pairExpList:
	{
	    it1 = interpExp(explist->u.pair.head, t);
	    printf("%d ", it1.i);
	    return interpExpList(explist->u.pair.tail, it1.t);
	}
    case A_lastExpList:
	{
	    it1 = interpExp(explist->u.last, t);
	    printf("%d\n", it1.i);
	    return it1;
	}
    }

}
#endif

Table_ interpStm(A_stm s, Table_ t) {
    struct IntAndTable it1;
    switch (s->kind) {
    case A_compoundStm:
	{
	    Table_ t1 = interpStm(s->u.compound.stm1, t);
	    return interpStm(s->u.compound.stm2, t1);
	}
    case A_assignStm:
	{
	    it1 = interpExp(s->u.assign.exp, t);
	    return table_update(s->u.assign.id, it1.i, it1.t);
	}
    case A_printStm:
	{
#ifdef RIECURSION
	    it1 = interpExpList(s->u.print.exps, t);
#else
	    A_expList exps = s->u.print.exps;
	    while (exps->kind != A_lastExpList) {
		it1 = interpExp(exps->u.pair.head, t);
		printf("%d ", it1.i);
		exps = exps->u.pair.tail;
		t = it1.t;
	    }
	    it1 = interpExp(exps->u.last, t);
	    printf("%d\n", it1.i);
#endif
	    return it1.t;
	}
    }
}

void print_table(Table_ t)
{
    Table_ cur = t;
    while (cur) {
	printf("id: %s, value: %d\n",cur->id, cur->value);
	cur = cur->tail;
    }

}

void interp(A_stm stm) {
    interpStm(stm, NULL);
}
