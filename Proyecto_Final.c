#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct _nodo {
   char valor;
   struct _nodo *siguiente;
} tipoNodo;
 
typedef tipoNodo *pNodo;
typedef tipoNodo *Pila;
int opera(char op);

void Push(Pila *l, char v);
char Pop(Pila *l);
void Prefija(char cadena[100]);
void Posfija(char cadena[100]);

main()
{
	int op;
	char cadena[100];
	char opc;
	printf("Escriba su cadena\n");
	scanf("%s", cadena);
	do{
		printf("Que desea hacer:\n\t1)Pasar a notacion prefija\n\t2)Pasar a notacion posfija\n\t3)Salir\n");
		scanf("%i",&op);
		system("cls");
		switch(op){
			case 1:
				printf("Su cadena original es: es: %s\n",cadena);
				Prefija(cadena);
				system("pause");system("cls");
				break;
			case 2:
				printf("Su cadena original es: : %s\n",cadena);
				Posfija(cadena);
				system("pause");system("cls");
				break;
			case 3:
				printf("Hasta luego\n");
				break;
			default:
				printf("Opcion incorrecta\n");
				break;
		}
	}while(op!=3);
}

void Push(Pila *pila, char v) {
   pNodo nuevo;
   nuevo = (pNodo)malloc(sizeof(tipoNodo));
   nuevo->valor = v;
   nuevo->siguiente = *pila;
   *pila = nuevo;
}
 
char Pop(Pila *pila) {
   pNodo nodo;
   char v;
   nodo = *pila;
   if(!nodo) return 0;
   *pila = nodo->siguiente;
   v = nodo->valor; 
   free(nodo);
   return v;
}
 
int opera(char op){
	int com=0;
	if(op=='+'){
		com=1;
	}
	if(op=='-'){
		com=1;
	}
	if(op=='*'){
		com=2;
	}
	if(op=='/'){
		com=2;
	}
	if(op=='^'){
		com=3;
	}
	return com;
}
void Prefija(char cadena[100]){
	Pila pila = NULL;
	char aux[10]="";
	int i=0,j=0,x;
	char pre[50]="";
	while (cadena[i]!='\0'){
		if (cadena[i] =='+'|| cadena[i] =='-'|| cadena[i] =='*'|| cadena[i] =='/'|| cadena[i] =='^'){
			if(aux[0]=='\0'){
				aux[0]=cadena[i];
			}
			else{
				x=strlen(aux)-1;
				for(x;x>=0;x--){
					if(opera(aux[x])>=opera(cadena[i])){
						Push(&pila, aux[x]);
						aux[x]='\0';
						j--;
					}
					aux[j]=cadena[i];
				}
			}
			j++;
		}else{
			Push(&pila, cadena[i]);	
		}
		i++;		
	}
	x=strlen(aux)-1;
	for(x;x>=0;x--){
		Push(&pila,aux[x]);
	}
	printf("La expresion prefija es: ");
	while(pila != NULL){
		printf("%c", Pop(&pila));
		i++;
	}
	printf("\n");
}

void Posfija(char cadena[100]){
	Pila pila = NULL;
	char aux[50]="";
	int i=0,j=0;
	while (cadena[i]!='\0'){
		if (cadena[i] =='+'|| cadena[i] =='-'|| cadena[i] =='*'|| cadena[i] =='/'|| cadena[i] =='^'){
			if(pila == NULL){
				Push(&pila, cadena[i]);
			}else{
				while (pila != NULL && opera(pila->valor) >= opera(cadena[i])){
					aux[j] = Pop(&pila);
					j++;
				}
				Push(&pila, cadena[i]);
			}
		}else{
			aux[j] = cadena[i];
			j++;
		}
		i++;
	}
	while(pila != NULL){
		aux[j] = Pop(&pila);
		j++;
	}
	printf("la expresion posfija es: %s\n",aux);
}
