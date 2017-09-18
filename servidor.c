#include "administration.h"
#include "const.h"



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

double *obtem_nota_1_svc(struct simple *test)
{
	static double a = 4;
	return &a;
}

int main()
{
	if	(registerrpc(BANKPROG,BANKVERS,MANAGEMENT_OP,obtem_nota_1_svc,
			     (xdrproc_t)xdr_management,(xdrproc_t)xdr_double ) == -1)  {
		fprintf(stderr,"Erro em registerrpc()!\n");
		exit(1);
	}
	svc_run();
	fprintf(stderr,"Erro em svc_run()!\n");
	return 1;
}
