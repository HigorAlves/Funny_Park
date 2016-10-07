########## Makefile ##############

#Principais
	name = tp2
	dirBib = bibliotecas/
	compl = gcc
	main = main.c	

	#Saida
	namet_e = tentErr.out
	namebak = backtrack.out
	nameheu = heuristica.out

	#Biblioteca
	bibG = geral.h
	bibB = backtrack.h
	bibH = heuristica.h
	bibV = verificador.h

	#Referência
	refG = geral.c
	refB = backtrack.c
	refH = heuristica.c
	refV = verificador.c

	#Dependencias
	depV = verificador.o
	depG = geral.o
	depB = backtrack.o
	depH = heuristica.o

all: $(name)

$(name): $(depG) $(depV) $(depB) $(depH) $(main)
	$(compl) $(depG) $(depV) $(depB) $(depH) $(main) -o $(name)
	rm -rf *.o *.gch

$(depH):$(dirBib)$(bibH) $(dirBib)$(refH)
	$(compl) -c $(dirBib)$(bibH) $(dirBib)$(refH)

$(depB):$(depG) $(dirBib)$(bibB) $(dirBib)$(refB)
	$(compl) -c $(dirBib)$(bibB) $(dirBib)$(refB)
	
$(depV): $(dirBib)$(bibV) $(dirBib)$(refV)
	$(compl) -c $(dirBib)$(bibV) $(dirBib)$(refV)

$(depG):$(dirBib)$(bibG) $(dirBib)$(refG)
	$(compl) -c $(dirBib)$(bibG) $(dirBib)$(refG)

clear: 
	rm -rf *.o *.gch *.out $(name)
