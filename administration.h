#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>

typedef struct{
  int account_number;
  int agency;
  char *first_name, *last_name;
  char *cpf;
  int balance;  
}ACCOUNT;
