#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea {
    int TareaID;
    char *Descripcion;
    int Duracion;
} Tarea;

typedef struct Nodo {
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

// Prototipos de funciones
Nodo *CrearListaVacia();
Nodo *CrearNodo(char *Descripcion, int Duracion, int id);
void InsertarNodo(Nodo **start, Nodo *Nodot1);
void InsertarAlFinal(Nodo **start, Nodo *Nodot1);
Nodo *EliminarNodo(Nodo **start, Nodo *Nodot1);

void MostrarTareasPendientes(Nodo *start);
void MostrarTareasRealizadas(Nodo *Trealizadas);

//Main principal
int main() {
    Nodo *start = CrearListaVacia();
    Nodo *Trealizadas = CrearListaVacia();
    int id = 1000;
    int opcion;
    int duracion;
    char buffer[500];
    char respuesta;

    do {
        printf("\n----MENU----\n");
        printf("1 : Cargar tareas pendientes\n");
        printf("0 : Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        if (opcion == 1) {
            do {
                printf("Ingrese la descripcion de la tarea:\n");
                gets(buffer);

                printf("Ingrese la duracion de la tarea (10-100):\n");
                scanf("%d", &duracion);
                getchar();
                char *descripcion = (char *)malloc(strlen(buffer) + 1);
                strcpy(descripcion, buffer);

                Nodo *Nodot1 = CrearNodo(descripcion, duracion, id++);
                InsertarNodo(&start, Nodot1);

                printf("Desea cargar otra tarea? (S/N): ");
                scanf("%c", &respuesta);
                getchar();
            } while (respuesta == 's' || respuesta == 'S');

            Nodo *tareaPendiente = start;

            while (tareaPendiente != NULL) {
                Nodo *siguiente = tareaPendiente->Siguiente;

                printf("\nTarea Id: %d\n", tareaPendiente->T.TareaID);
                printf("Descripcion: %s\n", tareaPendiente->T.Descripcion);
                printf("Duracion: %d\n", tareaPendiente->T.Duracion);
                printf("¿La tarea fue realizada? (S/N): ");
                scanf("%c", &respuesta);
                getchar();

                if (respuesta == 's' || respuesta == 'S') {
                    EliminarNodo(&start, tareaPendiente);
                    tareaPendiente->Siguiente = NULL;
                    InsertarAlFinal(&Trealizadas, tareaPendiente);
                }

                tareaPendiente = siguiente;
            }

            MostrarTareasPendientes(start);
            MostrarTareasRealizadas(Trealizadas);
        }

    } while (opcion != 0);

    return 0;
}

//Funciones
Nodo *CrearListaVacia() {
    return NULL;
}

Nodo *CrearNodo(char *Descripcion, int Duracion, int id) {
    Nodo *NodoT1 = (Nodo *)malloc(sizeof(Nodo));
    NodoT1->T.TareaID = id;
    NodoT1->T.Descripcion = Descripcion;
    NodoT1->T.Duracion = Duracion;
    NodoT1->Siguiente = NULL;
    return NodoT1;
}

void InsertarNodo(Nodo **start, Nodo *NodoT1) {
    NodoT1->Siguiente = *start;
    *start = NodoT1;
}

void InsertarAlFinal(Nodo **start, Nodo *NodoT1) {
    if (*start == NULL) {
        *start = NodoT1;
    } else {
        Nodo *auxiliar = *start;
        while (auxiliar->Siguiente != NULL) {
            auxiliar = auxiliar->Siguiente;
        }
        auxiliar->Siguiente = NodoT1;
    }
}

Nodo *EliminarNodo(Nodo **start, Nodo *Nodot1) {
    Nodo **aux = start;
    while (*aux != NULL && *aux != Nodot1) {
        aux = &(*aux)->Siguiente;
    }
    if (*aux) {
        Nodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        temp->Siguiente = NULL;
        return temp;
    }
    return NULL;
}

void MostrarTareasPendientes(Nodo *start) {
    printf("--Tareas pendientes--\n");
    Nodo *aux = start;
    while (aux != NULL) {
        printf("Id: %d\n", aux->T.TareaID);
        printf("Descripcion: %s\n", aux->T.Descripcion);
        printf("Duracion: %d\n\n", aux->T.Duracion);
        aux = aux->Siguiente;
    }
}

void MostrarTareasRealizadas(Nodo *Trealizadas) {
    printf("--Tareas Realizadas--\n");
    Nodo *aux = Trealizadas;
    while (aux != NULL) {
        printf("Id: %d\n", aux->T.TareaID);
        printf("Descripcion: %s\n", aux->T.Descripcion);
        printf("Duracion: %d\n\n", aux->T.Duracion);
        aux = aux->Siguiente;
    }
}
