#include <stdio.h>
#include "cont.h"
#include <sys/time.h>

int main(int argc, char *argv[])
{
  int agency_number = 2;
  int output;
  char *input;
  size_t inputsize = 32;
  input = (char *)malloc(inputsize*sizeof(char));
  struct timeval tv;

  while (1)
  {
    printf(">>>");
    scanf("%s", input);

    struct MANAGEMENT account;
    //struct MANAGEMENT management;

    if(!strcmp(input, "create"))
    {
      output = 9;
      memset(&account, 0, sizeof(account));

      printf("First Name: ");
      scanf("%s", account.first_name);
      printf("Last Name: ");
      scanf("%s", account.last_name);
      printf("CPF: ");
      scanf("%s", account.cpf); 
      account.agency = agency_number;
      account.type = CREATE;
      gettimeofday(&tv,NULL);
      
      account.operation_ID = 
      int stat = callrpc("localhost", OPPROG, OPVERSION, MANAGEMENT_OP,
               (xdrproc_t)xdr_management, (char *)&account,
               (xdrproc_t)xdr_int, (char *)&output );
      if	(stat!= 0)  {
        clnt_perrno(stat);
        printf("\n");
        return 1;}
    }
    else if(!strcmp(input, "delete"))
    {
      memset(&account, 0, sizeof(account));

      printf("Nº da Conta: \n");
      scanf("%02d\n", &account.account_number);
      printf("Agencia: \n");
      scanf("%02d\n", &account.agency);
      account.type = DELETE
      int stat = callrpc("localhost", OPPROG, OPVERSION, MANAGEMENT_OP,
               (xdrproc_t)xdr_management, (char *)&account,
               (xdrproc_t)xdr_int, (char *)&output );
      if	(stat!= 0)  {
        clnt_perrno(stat);
        printf("\n");
        return 1;}

    }
    else if(!strcmp(input, "balance"))
    {

    }
    else if(!strcmp(input, "deposit"))
    {

    }
    else if(!strcmp(input, "withdrawal"))
    {

    }
  }
}
