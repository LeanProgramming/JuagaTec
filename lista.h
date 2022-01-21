#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100

typedef char t_string [MAX];

typedef struct {
	t_string user;
	int contador3IL; 
	int contadorP; 
	int contadorS; 
	int contadorA;
	int contadorL;
}t_data;

typedef struct nodo {
	t_data dato;
	struct nodo *siguiente;
} t_list;

void initialize_list(t_list **);
bool empty_list(t_list *);
void push_start_list(t_list **, t_data);
void push_k_list(t_list **, int, t_data);
void push_end_list(t_list **, t_data);
void pull_start_list(t_list **);
void pull_k_list(t_list **, int);
void pull_end_list(t_list **);
void show_list(t_list *);

int list_size;

void initialize_list(t_list **p_list) {
	(*p_list) = NULL;
	list_size = 0;
}

bool empty_list(t_list * p_list) {
	if(p_list == NULL) {
		return true;
	} else {
		return false;
	}
}

 void push_start_list(t_list ** p_list, t_data p_data) {
	t_list *newNode;
	
	newNode	= (t_list *) malloc(sizeof(t_list));
	/*strcpy(newNode->dato.user, p_data.user);
	strcpy(newNode->dato.password, p_data.password);*/
	newNode->dato = p_data;
	
	if(empty_list(*p_list)) {
		newNode->siguiente = NULL;
	} else {
		newNode->siguiente = *p_list;
	}
	
	*p_list = newNode;
	list_size += 1;
	//printf("Se ha insertado el elemento al principio de la lista.\n\n");
}

void push_k_list(t_list **p_list, int k, t_data p_data) {
	t_list *newNode, *aux;
	int i;
	
	aux = *p_list;
	
	for(i=1; i<k-1; i++) {
		aux = aux->siguiente;
	}
	
	newNode	= (t_list *) malloc(sizeof(t_list));
	newNode->dato = p_data;
		
	newNode->siguiente = aux->siguiente;
	aux->siguiente = newNode;

	
	list_size += 1;
	printf("Se ha insertado el elemento a la lista en la posición %d.\n\n", k);
}

void push_end_list(t_list **p_list, t_data p_data) {
	t_list *newNode, *aux;
	int i;
	
	aux = *p_list;
	
	for(i=1; i<list_size-1; i++) {
		aux = aux->siguiente;
	}
		
	if(empty_list(*p_list)) {
		printf("La lista está vacía.\n\n");
	} else {
		newNode	= (t_list *) malloc(sizeof(t_list));
		newNode->dato = p_data;
		
		newNode->siguiente = NULL;
		aux->siguiente = newNode;
	}

	list_size += 1;
	printf("Se ha insertado el elemento al final de la lista.\n\n");
}

void pull_start_list(t_list **p_lista) {
	t_list *deleteNode;
	
	deleteNode = *p_lista;
	(*p_lista) = (*p_lista)->siguiente;
	free(deleteNode);
	deleteNode = NULL;
	
	list_size -= 1;
	printf("Se ha eliminado un elemento del inicio de la lista.\n\n");
}
void pull_k_list(t_list **p_lista, int k) {
	t_list *deleteNode, *aux;
	int i;
	
	aux = *p_lista;
	
	for(i=1; i<k-1; i++) {
		aux = aux->siguiente;
	}
	
	deleteNode = aux->siguiente;
	aux->siguiente = deleteNode->siguiente;
	
	free(deleteNode);
	deleteNode = NULL;
	
	list_size -= 1;
	printf("Se ha eliminado un elemento de la lista en la posición %d.\n\n", k);
}
void pull_end_list(t_list **p_list) {
	t_list *deleteNode, *aux;
	int i;
	
	aux = *p_list;
	
	for(i=1; i<list_size-2; i++) {
		aux = aux->siguiente;
	}
		
	if(empty_list(*p_list)) {
		printf("La lista está vacía.\n\n");
	} else {
		deleteNode = aux->siguiente;
		aux->siguiente = NULL;
	
		free(deleteNode);
		deleteNode = NULL;
	}

	list_size -= 1;
	printf("Se ha eliminado el elemento al final de la lista.\n\n");
}
 
void show_list(t_list *p_list) {
	int i = 1;
	t_list *aux;	
	aux = p_list;
	
	while(aux != NULL) {
		printf("%d-", i);
		printf("%s\t\t\t\n", aux->dato.user);
		printf("%d\t%d\t%d\t%d\t%d\n", aux->dato.contador3IL, aux->dato.contadorP, aux->dato.contadorS, aux->dato.contadorA, aux->dato.contadorL);
		aux = aux->siguiente;
		i++;
	}
}


