
#include <stdio.h>
#include <rpc/rpc.h>
#include "const.h"

int main(int argc, char *argv[])
{
	//char *pd;
	int stat;
	int nota;
	int out;
	MANAGEMENT test;

	test.agency = 1;
	test.cpf = "4236748";
	test.first_name = "AUGUSTo";
	test.last_name = "bergamin";
	test.operation_ID = 201;
	test.type = 1;


	stat = callrpc("localhost", BANKPROG, BANKVERS, MANAGEMENT_OP,
		       (xdrproc_t)xdr_management, (char *)&test,
		       (xdrproc_t)xdr_int, (char *)&out );
	if	(stat!= 0)  {
		clnt_perrno(stat);
		printf("\n");
		return 1;
	}

	printf("%d\n", out);

	test.type = 2;
	test.account_number = out;

	stat = callrpc("localhost", BANKPROG, BANKVERS, MANAGEMENT_OP,
		       (xdrproc_t)xdr_management, (char *)&test,
		       (xdrproc_t)xdr_int, (char *)& out);
	if	(stat!= 0)  {
		clnt_perrno(stat);
		printf("\n");
		return 1;
	}
	printf("%d\n", out);

	test.type = 3;

	stat = callrpc("localhost", BANKPROG, BANKVERS, MANAGEMENT_OP,
		       (xdrproc_t)xdr_management, (char *)&test,
		       (xdrproc_t)xdr_int, (char *)& out);
	if	(stat!= 0)  {
		clnt_perrno(stat);
		printf("\n");
		return 1;
	}
	printf("%d\n", out);

	test.type = 2;

	stat = callrpc("localhost", BANKPROG, BANKVERS, MANAGEMENT_OP,
		       (xdrproc_t)xdr_management, (char *)&test,
		       (xdrproc_t)xdr_int, (char *)& out);
	if	(stat!= 0)  {
		clnt_perrno(stat);
		printf("\n");
		return 1;
	}
	printf("%d\n", out);

	test.type = 1;
	stat = callrpc("localhost", BANKPROG, BANKVERS, MANAGEMENT_OP,
		       (xdrproc_t)xdr_management, (char *)&test,
		       (xdrproc_t)xdr_int, (char *)&out );
	if	(stat!= 0)  {
		clnt_perrno(stat);
		printf("\n");
		return 1;
	}

	printf("%d\n", out);


	return 0;
}
