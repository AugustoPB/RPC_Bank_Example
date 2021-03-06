/* const.h (Roland Teodorowitsch; 30 ago. 2013 - 31 mar. 2017) */
#include <rpc/rpc.h>

#define BANKPROG	0x20000000LU
#define BANKVERS	1
#define TRANSACTION_OP	1
#define MANAGEMENT_OP 2
#define CREATE 1
#define DELETE 2
#define AUTHENTICATE 3
#define WITHDRAWAL 4
#define DEPOSIT 5
#define BALANCE 6
#define NO_AGENCY -2

typedef struct
{
  int type;
  int operation_ID;
  char first_name[20],last_name[20];
  char cpf[20];
  int account_number;
  int agency;
} MANAGEMENT;

typedef struct
{
  int type;
  int operation_ID;
  int account_number;
  int agency;
  float value;
} TRANSACTION;

int xdr_management(XDR *xdrsp, MANAGEMENT *operation)
{
    if (!xdr_int(xdrsp, &operation->type))
        return (0);
    if (!xdr_int(xdrsp, &operation->operation_ID))
        return (0);
    if (!xdr_vector(xdrsp, operation->first_name, 20, sizeof(char),(xdrproc_t)xdr_char))
        return (0);
    if (!xdr_vector(xdrsp, operation->last_name, 20, sizeof(char),(xdrproc_t)xdr_char))
        return (0);
    if (!xdr_vector(xdrsp, operation->cpf, 20, sizeof(char),(xdrproc_t)xdr_char))
        return (0);
    if (!xdr_int(xdrsp, &operation->account_number))
        return (0);
    if (!xdr_int(xdrsp, &operation->agency))
        return (0);
    return (1);
}

int xdr_transaction(XDR *xdrsp, TRANSACTION *operation)
{
    if (!xdr_int(xdrsp, &operation->type))
        return (0);
    if (!xdr_int(xdrsp, &operation->operation_ID))
        return (0);
    if (!xdr_int(xdrsp, &operation->account_number))
        return (0);
    if (!xdr_int(xdrsp, &operation->agency))
        return (0);
    if (!xdr_float(xdrsp, &operation->value))
        return (0);
    return (1);
}
