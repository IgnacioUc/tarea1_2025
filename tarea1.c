#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Ticket {
    int id;
    char descripcion[256];
    char prioridad[10];
    time_t hora_registro;
    struct Ticket* siguiente;
} Ticket;

Ticket* inicio = NULL;

// Conversión de prioridad a valor numérico (para ordenar)
int prioridad_valor(const char* prioridad) {
    if (strcmp(prioridad, "Alto") == 0) return 3;
    if (strcmp(prioridad, "Medio") == 0) return 2;
    return 1;  // Bajo
}

// Crear nuevo ticket y agregarlo ordenadamente
void registrar_ticket(int id, const char* descripcion) {
    Ticket* nuevo = (Ticket*)malloc(sizeof(Ticket));
    nuevo->id = id;
    strcpy(nuevo->descripcion, descripcion);
    strcpy(nuevo->prioridad, "Bajo");
    nuevo->hora_registro = time(NULL);
    nuevo->siguiente = NULL;

    // Insertar ordenadamente
    if (!inicio || prioridad_valor("Bajo") > prioridad_valor(inicio->prioridad)) {
        nuevo->siguiente = inicio;
        inicio = nuevo;
        return;
    }

    Ticket* actual = inicio;
    while (actual->siguiente &&
          (prioridad_valor(nuevo->prioridad) <= prioridad_valor(actual->siguiente->prioridad))) {
        actual = actual->siguiente;
    }
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
    printf("✅ Ticket registrado con prioridad 'Bajo'\n");
}

// Buscar y cambiar prioridad, luego reordenar
void asignar_prioridad(int id, const char* nueva_prioridad) {
    Ticket *anterior = NULL, *actual = inicio;

    while (actual) {
        if (actual->id == id) {
            // quitar el ticket de la lista
            if (anterior) anterior->siguiente = actual->siguiente;
            else inicio = actual->siguiente;

            strcpy(actual->prioridad, nueva_prioridad);
            actual->siguiente = NULL;

            // reinsertar ordenadamente
            registrar_ticket(actual->id, actual->descripcion);
            printf("🔄 Prioridad actualizada a %s\n", nueva_prioridad);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    printf("❌ Ticket no encontrado\n");
}

// Procesar ticket con más prioridad
void procesar_ticket() {
    if (!inicio) {
        printf("📭 No hay tickets pendientes\n");
        return;
    }
    Ticket* procesado = inicio;
    inicio = inicio->siguiente;

    printf("🛠️ Procesando Ticket ID: %d\nDescripción: %s\nPrioridad: %s\nHora: %s\n",
           procesado->id,
           procesado->descripcion,
           procesado->prioridad,
           ctime(&(procesado->hora_registro)));
    free(procesado);
}

// Mostrar lista de tickets
void mostrar_tickets() {
    if (!inicio) {
        printf("📭 No hay tickets pendientes\n");
        return;
    }
    Ticket* actual = inicio;
    printf("📋 Tickets pendientes:\n");
    while (actual) {
        printf("ID: %d | Prioridad: %s | Descripción: %s | Hora: %s",
               actual->id,
               actual->prioridad,
               actual->descripcion,
               ctime(&(actual->hora_registro)));
        actual = actual->siguiente;
    }
}

void mostrar_tickets() {
    if (!inicio) {
        printf("📭 No hay tickets pendientes.\n");
        return;
    }

    Ticket* actual = inicio;
    printf("📋 Lista de tickets pendientes:\n\n");

    while (actual) {
        char* hora_str = ctime(&(actual->hora_registro));
        hora_str[strcspn(hora_str, "\n")] = 0; // eliminar salto de línea

        printf("ID: %d\n", actual->id);
        printf("Prioridad: %s\n", actual->prioridad);
        printf("Descripción: %s\n", actual->descripcion);
        printf("Hora de registro: %s\n", hora_str);
        printf("-----------------------------\n");

        actual = actual->siguiente;
    }
}
