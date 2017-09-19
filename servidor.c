#include "administration.h"
#include "const.h"

AGENCY agencies[5];

float deposit(TRANSACTION *operation)
{
	if(agencies[operation->agency-1].agency != operation->agency)
		return NO_AGENCY;
	return agencies[operation->agency-1].accounts[operation->account_number-1].balance += operation->value;
}

float withdrawal(TRANSACTION *operation)
{
	if(agencies[operation->agency-1].agency != operation->agency)
		return NO_AGENCY;
	int balance = agencies[operation->agency-1].accounts[operation->account_number-1].balance - operation->value;
	if(balance < 0)
		return -1;
	else
		return balance;
}

float balance(TRANSACTION *operation)
{
	if(agencies[operation->agency-1].agency != operation->agency)
		return NO_AGENCY;
	return agencies[operation->agency-1].accounts[operation->account_number-1].balance;
}

int authentication(MANAGEMENT *operation)
{
	if(agencies[operation->agency-1].agency != operation->agency)
		return NO_AGENCY;
	//return operation->account_number-1;
	if(agencies[operation->agency-1].accounts[operation->account_number-1].account_number == operation->account_number)
		return operation->account_number;
	else
		return -1;
}

int create_account(MANAGEMENT *operation)
{
	if(agencies[operation->agency-1].agency != operation->agency)
		return NO_AGENCY;

	ACCOUNT new_account;
	new_account.first_name = operation->first_name;
	new_account.last_name = operation->last_name;
	new_account.cpf = operation->cpf;
	new_account.agency = operation->agency;
	new_account.balance = 0;

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

int delete_account(MANAGEMENT *operation)
{
	int account_number;
	if(!(account_number = authentication(operation)))
		return account_number;
	ACCOUNT account;

	memset(&agencies[operation->agency-1].accounts[operation->account_number-1], 0, sizeof(account));
	return 1;
}

int *management_svc(MANAGEMENT *operation)
{
	static int a;
	a = 0;
	if(operation->type == CREATE)
		a = create_account(operation);
	else if(operation->type == AUTHENTICATE)
		a = authentication(operation);
	else if(operation->type == DELETE)
		a = delete_account(operation);
	return &a;
}

float *transaction_svc(TRANSACTION *operation)
{
	static float a;
	a = 0;
	if(operation->type == WITHDRAWAL)
		a = withdrawal(operation);
	else if(operation->type == DEPOSIT)
		a = deposit(operation);
	else if(operation->type == BALANCE)
		a = balance(operation);
	return &a;
}

int main()
{
	agencies[0].agency = 1;
	if	(registerrpc(BANKPROG,BANKVERS,MANAGEMENT_OP,management_svc,
			     (xdrproc_t)xdr_management,(xdrproc_t)xdr_int ) == -1)  {
		fprintf(stderr,"Erro em registerrpc()!\n");
		exit(1);
	}

	if	(registerrpc(BANKPROG,BANKVERS,TRANSACTION_OP,transaction_svc,
			     (xdrproc_t)xdr_transaction,(xdrproc_t)xdr_float ) == -1)  {
		fprintf(stderr,"Erro em registerrpc()!\n");
		exit(1);
	}

	svc_run();
	fprintf(stderr,"Erro em svc_run()!\n");
	return 1;
}
