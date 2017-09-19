#include <stdio.h>
#include "const.h"
#include <sys/time.h>

int main(int argc, char *argv[])
{
  int agency_number = 2;
  int output;
  char *input;
  size_t inputsize = 32;
  input = (char *)malloc(inputsize*sizeof(char));
  time_t timer;
   
  while (1)
  {
    printf(">>>");
    scanf("%s", input);

    MANAGEMENT account;
    TRANSACTION transaction;
    if(!strcmp(input, "create"))
    {
      output = 9;
      memset(&account, 0, sizeof(account));

      printf("First Name: ");
      scanf("%s", &account.first_name); 
      printf("Last Name: ");
      scanf("%s", &account.last_name);
      printf("CPF: ");
      scanf("%s", &account.cpf); 
      account.agency = agency_number;
      account.type = CREATE;
      account.operation_ID = time(&timer);
      account.operation_ID = (account.operation_ID*100) + account.agency;
      printf("%d,%d,%s,%s,%s,%d,%d\n",account.type,account.operation_ID,&account.first_name,&account.last_name,&account.cpf,account.account_number,account.agency);
     /* int stat = callrpc("localhost", OPPROG, OPVERSION, MANAGEMENT_OP,
               (xdrproc_t)xdr_management, (char *)&account,
               (xdrproc_t)xdr_int, (char *)&output );
      if	(stat!= 0)  {
        clnt_perrno(stat);
        printf("\n");
        return 1;}*/
       
    }
    else if(!strcmp(input, "delete"))
    {
      memset(&account, 0, sizeof(account));

      printf("Nº da Conta: \n");
      scanf("%02d", &account.account_number);
      printf("Agencia: \n");
      scanf("%02d", &account.agency);
      account.type = DELETE;
      account.operation_ID = time(&timer);
      account.operation_ID = (account.operation_ID*100) + account.agency;
      printf("%d,%d,%s,%s,%s,%d,%d\n",account.type,account.operation_ID,account.first_name,account.last_name,account.cpf,account.account_number,account.agency);
     /* int stat = callrpc("localhost", OPPROG, OPVERSION, MANAGEMENT_OP,
               (xdrproc_t)xdr_management, (char *)&account,
               (xdrproc_t)xdr_int, (char *)&output );
      if	(stat!= 0)  {
        clnt_perrno(stat);
        printf("\n");
        return 1;}*/

    }
    else if(!strcmp(input, "balance"))
    {
      memset(&account, 0, sizeof(account));

      printf("Nº da Conta: \n");
      scanf("%02d", &account.account_number);
      printf("Agencia: \n");
      scanf("%02d", &account.agency);
      account.type = BALANCE;
      account.operation_ID = time(&timer);
      account.operation_ID = (account.operation_ID*100) + account.agency;
      printf("%d,%d,%s,%s,%s,%d,%d\n",account.type,account.operation_ID,account.first_name,account.last_name,account.cpf,account.account_number,account.agency);
    }
    else if(!strcmp(input, "deposit"))
    {
      memset(&transaction, 0, sizeof(transaction));
      printf("Nº da Conta: \n");
      scanf("%02d", &transaction.account_number);
      printf("Agencia: \n");
      scanf("%02d", &transaction.agency);
      printf("Valor: ");
      scanf("%f", &transaction.value);
      transaction.type = DEPOSIT;
      transaction.operation_ID = time(&timer);
      transaction.operation_ID = (transaction.operation_ID*100) + transaction.agency;
      printf("%d,%d,%d,%d,%f\n",transaction.type,transaction.operation_ID,transaction.account_number,transaction.agency,transaction.value);
    }
    else if(!strcmp(input, "withdrawal"))
    {
      memset(&transaction, 0, sizeof(transaction));
      printf("Nº da Conta: \n");
      scanf("%02d", &transaction.account_number);
      printf("Agencia: \n");
      scanf("%02d", &transaction.agency);
      printf("Valor: ");
      scanf("%f", &transaction.value);
      transaction.type = WITHDRAWAL;
      transaction.operation_ID = time(&timer);
      transaction.operation_ID = (transaction.operation_ID*100) + transaction.agency;
      printf("%d,%d,%d,%d,%f\n",transaction.type,transaction.operation_ID,transaction.account_number,transaction.agency,transaction.value);
    }
  }
}
