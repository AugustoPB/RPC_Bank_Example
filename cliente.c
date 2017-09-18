/* cliente.c (Roland Teodorowitsch; 30 ago. 2013 - 31 mar. 2017) */

#include <stdio.h>
#include <rpc/rpc.h>
#include "const.h"

int main(int argc, char *argv[])
{
	//char *pd;
	int stat;
	double nota;
	MANAGEMENT test;

	if	(argc!=3)  {
		fprintf(stderr,"Uso:\n%s <nome_do_servidor> <nome>\n\n",argv[0]);
		return 1;
	}
	test.b = argv[2];
	test.a = 3;
	stat = callrpc(argv[1], BANKPROG, BANKVERS, MANAGEMENT_OP,
		       (xdrproc_t)xdr_management, (char *)&test,
		       (xdrproc_t)xdr_double, (char *)&nota );
	if	(stat!= 0)  {
		clnt_perrno(stat);
		printf("\n");
		return 1;
	}
	printf("Nome: %s\n",argv[2]);
	if	(nota<0.0)
		printf("Resultado: nome nao encontrado!\n");
	else
		printf("Nota: %.1lf\n",nota);
	return 0;
}
