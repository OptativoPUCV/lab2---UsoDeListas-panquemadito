#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

//#include "exercises.h"

//Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
//NO MODIFICAR
void imprime_lista(List *L) {
   int *dato;
   dato = (int*)first(L);
   printf("[");
   while(dato != NULL) {
      printf("%d ", *dato);
      dato = (int*)next(L);
   }
   printf("]\n");

}

//Ojo que la pila se vacía al imprimir y se imprime en orden inverso
//NO MODIFICAR
void imprime_y_vacia_pila(Stack *P) {
   void *dato;
   printf("[");
   while((dato = pop(P)) != NULL) {
      printf("%d ", *(int*)dato);
   }
   printf("]\n");
}

/* 
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/
List* crea_lista() {
    List* L = create_list();
    if (L == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= 10; i++) {
        int* nuevoElemento = (int*)malloc(sizeof(int)); 
        if (nuevoElemento == NULL) {
            exit(EXIT_FAILURE);
        }
        *nuevoElemento = i; 
        pushBack(L, nuevoElemento); 
    }

    return L; 
}

/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.
*/
int sumaLista(List *L) {
    int suma = 0; 
    int* elemento = (int*)first(L);

    while (elemento != NULL) { 
        suma += *elemento; 
        elemento = (int*)next(L); 
    }

    return suma; 
}
/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos 
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/

void eliminaElementos(List *L, int elem) {
    if (L == NULL) return; 

    void* current = first(L);
    while (current != NULL) { 
        int* currentElem = (int*) current;
        if (*currentElem == elem) { 
            free(current); 
            popCurrent(L);
            current = next(L); 
        } else {
            current = next(L); 
        }
    }
}

/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/

#include "stack.h"

void copia_pila(Stack* P1, Stack* P2) {
  
    Stack* aux = create_stack();
    if (aux == NULL) {
        fprintf(stderr, "Failed to create auxiliary stack\n");
        exit(EXIT_FAILURE);
    }

  
    while (top(P1) != 0) {
        void* elemento = pop(P1);
        push(aux, elemento);
    }

    while (top(aux) != 0) {
        void* elemento = pop(aux);
        push(P1, elemento); 
        push(P2, elemento);
    }

}

/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus 
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/
int parentesisBalanceados(char *cadena) {
    Stack *pila = createStack();
    char *actual = cadena;
    while (*actual) {
        if (*actual == '(') {
            int *dato = (int*)malloc(sizeof(int));
            *dato = 1; 
            push(pila, dato);
        } else if (*actual == ')') {
            if (top(pila) == 0) { 
                free(pila); 
                return 0;
            } else {
                int *dato = (int*)pop(pila);
                free(dato);
            }
        }
        actual++;
    }

    int esBalanceado = (top(pila) == 0);
    while (top(pila) != 0) {
        int *dato = (int*)pop(pila);
        free(dato);
    }
    free(pila); 
    return esBalanceado;
}
