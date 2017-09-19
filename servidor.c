#include "administration.h"
#include "const.h"

AGENCY agencies[5];

//double *obtem_nota_1_svc(struct simple *test)
//{
//	char **nome = &test->b;
//	static NOTAS notas[NUM_ALUNOS] = {
//		{"Alexandre", 9.5},
//		{"Barbara",   8.5},
//		{"Joao",      6.5},
//		{"Maria",     9.0},
//		{"Paulo",    10.0},
//		{"Pedro",     7.0}
//	};
//	static double erro = -1.0;
//	int i;
//
//	for	(i=0;i<NUM_ALUNOS;++i)
//		if	(strcmp(notas[i].nome,*nome)==0)
//			return &(notas[i].nota);
//	return &erro;
//}
int create_account(MANAGEMENT *operation)
{
	ACCOUNT new_account;
	new_account.first_name = operation->first_name;
	new_account.last_name = operation->last_name;
	new_account.cpf = operation->cpf;
	new_account.agency = operation->agency;
	new_account.balance = 0;


	if(agencies[operation->agency-1].agency != operation->agency)
		return -2;

	int iterator;
	for(iterator = 0; iterator < MAX_ACCOUNTS_NUMBER; iterator++)
	{
		if(agencies[operation->agency-1].accounts[iterator].account_number == 0)
		{
			new_account.account_number = iterator+1;
			agencies[operation->agency-1].accounts[iterator] = new_account;
			return new_account.account_number;
		}
	}
	return -1;
}

double *obtem_nota_1_svc(MANAGEMENT *operation)
{
	static double a;

	a = create_account(operation);
	return &a;
}

int main()
{
	agencies[0].agency = 1;
	if	(registerrpc(BANKPROG,BANKVERS,MANAGEMENT_OP,obtem_nota_1_svc,
			     (xdrproc_t)xdr_management,(xdrproc_t)xdr_double ) == -1)  {
		fprintf(stderr,"Erro em registerrpc()!\n");
		exit(1);
	}
	svc_run();
	fprintf(stderr,"Erro em svc_run()!\n");
	return 1;
}
