#include "administration.h"
#include "const.h"

AGENCY agencies[5];

float deposit(TRANSACTION *operation)
{
	if(agencies[operation->agency-1].agency != operation->agency)
		return NO_AGENCY;
	agencies[operation->agency-1].accounts[operation->account_number-1].balance += operation->value;
	return agencies[operation->agency-1].accounts[operation->account_number-1].balance;
}

float withdrawal(TRANSACTION *operation)
{
	if(agencies[operation->agency-1].agency != operation->agency)
		return NO_AGENCY;
	int balance = agencies[operation->agency-1].accounts[operation->account_number-1].balance - operation->value;
	if(balance < 0)
		return -1;

	agencies[operation->agency-1].accounts[operation->account_number-1].balance -= operation->value;
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
	static int output;
	output = 0;

	if(operation->type == CREATE)
	{
		if(agencies[operation->agency-1].last_operation_ID != operation->operation_ID)
			output = create_account(operation);
		else
			output = -4;
	}
	else
	{
		if(operation->account_number != agencies[operation->agency-1].accounts[operation->account_number].account_number)
		{
			output = -5;
			return &output;
		}
		
		if(operation->type == AUTHENTICATE)
		{
				output = authentication(operation);

		}
		else if(operation->type == DELETE)
		{
			if(agencies[operation->agency-1].last_operation_ID != operation->operation_ID)
				output = delete_account(operation);
			else
				output = -4;
		}
	}

		agencies[operation->agency-1].last_operation_ID = operation->operation_ID;
	return &output;
}

float *transaction_svc(TRANSACTION *operation)
{
	static float output;
	output = 0;

	if(operation->account_number != agencies[operation->agency-1].accounts[operation->account_number].account_number)
	{
		output = -5;
		return &output;
	}

	if(operation->type == WITHDRAWAL)
	{
		if(agencies[operation->agency-1].last_operation_ID != operation->operation_ID)
			output = withdrawal(operation);
		else
			output = -4;
	}
	else if(operation->type == DEPOSIT)
	{
		if(agencies[operation->agency-1].last_operation_ID != operation->operation_ID)
			output = deposit(operation);
		else
			output = -4;
	}
	else if(operation->type == BALANCE)
	{
			output = balance(operation);
	}
	agencies[operation->agency-1].last_operation_ID = operation->operation_ID;
	return &output;
}

int main()
{
	memset(agencies, 0, sizeof(agencies));
	agencies[0].agency = 1;
	agencies[1].agency = 2;
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
