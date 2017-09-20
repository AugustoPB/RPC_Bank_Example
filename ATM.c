#include <stdio.h>
#include "const.h"
#include <time.h>


float rpc_transaction(char *ip,TRANSACTION *transaction){
  float output;
    int stat = callrpc(ip, BANKPROG, BANKVERS, TRANSACTION_OP,
               (xdrproc_t)xdr_transaction, (char *)transaction,
               (xdrproc_t)xdr_float, (char *)&output );
      if	(stat!= 0)  {
        clnt_perrno(stat);
        printf("\n");
        return -1000;}
      return output;

}

int main(int argc, char *argv[])
{
  float output;
  time_t timer;
  int account_number,operation,agency;
  TRANSACTION transaction;

  while (1)
  {
    printf("Insira o numero da conta:\n");
    scanf("%d", &account_number);
    printf("Insira o numero da agencia:\n");
    scanf("%d", &agency);
    printf("Escolha a operação desejada: \n1-Deposit\n2-Balance\n3-Withdrawal\n");
    scanf("%d",&operation);
    if(operation==1){
      memset(&transaction, 0, sizeof(transaction));
      transaction.account_number = account_number;
      transaction.agency = agency;
      printf("Valor: ");
      scanf("%f", &transaction.value);
      transaction.type = DEPOSIT;
      transaction.operation_ID = time(&timer);
      transaction.operation_ID = (transaction.operation_ID*100) + transaction.agency;
    //  printf("%d,%d,%d,%d,%f\n",transaction.type,transaction.operation_ID,transaction.account_number,transaction.agency,transaction.value);
      output = rpc_transaction((char *)"localhost",&transaction);
      printf("%f\n", output);
    }
    else if (operation==2){
      memset(&transaction, 0, sizeof(transaction));
      transaction.account_number = account_number;
      transaction.agency = agency;
      transaction.type = BALANCE;
      transaction.operation_ID = time(&timer);
      transaction.operation_ID = (transaction.operation_ID*100) + transaction.agency;
      output = rpc_transaction((char *)"localhost",&transaction);
      printf("Balance value: %f\n",output);
    }
    else if (operation==3){
      memset(&transaction, 0, sizeof(transaction));
      transaction.account_number = account_number;
      transaction.agency = agency;
      printf("Valor: ");
      scanf("%f", &transaction.value);
      transaction.type = WITHDRAWAL;
      transaction.operation_ID = time(&timer);
      transaction.operation_ID = (transaction.operation_ID*100) + transaction.agency;
     // printf("%d,%d,%d,%d,%f\n",transaction.type,transaction.operation_ID,transaction.account_number,transaction.agency,transaction.value);
      output = rpc_transaction((char *)"localhost",&transaction);
      printf("%f\n", output);
    }
    else
    {
    printf("Operação inexistente\n");
    }
  }
}
