#include <stdio.h>
#include "const.h"
#include <time.h>

int rpc_management(char *ip,MANAGEMENT *account){
      int stat = callrpc(ip, OPPROG, OPVERSION, MANAGEMENT_OP,
               (xdrproc_t)xdr_management, (char *)&account,
               (xdrproc_t)xdr_int, (char *)&output );
      if	(stat!= 0)  {
        clnt_perrno(stat);
        printf("\n");
        return -1000;}
      return output;
}

float rpc_transaction(char *ip,TRANSACTION *transaction){
    int stat = callrpc(ip, OPPROG, OPVERSION, TRANSACTION_OP,
               (xdrproc_t)xdr_transaction, (char *)&transaction,
               (xdrproc_t)xdr_float, (char *)&output );
      if	(stat!= 0)  {
        clnt_perrno(stat);
        printf("\n");
        return -1000;}
      return output;

}

int main(int argc, char *argv[])
{
  int output;
  time_t timer;
  
  MANAGEMENT account;
  TRANSACTION transaction;

  while (1)
  {
    printf("Insira o numero da conta:");
    scanf("%s", account);
  }

 
}
