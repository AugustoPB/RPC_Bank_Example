#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>

#define MAX_ACCOUNTS_NUMBER 10

typedef struct{
  int account_number;
  int agency;
  char *first_name, *last_name;
  char *cpf;
  float balance;
}ACCOUNT;

typedef struct{
  int agency;
  int last_operation_ID;
  ACCOUNT accounts[10];
}AGENCY;
