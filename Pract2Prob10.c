/*
 ============================================================================
 Name        : Pract2Prob10.c
 Author      : M.Pividori
 Version     :
 Copyright   : Your copyright notice
 Description : Problema de estructuras en c
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stddef.h>


typedef struct Automovil{
	char patente[10];
	char nMotor[18];
	char* marca;
	char* modelo;
	int potencia;
	char* color;
}Auto;

//Lista enlazada: estructura de datos dinamica para almacenar estructuras 'nodo'
typedef struct Nodo{
	Auto *pAuto;
	struct Nodo* siguiente;//puntero al siguiente nodo que contiene un auto
} Tnodo;

typedef struct LE{
	Tnodo* inicio;//puntero al primer nodo
} TLE;

Auto* creaAuto(char *, char *,char*, char*, int,char*);
void mostrarAuto( Auto * );
int comparadominios( Auto *, Auto * );
void cambiaColor( Auto *, char * );
void insertarAutoNodo(TLE *,Auto *);
Tnodo* nuevoNodo( Auto * );
int comparaPatente( Auto *, Auto * );
Tnodo* nuevoNodo( Auto* );
void listar(TLE*);
void eliminoNodo (TLE *,  Tnodo *);
Auto* autoMaxPot(TLE *);


int main()
{

	setbuf(stdout,0);
	printf("Detalles de la estructura de automovil\n");
	Auto a={"ABC 123","1HGBH41JXMN109186","Fiat","Fiorino",44,"rojo alpine"};
	Auto *pa=&a;
	printf("Estructura auto global  : Size:%d  Direccion:%p\n", sizeof( a), &a);
	printf("Estructura auto patente : Size:%d  Direccion:%p  offset:%d\n",sizeof(a.patente), &(a.patente), offsetof(struct Automovil,patente));
	printf("Estructura auto nroMotor: Size:%d  Direccion:%p  offset:%d\n",sizeof(a.nMotor), &(a.nMotor), offsetof(struct Automovil,nMotor));
	printf("Estructura auto marca   : Size:%d  Direccion:%p  offset:%d\n",sizeof(a.marca), &(a.marca), offsetof(struct Automovil,marca));
	printf("Estructura auto modelo  : Size:%d  Direccion:%p  offset:%d\n",sizeof(a.modelo), &(a.modelo), offsetof(struct Automovil,modelo));
	printf("Estructura auto potencia: Size:%d  Direccion:%p  offset:%d\n",sizeof(a.potencia), &(a.potencia), offsetof(struct Automovil,potencia));
	printf("Estructura auto color   : Size:%d  Direccion:%p  offset:%d\n",sizeof(a.color), &(a.color), offsetof(struct Automovil,color));
	printf("Variable puntero Estructura Auto: Size:%d  Direccion:%p  Valor:%p\n",sizeof(pa), &pa, pa);

	Auto *pb=creaAuto("JHG 776","VF33CN6AP1Y400321","Renault", "Clio Mio",76,"azul crepusculo");
	Auto *pc=creaAuto("AHU 234","8AD3CN6AP4G003230","Volkswagen","Fox Highline",110,"negro");




	printf("Donde está y cuanto ocupa cada dato de auto globalmente?\n");
	printf("Auto a: Direccion:%p Cantidad de bytes:%d Datos:\n", pa, (sizeof(struct Automovil)+strlen(pa->marca)+3+strlen(pa->modelo)+strlen(pa->color)));
	mostrarAuto(pa);
	printf("Auto b: Direccion:%p Cantidad de bytes:%d Datos:\n", pb, (sizeof(struct Automovil)+strlen(pb->marca)+strlen(pb->modelo)+strlen(pb->color)));
	mostrarAuto(pb);
	printf("Auto c: Direccion:%p Cantidad de bytes:%d Datos:\n", pc, (sizeof(struct Automovil)+strlen(pc->marca)+strlen(pc->modelo)+strlen(pc->color)));
	mostrarAuto(pc);
	printf("Cambio color auto\n");
	cambiaColor(pc,"Blanco Perlado brillo mate");
	mostrarAuto(pc);

	printf("---------------------------------------------------------\n");
	// Creo lista enlazada
	TLE miLista, *pmiLista=&miLista;
	miLista.inicio=NULL;
	printf("miLista: Size:%d  Direccion:%p\n", sizeof( miLista), &miLista);
	printf("pmiLista: Size:%d  Direccion:%p Valor:%p\n", sizeof( pmiLista), &pmiLista, pmiLista);

	insertarAutoNodo(pmiLista,pa);
	insertarAutoNodo(pmiLista,pb);
	insertarAutoNodo(pmiLista,pc);
	printf("---------------------------------------------------------\n");
	listar(pmiLista);
	pa= autoMaxPot(pmiLista);
	printf("\nAuto de Maxima Potencia\n");
	mostrarAuto(pa);

	eliminoNodo(pmiLista,pmiLista->inicio);

	printf("---------------------------------------------------------\n");
	listar(pmiLista);
	return 0;
}

Auto* creaAuto(char *patente, char *nroMotor,char* marca, char* modelo, int potencia,char* color){
	 Auto* nuevoAuto = (Auto*) malloc( sizeof(Auto) );

	 strncpy( nuevoAuto->patente,patente, sizeof(nuevoAuto->patente));
	 strcpy( nuevoAuto->nMotor, nroMotor );

	 nuevoAuto->marca = (char*) malloc( strlen(marca) +1 );
	 strcpy( nuevoAuto->marca, marca);

	 nuevoAuto->modelo = (char*) malloc( strlen(modelo) + 1);
	 strcpy( nuevoAuto->modelo, modelo);

	 nuevoAuto->potencia = potencia;

	 nuevoAuto->color = (char*) malloc( strlen(color) + 1);
	 strcpy( nuevoAuto->color, color );

	 return nuevoAuto;
 }


void mostrarAuto( Auto * elAuto ){
	printf("El auto tiene patente: %s\n",elAuto->patente);
	printf("\tNroMotor: %s\n",elAuto->nMotor);
	printf("\tMarca: %s\n",elAuto->marca);
	printf("\tModelo: %s\n",elAuto->modelo);
	printf("\tPotencia en CV: %d\n",elAuto->potencia);
	printf("\tColor: %s\n",elAuto->color);

	return;
}

void cambiaColor( Auto *elAuto, char *nColor ){

	free(elAuto->color);
	elAuto->color = (char*) malloc( strlen(nColor) + 1);
	if(elAuto->color!=NULL) {
		strcpy( elAuto->color, nColor);
	}
	/*
	elAuto->color = (char*) realloc( elAuto->color, strlen(nColor) + 1);
	if(elAuto->color!=NULL) {
		strcpy( elAuto->color, nColor);
	}
	*/
	return;
}


Tnodo* nuevoNodo( Auto* elAuto ){
	Tnodo *nNodo=(Tnodo*)malloc(sizeof(Tnodo));
	if(nNodo!=NULL) {
		nNodo->pAuto=elAuto;
		nNodo->siguiente=NULL;
	}
	return nNodo;
}

int comparaPatente( Auto *elAutoA, Auto *elAutoB ){
	//si la Patente de a es < que el de b retorna un valor negativo, 0 si son iguales y positivo si el de a es mayor que el de b
	return strcmp( elAutoA->patente, elAutoB->patente );
}

void insertarAutoNodo(TLE *pLista, Auto *elAuto){
	Tnodo * actual, *nNodo;
	nNodo= nuevoNodo(elAuto);
	if(nNodo==NULL) return;

	if((pLista->inicio==NULL) || ((pLista->inicio!=NULL) && (comparaPatente(pLista->inicio->pAuto,nNodo->pAuto)>0))){
		nNodo->siguiente=pLista->inicio;
		pLista->inicio= nNodo;
//		return;
	} else
	{
		actual = pLista->inicio;
		while(actual->siguiente!=NULL && comparaPatente(actual->siguiente->pAuto,nNodo->pAuto)<0)
		{
			actual=actual->siguiente;
		}
			nNodo->siguiente=actual->siguiente;
			actual->siguiente=nNodo;
	}

}


void listar(TLE* ini){
	Tnodo* temp=ini->inicio;
	while(temp!=NULL){
		mostrarAuto(temp->pAuto);
		temp=temp->siguiente;
	}
}

void eliminoNodo (TLE *ini,  Tnodo *aEliminar) {
	Tnodo* temp;
	if(ini->inicio==aEliminar){
		ini->inicio=aEliminar->siguiente;
	} else
	{
		temp=ini->inicio;
		while(temp->siguiente!= aEliminar)
			temp=temp->siguiente;
		temp->siguiente=aEliminar->siguiente;
	}
	free(aEliminar);
}
Auto* autoMaxPot(TLE * ini){
	Tnodo* temp=ini->inicio;
	Tnodo* max=temp;
	while(temp!=NULL){
		if(temp->pAuto->potencia > max->pAuto->potencia)
			max=temp;
		temp=temp->siguiente;
	}
	return max->pAuto;
}
