
#include <stdio.h>
#include <rpc/rpc.h>
#include "const.h"

int main(int argc, char *argv[])
{
	//char *pd;
	int stat;
	double nota;
	MANAGEMENT test;

	test.agency = 1;
	test.cpf = "4236748";
	test.first_name = "AUGUSTo";
	test.last_name = "bergamin";
	test.operation_ID = 201;
	test.type = 1;


	stat = callrpc("localhost", BANKPROG, BANKVERS, MANAGEMENT_OP,
		       (xdrproc_t)xdr_management, (char *)&test,
		       (xdrproc_t)xdr_double, (char *)&nota );
	if	(stat!= 0)  {
		clnt_perrno(stat);
		printf("\n");
		return 1;
	}
	printf("%lf\n", nota);
	return 0;
}
