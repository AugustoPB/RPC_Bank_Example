all:		servidor cliente agency atm

cliente:	cliente.c const.h
		@gcc -o cliente cliente.c

servidor:	servidor.c const.h
		@gcc -o servidor servidor.c

agency:	agency.c const.h
		@gcc -o agency agency.c

atm:	ATM.c const.h
		@gcc -o ATM ATM.c

clean:
		@rm -f cliente servidor agency atm *~

info:
		@echo "(c) Roland Teodorowitsch (30 ago. 2013 - 31 mar. 2017)"
