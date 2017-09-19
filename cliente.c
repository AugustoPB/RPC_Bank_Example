
#include <stdio.h>
#include <rpc/rpc.h>
#include "const.h"

int main(int argc, char *argv[])
{
	//char *pd;
	int stat;
	int out;
	float value;
	MANAGEMENT test;
	TRANSACTION opt;

	test.agency = 1;
	sprintf(test.cpf, "4236748");
	sprintf(test.first_name, "AUGUSTo");
	sprintf(test.last_name, "bergamin");
	test.operation_ID = 201;
	test.type = CREATE;


	stat = callrpc("localhost", BANKPROG, BANKVERS, MANAGEMENT_OP,
		       (xdrproc_t)xdr_management, (char *)&test,
		       (xdrproc_t)xdr_int, (char *)&out );
	if	(stat!= 0)  {
		clnt_perrno(stat);
		printf("\n");
		return 1;
	}

	printf("%d\n", out);

	test.type = AUTHENTICATE;
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

	opt.account_number = test.account_number;
	opt.agency = test.agency;
	opt.operation_ID = 45678;
	opt.type = DEPOSIT;
	opt.value = 250;

	stat = callrpc("localhost", BANKPROG, BANKVERS, TRANSACTION_OP,
		       (xdrproc_t)xdr_transaction, (char *)&opt,
		       (xdrproc_t)xdr_float, (char *)& value);
	if	(stat!= 0)  {
		clnt_perrno(stat);
		printf("\n");
		return 1;
	}
	printf("%f\n", value);

	opt.type = BALANCE;

	stat = callrpc("localhost", BANKPROG, BANKVERS, TRANSACTION_OP,
		       (xdrproc_t)xdr_transaction, (char *)&opt,
		       (xdrproc_t)xdr_float, (char *)& value);
	if	(stat!= 0)  {
		clnt_perrno(stat);
		printf("\n");
		return 1;
	}
	printf("%f\n", value);

	opt.type = WITHDRAWAL;
	opt.value = 130;

	stat = callrpc("localhost", BANKPROG, BANKVERS, TRANSACTION_OP,
		       (xdrproc_t)xdr_transaction, (char *)&opt,
		       (xdrproc_t)xdr_float, (char *)& value);
	if	(stat!= 0)  {
		clnt_perrno(stat);
		printf("\n");
		return 1;
	}
	printf("%f\n", value);



	return 0;
}
