#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "slp.h"
#include "prog1.h"

int maxargs(A_stm stm);
int maxargs_exp(A_exp exp);
int maxargs_explist(A_expList explist);
int countargs(A_expList explist);

int maxargs_exp(A_exp exp) {
	if (exp == NULL)
		return 0;

	switch(exp->kind) {
		case A_idExp:
		case A_numExp:
			return 0;
		case A_opExp:
			return maxargs_exp(exp->u.op.left) > maxargs_exp(exp->u.op.right) ? maxargs_exp(exp->u.op.left) : maxargs_exp(exp->u.op.right);
		case A_eseqExp:
			return maxargs(exp->u.eseq.stm) > maxargs_exp(exp->u.eseq.exp) ? maxargs(exp->u.eseq.stm) : maxargs_exp(exp->u.eseq.exp);
	}
}


int maxargs_explist(A_expList explist) {
	if (explist == NULL)
		return 0;

	switch(explist->kind) {
		case A_pairExpList:
			return maxargs_exp(explist->u.pair.head) > maxargs_explist(explist->u.pair.tail) ? maxargs_exp(explist->u.pair.head) : maxargs_explist(explist->u.pair.tail);
		case A_lastExpList:
			return maxargs_exp(explist->u.last);

	}
}

int countargs(A_expList explist) {
	if(explist->kind == A_pairExpList)
		return 1 + countargs(explist->u.pair.tail);
	else
		return 1;
}

int maxargs(A_stm stm) {
	if (stm == NULL)
		return 0;

	switch(stm->kind) {
		case A_compoundStm:
			return maxargs(stm->u.compound.stm1) > maxargs(stm->u.compound.stm2) ? maxargs(stm->u.compound.stm1) : maxargs(stm->u.compound.stm2);
		case A_assignStm:
			return maxargs_exp(stm->u.assign.exp);
		case A_printStm:
			return maxargs_explist(stm->u.print.exps) > countargs(stm->u.print.exps) ? maxargs_explist(stm->u.print.exps) : countargs(stm->u.print.exps);
	}
}

int main(void) {
	A_stm tmp = prog();
	int res = maxargs(tmp);
	printf("%d\n",res);
	return 0;
}
