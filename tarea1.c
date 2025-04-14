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

// Obtener valor numérico para comparar prioridades
int prioridad_valor(const char* prioridad) {
    if (strcmp(prioridad, "Alto") == 0) return 3;
    if (strcmp(prioridad, "Medio") == 0) return 2;
    return 1; // Bajo
}

// Insertar ticket en la lista ordenadamente
void insertar_ordenado(Ticket* nuevo) {
    if (!inicio || 
        prioridad_valor(nuevo->prioridad) > prioridad_valor(inicio->prioridad) ||
        (prioridad_valor(nuevo->prioridad) == prioridad_valor(inicio->prioridad) &&
         nuevo->hora_registro < inicio->hora_registro)) {

        nuevo->siguiente = inicio;
        inicio = nuevo;
        return;
    }

    Ticket* actual = inicio;
    while (actual->siguiente &&
          (prioridad_valor(nuevo->prioridad) < prioridad_valor(actual->siguiente->prioridad) ||
           (prioridad_valor(nuevo->prioridad) == prioridad_valor(actual->siguiente->prioridad) &&
            nuevo->hora_registro >= actual->siguiente->hora_registro))) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

// Registrar nuevo ticket (siempre con prioridad "Bajo")
void registrar_ticket(int id, const char* descripcion, const char* prioridad) {
    Ticket* nuevo = (Ticket*)malloc(sizeof(Ticket));
    nuevo->id = id;
    strcpy(nuevo->descripcion, descripcion);
    strcpy(nuevo->prioridad, prioridad);
    nuevo->hora_registro = time(NULL);
    nuevo->siguiente = NULL;

    insertar_ordenado(nuevo);
    printf("✅ Ticket registrado con prioridad '%s'\n", prioridad);
}

// Asignar nueva prioridad a un ticket existente
void asignar_prioridad(int id, const char* nueva_prioridad) {
    Ticket *actual = inicio, *anterior = NULL;

    while (actual) {
        if (actual->id == id) {
            // Desenlazar el ticket
            if (anterior) anterior->siguiente = actual->siguiente;
            else inicio = actual->siguiente;

            // Actualizar prioridad
            strcpy(actual->prioridad, nueva_prioridad);
            actual->siguiente = NULL;

            // Reinsertar ordenado
            insertar_ordenado(actual);
            printf("🔄 Prioridad actualizada a %s\n", nueva_prioridad);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    printf("❌ Ticket no encontrado\n");
}

// Procesar siguiente ticket
void procesar_ticket() {
    if (!inicio) {
        printf("📭 No hay tickets pendientes\n");
        return;
    }

    Ticket* procesado = inicio;
    inicio = inicio->siguiente;

    char* hora_str = ctime(&(procesado->hora_registro));
    hora_str[strcspn(hora_str, "\n")] = 0;

    printf("🛠️ Procesando Ticket:\n");
    printf("ID: %d\nDescripción: %s\nPrioridad: %s\nHora: %s\n",
           procesado->id, procesado->descripcion, procesado->prioridad, hora_str);

    free(procesado);
}

// Mostrar todos los tickets pendientes ordenados
void mostrar_tickets() {
    if (!inicio) {
        printf("📭 No hay tickets pendientes\n");
        return;
    }

    Ticket* actual = inicio;
    printf("📋 Lista de tickets pendientes:\n\n");

    while (actual) {
        char* hora_str = ctime(&(actual->hora_registro));
        hora_str[strcspn(hora_str, "\n")] = 0; // eliminar \n

        printf("ID: %d\n", actual->id);
        printf("Prioridad: %s\n", actual->prioridad);
        printf("Descripción: %s\n", actual->descripcion);
        printf("Hora de registro: %s\n", hora_str);
        printf("-----------------------------\n");

        actual = actual->siguiente;
    }
}

// Buscar ticket por ID
void buscar_ticket(int id) {
    Ticket* actual = inicio;
    while (actual) {
        if (actual->id == id) {
            char* hora_str = ctime(&(actual->hora_registro));
            hora_str[strcspn(hora_str, "\n")] = 0;

            printf("🔎 Ticket encontrado:\n");
            printf("ID: %d\n", actual->id);
            printf("Descripción: %s\n", actual->descripcion);
            printf("Prioridad: %s\n", actual->prioridad);
            printf("Hora de registro: %s\n", hora_str);
            return;
        }
        actual = actual->siguiente;
    }
    printf("❌ No se encontró un ticket con ID %d\n", id);
}

// Menú principal
int main() {
    int opcion, id;
    char descripcion[256];
    char prioridad[10];

    do {
        printf("\n🎟️  Sistema de Gestión de Tickets\n");
        printf("1. Registrar nuevo ticket\n");
        printf("2. Asignar prioridad a ticket\n");
        printf("3. Procesar siguiente ticket\n");
        printf("4. Mostrar tickets pendientes\n");
        printf("5. Buscar ticket por ID\n");
        printf("0. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch (opcion) {
            case 1:
                printf("Ingrese ID del ticket: ");
                scanf("%d", &id);
                getchar();
                printf("Ingrese descripción del problema: ");
                fgets(descripcion, sizeof(descripcion), stdin);
                descripcion[strcspn(descripcion, "\n")] = 0;
                registrar_ticket(id, descripcion, "Bajo");
                break;
            case 2:
                printf("Ingrese ID del ticket: ");
                scanf("%d", &id);
                getchar();
                printf("Ingrese nueva prioridad (Alto/Medio/Bajo): ");
                fgets(prioridad, sizeof(prioridad), stdin);
                prioridad[strcspn(prioridad, "\n")] = 0;
                asignar_prioridad(id, prioridad);
                break;
            case 3:
                procesar_ticket();
                break;
            case 4:
                mostrar_tickets();
                break;
            case 5:
                printf("Ingrese ID a buscar: ");
                scanf("%d", &id);
                buscar_ticket(id);
                break;
            case 0:
                printf("👋 Saliendo del sistema...\n");
                break;
            default:
                printf("❌ Opción inválida.\n");
        }
    } while (opcion != 0);

    return 0;
}

